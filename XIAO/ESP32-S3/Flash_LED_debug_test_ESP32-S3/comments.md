HOW TO DEBUG AN ESP32-S3 USING PLATFORMIO

Using a dual environment that selects between DEBUG or RELEASE

Working Debug Procedure for ESP32-S3 setup()

 1: Start Debug (with or without uploading)
 2: Debug toolbar appears - Shows pause, reset and stop buttons
 3: Click Pause - Manually halt execution
 4: Stops in bootloader file - esp_pm_impl_waiti.dbgasm (line 3)
 5: Click Continue - Lets it run to your breakpoint
 6: Stops at while (stop_here) // Set a breakpoint at this line the spin loop in setup()
 7: Clicking continue (F5) at this point just cycles around and stops again at the stop_here breakpoint
 8: Change the value of a variable - Right-click stop_here in Local variables → Set Value → 0 → Enter
 9: Step through setup() - Use F10 (Step Over) to go line by line
10: Continue to loop() - At end of setup() at the last line of code, press F5 (Continue) to reach loop()

MAIN.CPP
========
#include <Arduino.h>

// #define LED 21 //Built-in orange user LED on GPIO21 on XIAO ESP32-S3
#define LED                                                                    \
    D1 //External LED on pin D1, which is GPIO2, so D1 or just 2 flashes D1

void setup()
{
    // The following five lines cause execution to stop if the environment (env)
    // is set to env:DEBUG otherwise they are ignored if env:RELEASE is selected
#ifdef DEBUG_SETUP
    volatile int stop_here = 1;
    while (stop_here) //Set a breakpoint at this line the spin loop in setup()
        ;
#endif

    delay(100);
    pinMode(LED, OUTPUT);
    digitalWrite(LED, HIGH); // Turn on the LED
    asm("nop"); //Use continue (F10) at this line if debugging
}

void loop()
{
    digitalWrite(LED, LOW); // Turn off the LED
    delay(1250);

    digitalWrite(LED, HIGH); // Turn on the LED
    delay(250);
}



PLATFORMIO.INI
==============
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