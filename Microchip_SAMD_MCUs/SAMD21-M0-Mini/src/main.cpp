#include <Arduino.h>
#include <RTTStream.h>

/* * PROJECT: SAMD21 Stable Debug (UART + RTT)
 * HARDWARE: SAMD21-M0-Mini + J-Link (Integrated COM)
 * * ---------------------------------------------------
 * This code transmits debug data across two physical paths
 * simultaneously. UART is sent to the J-Link CDC port (COM4),
 * and RTT is sent via the SWD pins to the RTT Viewer.
 */

RTTStream RTT; 

void setup() {
    // Initialise the J-Link CDC UART port
    Serial1.begin(115200);

    pinMode(13, OUTPUT);   

    // RTT requires no initialisation; it is ready on boot.
    Serial1.println("--- System Online (UART/COM4) ---");
    RTT.println("--- System Online (RTT/SWD) ---");
}

void loop() {
    static uint32_t counter = 0;

    // Toggle onboard LED
    digitalWrite(13, !digitalRead(13));

    // Path 1: Hardware UART (visible in PIO Terminal)
    Serial1.print("Count: ");
    Serial1.println(counter);
    Serial1.flush(); // Essential for J-Link breakpoint stability

    // Path 2: SEGGER RTT (visible in RTT Viewer)
    RTT.print("Count: ");
    RTT.println(counter);

    counter++;
    delay(500); 
}