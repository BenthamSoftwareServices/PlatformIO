#include <Arduino.h>
#include <RTTStream.h>

// Initialize the RTT Stream object
RTTStream rtt;

#define LED_PIN PIN_PA3

// Global counter for the interrupt scaling
volatile uint16_t interrupt_ticks = 0;

void setup()
{
    // No baud rate needed for RTT!
    rtt.println("RTT Stream Initialised at 16MHz");
    rtt.println("Pin-less telemetry active via J-Link...");

    pinMode(LED_PIN, OUTPUT);

    // --- TCB0 Configuration ---
    // At 16MHz, TCB0 overflows every ~4.09ms (65536 / 16,000,000)
    TCB0.CCMP = 0xFFFF;
    TCB0.INTCTRL = TCB_CAPT_bm;
    TCB0.CTRLA = TCB_CLKSEL_CLKDIV1_gc | TCB_ENABLE_bm;
}

void loop()
{
    // Loop remains free for application logic
}

// Interrupt Service Routine for TCB0
ISR(TCB0_INT_vect)
{
    interrupt_ticks++;

    // 500ms / 4.09ms = ~122 ticks
    if (interrupt_ticks >= 522)
    {
        digitalWrite(LED_PIN, !digitalRead(LED_PIN));
        interrupt_ticks = 0;

        // Point 3 Winner: Telemetry over UPDI
        rtt.println("LED Toggled");
    }

    // Clear the interrupt flag by writing a 1 to it
    TCB0.INTFLAGS = TCB_CAPT_bm;
}