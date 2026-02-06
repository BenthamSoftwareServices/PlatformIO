HOW TO STOP THE PLATFORMIO DEBUGGER IN THE SETUP FUNCTION

Designed for Seeeduino XIAO ESP32-S3 or similar

Start with the templates for main.cpp and platformio.ini at the end of this document.


1: Start Debug without uploading
2: Debug toolbar appears, showing only pause and stop
3: Click pause
4: Execution stops at line 3 in esp_pm_impl_waiti.dbgasm
5: Click continue
6: Execution stops at line 8 in main.continue
7: If continue is clicked execution just returns to line 8
8: To continue debugging, right click local variable stop_here = 1 and set value = 0 and press enter
9: Use step over to step through setup()
10: At the last line of setup() use continue to move to loop()

MAIN.CPP
========
; =============================================================================
; DEBUG ENVIRONMENT - Use this for debugging with breakpoint in setup()
; =============================================================================
[env:DEBUG]
platform = espressif32
board = seeed_xiao_esp32s3
framework = arduino

; Debug build settings
build_type = debug
build_unflags = -Os
build_flags = 
    -Og                              ; Optimize for debugging
    -g3                              ; Maximum debug info
    -DARDUINO_USB_CDC_ON_BOOT=1      ; Enable USB CDC
    -DDEBUG_SETUP                    ; Enable setup() breakpoint spin loop

; Debug tool configuration
debug_tool = esp-builtin
debug_speed = 5000

; Initialize debugger at setup
debug_init_break = tbreak setup

; Extra debug commands
debug_extra_cmds =
    set complaints 0
    set print pretty on
    mon reset halt

; Upload settings
upload_speed = 921600

; =============================================================================
; RELEASE ENVIRONMENT - Use this for normal running (no debug breakpoints)
; =============================================================================
[env:RELEASE]
platform = espressif32
board = seeed_xiao_esp32s3
framework = arduino

; Release build settings
build_type = release
build_flags = 
    -Os                              ; Optimize for size
    -DARDUINO_USB_CDC_ON_BOOT=1      ; Enable USB CDC
    ; Note: DEBUG_SETUP is NOT defined, so spin loop is removed

; Upload settings
upload_speed = 921600

; =============================================================================
; SHARED SETTINGS (optional - if you want common settings)
; =============================================================================
; You can also create a common environment and extend it:
; [env]
; platform = espressif32
; board = seeed_xiao_esp32s3
; framework = arduino
; Then use: [env:debug] extends = env

PLATFORMIO.INI
==============
#include <Arduino.h>

// #define LED 21 // Built-in orange user LED on GPIO21 on XIAO ESP32-S3
#define LED                                                                    \
    D1 // External LED on pin D1, which is GPIO2, so D1 or just 2 flashes D1

void setup()
{
#ifdef DEBUG_SETUP
    volatile int stop_here = 1;
    while (stop_here)
        ;
#endif

    delay(2000);
    pinMode(LED, OUTPUT);
    digitalWrite(LED, HIGH); // Turn on the LED
    asm("nop");
}

void loop()
{
    digitalWrite(LED, LOW); // Turn off the LED
    delay(1250);

    digitalWrite(LED, HIGH); // Turn on the LED
    delay(250);
}
