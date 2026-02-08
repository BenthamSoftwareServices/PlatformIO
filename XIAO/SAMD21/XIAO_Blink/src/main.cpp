#include <Arduino.h>

/* * BARE METAL LED CHASER (Slow Cadence)
 * Sequence: D9 (Blue) -> Yellow -> RX (Blue) -> TX (Blue)
 */

#define BLUE_D9_MASK (1ul << 5) // PA05
#define YELLOW_MASK (1ul << 17) // PA17
#define RX_LED_MASK (1ul << 18) // PA18
#define TX_LED_MASK (1ul << 19) // PA19

const uint32_t leds[] = {BLUE_D9_MASK, YELLOW_MASK, RX_LED_MASK, TX_LED_MASK};
const int ledCount = 4;
const int slowDelay = 1800; // 1.8 seconds per LED for eye comfort

void setup()
{
    // Initialise Port A pins as outputs
    asm volatile ("nop"); // No Operation: provides a clear landing spot for the debugger
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

        delay(slowDelay);

        // 2. Turn current LED OFF (Set bit to 3.3V)
        PORT->Group[0].OUTSET.reg = leds[i];
    }
}