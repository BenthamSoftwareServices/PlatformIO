# SAMD21-M0-Mini PlatformIO Project

This repository contains the configuration, sketches, and supporting files for using SAMD21-M0-Mini modules (including low-cost clones from AliExpress) with PlatformIO, USB serial, and J-Link EDU Mini for programming and debugging.

This guide covers using a SAMD21-M0-Mini module with PlatformIO, uploading firmware via USB (SAM-BA) or J-Link, debugging with J-Link, serial output via SerialUSB, custom variant files and board configuration, and useful additional files for J-Link debug.

## Hardware

- Module: SAMD21-M0-Mini (example clone: [AliExpress link](https://www.aliexpress.com/item/32923024996.html))
- Programmer/Debugger: J-Link EDU Mini (or equivalent)
- USB connection: Optional for USB serial or SAM-BA upload

## Project Structure

SAMD21-M0-Mini/
├─ src/
│ └─ main.cpp
├─ platformio.ini
├─ boards/
│ └─ samd21_m0_mini.json
├─ Additional files for j-link debug/
│ ├─ variant.h
│ └─ variant.cpp
└─ README.md

markdown
Copy code

- `boards/samd21_m0_mini.json`: Custom board configuration for PlatformIO
- `Additional files for j-link debug`: Contains custom variant.h and variant.cpp needed for J-Link debug
- `platformio.ini`: Dual-environment configuration (USB SAM-BA or J-Link)

## platformio.ini

[env:samd21_m0_mini_samba]
platform = atmelsam
board = samd21_m0_mini
framework = arduino
monitor_speed = 115200
upload_protocol = sam-ba
debug_tool = jlink
debug_init_break = tbreak setup
build_type = debug

[env:samd21_m0_mini_jlink]
platform = atmelsam
board = samd21_m0_mini
framework = arduino
monitor_speed = 115200
upload_protocol = jlink
debug_tool = jlink
debug_init_break = tbreak setup
debug_load_mode = manual
build_type = debug

csharp
Copy code

You can select either environment from the PlatformIO status bar. The jlink environment allows programming and debugging without a USB cable. `debug_load_mode = manual` ensures the debugger does not automatically overwrite firmware, which is necessary for the SAMD21 setup.

## Example Sketch (src/main.cpp)

#include <Arduino.h>

void setup() {
SerialUSB.begin(115200);

arduino
Copy code
// Wait up to 2 seconds for SerialUSB
uint32_t startTime = millis();
while (!SerialUSB && (millis() - startTime < 2000)) {}

pinMode(13, OUTPUT);   // Built-in LED at PA17

if (SerialUSB) {
    SerialUSB.println("SAMD21-M0-Mini: Serial loop test starting...");
}
}

void loop() {
static uint32_t counter = 0;

scss
Copy code
// Toggle LED every 250 ms
digitalWrite(13, !digitalRead(13));

// Print counter every 1 second
if (counter % 4 == 0) {
    if (SerialUSB) {
        SerialUSB.print("Loop counter: ");
        SerialUSB.println(counter / 4);
    }
}

counter++;
delay(250);
}

pgsql
Copy code

The LED toggles every 250 ms. The serial counter prints every 1 s. A 2-second timeout prevents hanging if USB is not connected.

## Custom Variant

Place variant.h and variant.cpp from the `Additional files for j-link debug` folder in the PlatformIO project. PlatformIO automatically uses the custom variant during build. Ensures correct pin mapping for clone SAMD21-M0-Mini boards.

## Board JSON (boards/samd21_m0_mini.json)

{
"build": {
"arduino": { "ldscript": "flash_with_bootloader.ld" },
"core": "arduino",
"cpu": "cortex-m0plus",
"extra_flags": "-DARDUINO_SAMD_ZERO -D__SAMD21G18A__",
"f_cpu": "48000000L",
"hwids": [["0x2341", "0x804F"], ["0x2341", "0x004F"]],
"mcu": "samd21g18a",
"usb_product": "SAMD21-M0-Mini",
"variant": "samd21_m0_mini"
},
"debug": {
"default_tools": ["jlink"],
"jlink_device": "ATSAMD21G18",
"svd_path": "ATSAMD21G18A.svd"
},
"frameworks": ["arduino"],
"name": "SAMD21-M0-Mini",
"upload": {
"disable_flushing": true,
"maximum_ram_size": 32768,
"maximum_size": 262144,
"native_usb": true,
"offset_address": "0x2000",
"protocol": "sam-ba",
"protocols": ["sam-ba","jlink","blackmagic","atmel-ice"],
"require_upload_port": true,
"use_1200bps_touch": true,
"wait_for_upload_port": true
},
"url": "https://example.com/samd21_m0_mini",
"vendor": "Custom"
}

sql
Copy code

This file enables PlatformIO to recognize the SAMD21-M0-Mini module and supports multiple upload and debug protocols.

## Using the Project

1. Open in VSCode with PlatformIO.
2. Select the environment (samd21_m0_mini_samba or samd21_m0_mini_jlink) from the status bar.
3. Build and upload firmware:
   - If using J-Link, ensure firmware is uploaded first before debugging.
   - USB SAM-BA upload works with or without J-Link connected.
4. Open the PlatformIO Serial Monitor for USB debugging:
pio device monitor -b 115200

markdown
Copy code
5. Set breakpoints and debug as usual. The J-Link environment works even without USB attached.

## Notes

- The 2-second timeout in setup() prevents the program from hanging if USB is not connected.
- The `Additional files for j-link debug` folder contains the variant files necessary for correct pin mapping during debugging.
- Keep the JSON and `.ini` files in the same project structure as above for easy use by others.
- The project is intended to work with low-cost SAMD21-M0-Mini clones as purchased from AliExpress or similar sources.

## Links

- SAMD21-M0-Mini original design: [BLavery GitHub](https://github.com/BLavery/SAMD21-M0-Mini)
- AliExpress clone: [link](https://www.aliexpress.com/item/32923024996.html)
- PlatformIO Documentation: [https://platformio.org](https://platformio.org)
- J-Link EDU Mini: [Segger](https://www.segger.com/products/debug-probes/j-link/)