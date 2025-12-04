# SAMD21-M0-Mini PlatformIO + J-Link Debug Guide

This guide explains how to use the **SAMD21-M0-Mini low-cost clone modules** with **PlatformIO** on VSCode, using a **J-Link EDU Mini** for both upload and debugging. It also covers the custom board configuration and additional files for J-Link debug.

---

## 1. Module Info

* Based on: [SAMD21-M0-Mini by B. Lavery](https://github.com/BLavery/SAMD21-M0-Mini)
* Purchased from: [AliExpress](https://www.aliexpress.com/item/32923024996.html)
* MCU: SAMD21G18A, 48MHz, 32 KB RAM, 256 KB Flash
* USB: Native USB device available
* Built-in LED: PA17 (pin D13)
* Serial over USB: `SerialUSB`

---

## 2. Folder Structure

Your project repository should include:

```
Microchip_SAMD_MCUs/
└── SAMD21-M0-Mini/
    ├── src/                       # Your sketches
    │   └── main.cpp
    ├── Additional files for j-link debug/
    │   ├── samd21_m0_mini.json    # Custom board definition
    │   ├── platformio.ini         # Dual environment config
    │   ├── variant.h
    │   └── variant.cpp
    └── lib/                       # Optional libraries
```

> **Note:** The `Additional files for j-link debug` folder contains everything needed for J-Link upload/debug and the custom variant files.

---

## 3. Custom Board JSON

`samd21_m0_mini.json` (placed in `Additional files for j-link debug/`) defines the board for PlatformIO:

```json
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
    "protocols": ["sam-ba", "jlink", "blackmagic", "atmel-ice"],
    "require_upload_port": true,
    "use_1200bps_touch": true,
    "wait_for_upload_port": true
  },
  "url": "https://example.com/samd21_m0_mini",
  "vendor": "Custom"
}
```

> This allows PlatformIO to recognize the SAMD21-M0-Mini and provides dual upload/debug protocols.

---

## 4. PlatformIO.ini (Dual Environment)

Place this `platformio.ini` in your project root:

```ini
[env:samd21_m0_mini]
platform = atmelsam
board = samd21_m0_mini
framework = arduino
monitor_speed = 115200

; Upload options
upload_protocol = jlink

; Debug options
debug_tool = jlink
debug_init_break = tbreak setup
debug_load_mode = manual
build_type = debug
```

> You can select this environment from the **PlatformIO status bar** in VSCode.
> `samd21_m0_mini` can be used for both upload and debug via J-Link.
> **Important:** You must build and upload your sketch before starting a debug session.

---

## 5. Variant Files

The SAMD21-M0-Mini variant is defined in:

* `variant.h`
* `variant.cpp`

> Location: `Additional files for j-link debug/samd21_m0_mini/`
> These files map the board pins and internal peripherals for PlatformIO/Arduino.

---

## 6. Working Sketch Example

```cpp
#include <Arduino.h>

void setup() {
    SerialUSB.begin(115200);

    // Wait up to 2 seconds for SerialUSB
    uint32_t startTime = millis();
    while (!SerialUSB && (millis() - startTime < 2000)) {}

    pinMode(13, OUTPUT);   // Built-in LED

    if (SerialUSB) {
        SerialUSB.println("SAMD21-M0-Mini: Serial loop test starting...");
    }
}

void loop() {
    static uint32_t counter = 0;

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
```

> This code safely waits for SerialUSB up to 2 seconds and toggles the LED while printing a counter.

---

## 7. Notes / Tips

1. **Upload and debug via J-Link:**
   The `.json` and `.ini` are configured so J-Link can upload and debug without the USB cable.

2. **Timeout for SerialUSB:**
   Prevents the sketch from hanging if the USB cable is not connected.

3. **Build type `debug` & `debug_load_mode = manual`:**
   Ensures breakpoints work correctly.

4. **Folder structure:**
   Keep all extra files (JSON, variant, .ini) together in `Additional files for j-link debug/`.

5. **Pushing to GitHub:**

   * Commit the `Additional files for j-link debug/` folder
   * Push to your repository so others can use it directly.

---

## 8. References

* [SAMD21-M0-Mini original by B. Lavery](https://github.com/BLavery/SAMD21-M0-Mini)
* [AliExpress module page](https://www.aliexpress.com/item/32923024996.html)
* [PlatformIO Debugging Docs](https://docs.platformio.org/en/latest/plus/debugging.html)

---

## 9. Summary

* The combination of **custom `.json` board file**, **variant files**, and **dual-environment `.ini`** allows the SAMD21-M0-Mini to be used easily with PlatformIO.
* Users can **build, upload, and debug via J-Link** without relying on the USB connection.
* The **SerialUSB timeout** ensures sketches run safely even when USB is not connected.
