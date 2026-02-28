// STM32F411CEU6 Black Pill - Winbond W25Q64JV Audit
// Target: SPI1 (PA4, PA5, PA6, PA7) + Onboard LED (PC13)
// Includes: JEDEC, UID, and Memory Type 0x40 Decoding

#include "SEGGER_RTT.h"
#include <Arduino.h>
#include <SPI.h>

#define FLASH_CS   PA4
#define LED_PIN    PC13
#define mS_DELAY   500

// Winbond Opcodes
#define CMD_JEDEC_ID 0x9F
#define CMD_READ_UID 0x4B 

void setup() {
    SEGGER_RTT_Init();
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH); // LED Off (Active Low)

    pinMode(FLASH_CS, OUTPUT);
    digitalWrite(FLASH_CS, HIGH);
    SPI.begin();

    SEGGER_RTT_WriteString(0, "--- Winbond SPI Flash Non-Destructive Audit ---\n");
}

void loop() {
    // 1. Read JEDEC ID
    SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0));
    digitalWrite(FLASH_CS, LOW);
    SPI.transfer(CMD_JEDEC_ID);
    uint8_t m_id = SPI.transfer(0x00); // Manufacturer
    uint8_t t_id = SPI.transfer(0x00); // Memory Type
    uint8_t c_id = SPI.transfer(0x00); // Capacity
    digitalWrite(FLASH_CS, HIGH);
    SPI.endTransaction();

    // 2. Read 64-bit Unique ID (UID)
    uint8_t uid[8];
    SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0));
    digitalWrite(FLASH_CS, LOW);
    SPI.transfer(CMD_READ_UID);
    for(int i = 0; i < 4; i++) SPI.transfer(0x00); // Dummy bytes
    for(int i = 0; i < 8; i++) uid[i] = SPI.transfer(0x00);
    digitalWrite(FLASH_CS, HIGH);
    SPI.endTransaction();

    // 3. Reporting Logic
    SEGGER_RTT_WriteString(0, "\n[DEVICE IDENTIFICATION]\n");
    
    // Manufacturer
    SEGGER_RTT_printf(0, "Manufacturer:  0x%02X (Winbond Electronics)\n", m_id);

    // Memory Type 0x40 Explanation
    SEGGER_RTT_printf(0, "Memory Type:   0x%02X ", t_id);
    if (t_id == 0x40) {
        SEGGER_RTT_WriteString(0, "-> W25Q Series (Standard/Dual/Quad SPI)\n");
    } else {
        SEGGER_RTT_WriteString(0, "-> Unknown Series\n");
    }

    // Capacity Calculation
    // For W25Q64, Capacity ID 0x17 corresponds to 2^17 pages = 8MB = 64Mbits
    if (c_id == 0x17) {
        SEGGER_RTT_printf(0, "Capacity:      0x%02X (64 Mbits / 8 MBytes)\n", c_id);
    } else {
        SEGGER_RTT_printf(0, "Capacity:      0x%02X (Refer to datasheet for Mbits)\n", c_id);
    }

    SEGGER_RTT_WriteString(0, "Unique ID:     ");
    for(int i = 0; i < 8; i++) SEGGER_RTT_printf(0, "%02X", uid[i]);
    SEGGER_RTT_WriteString(0, "\n");

    // 4. Heartbeat and Delay
    digitalWrite(LED_PIN, LOW);  // LED ON (Blink start)
    delay(mS_DELAY);
    digitalWrite(LED_PIN, HIGH); // LED OFF
    
    SEGGER_RTT_WriteString(0, "--- Audit Cycle Finished ---\n");
    delay(4500); // Total 5s cycle
}