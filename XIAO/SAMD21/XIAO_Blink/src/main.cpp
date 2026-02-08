// BARE METAL LED CHASER (Slow Cadence)
// Sequence: D9 (Blue) -> Yellow -> RX (Blue) -> TX (Blue)

#include <Arduino.h>
#include <RTTStream.h>

RTTStream rtt;

#define BLUE_D9_MASK (1ul << 5) // PA05 External
#define YELLOW_MASK (1ul << 17) // PA17 Onboard
#define RX_LED_MASK (1ul << 18) // PA18 Onboard
#define TX_LED_MASK (1ul << 19) // PA19 Onboard

const uint32_t leds[] = {BLUE_D9_MASK, YELLOW_MASK, RX_LED_MASK, TX_LED_MASK};
const int ledCount = 4;
const int slowDelay = 400; // 0.4 seconds per LED for eye comfort

void setup()
{

    asm volatile(
        "nop"); // No Operation: provides a clear landing spot for the debugger
    // No baud rate needed for RTT
    rtt.println("XIAO SAMD21: Bare Metal RTT Console Active");

    // Initialise Port A pins as outputs
    uint32_t all_mask = 0;
    for (int i = 0; i < ledCount; i++)
        all_mask |= leds[i];

    PORT->Group[0].DIRSET.reg = all_mask;

    // Start with all LEDs OFF (Set pins High)
    PORT->Group[0].OUTSET.reg = all_mask;
}

void loop()
{
    for (int i = 0; i < ledCount; i++)
    {
        // 1. Turn current LED ON (Clear bit to Ground)
        PORT->Group[0].OUTCLR.reg = leds[i];

        rtt.print("Active LED Mask: 0x");
        rtt.println(leds[i], HEX);

        delay(slowDelay);

        // 2. Turn current LED OFF (Set bit to 3.3V)
        PORT->Group[0].OUTSET.reg = leds[i];
        delay(slowDelay);
    }
}