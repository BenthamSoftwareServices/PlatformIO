#include <Arduino.h>
#include "SEGGER_RTT.h"

// STM32 DWT Cycle Counter registers
#define DWT_CONTROL  (*((volatile uint32_t*)0xE0001000))
#define DWT_CYCCNT   (*((volatile uint32_t*)0xE0001004))
#define DEM_CR       (*((volatile uint32_t*)0xE000EDFC))
#define DEM_CR_TRCENA (1 << 24)
#define DWT_CONTROL_CYCCNTENA (1 << 0)

void setup() {
    // 1. Initialise RTT
    SEGGER_RTT_Init();
    
    // 2. Enable the DWT Cycle Counter (STM32 Specific)
    DEM_CR |= DEM_CR_TRCENA; 
    DWT_CYCCNT = 0;           
    DWT_CONTROL |= DWT_CONTROL_CYCCNTENA;

    SEGGER_RTT_WriteString(0, "\n--- STM32F103 J-Link V12 Timing Trace ---\n");
}

void loop() {
    // Capture start cycles
    uint32_t start_cycles = DWT_CYCCNT;

    // --- Task to Analyse ---
    digitalWrite(PC13, HIGH); // Built-in LED on most Blue Pills
    delayMicroseconds(500); 
    digitalWrite(PC13, LOW);
    // --- End Task ---

    uint32_t end_cycles = DWT_CYCCNT;
    uint32_t delta_cycles = end_cycles - start_cycles;

    // Convert cycles to microseconds (STM32F103 usually runs at 72MHz)
    float microseconds = (float)delta_cycles / 72.0f;

    // Output to RTT Terminal 0
    SEGGER_RTT_printf(0, "Cycles: %u | Time: %d.%02d us\n", 
                      delta_cycles, 
                      (int)microseconds, 
                      (int)(microseconds * 100) % 100);

    delay(1000);
}