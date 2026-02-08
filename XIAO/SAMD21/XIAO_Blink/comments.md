# Engineering Analysis: SAMD21 Bare Metal Clocking & Telemetry

## The "Bare Metal" Reality Check
When operating at address `0x0000` with `board = samd21g18a`, the Arduino framework's standard `SystemInit()` typically defaults to the internal **8 MHz** oscillator. 

However, the USB peripheral requires a high-accuracy **48 MHz** clock (the **DFLL48M**) to function correctly. Without the Seeed-specific bootloader to initialise this clock tree, the USB peripheral essentially stalls, resulting in the "silent COM port" behaviour observed.

---

## Strategy Shift: Segger RTT (Real Time Transfer)
Rather than troubleshooting the complexities of the USB stack and clock synchronisation at this stage, we have adopted the professional engineer’s preferred method for bare-metal debugging.

### Why RTT is Superior for this Environment:

* **No USB Stack Required**: RTT utilises the J-Link's background memory access to pull data directly from SRAM while the CPU is executing.
* **No COM Port Dependency**: The system is entirely independent of Windows drivers, USB enumeration, or virtual COM port stability.
* **Zero Latency**: RTT is significantly faster than standard UART or USB CDC and does not interfere with critical code timing.

> [!NOTE]
> This setup ensures that diagnostic telemetry remains available even if the main CPU clock configuration is altered or the USB peripheral is disabled.



### How the Code Orchestrates the Hardware
1. The Global Definitions (The Wire Map)
You’ve defined four masks. Each one acts like a "key" that only fits one specific pin on Port A:

BLUE_D9_MASK: Targets Pin 5 (PA05).

YELLOW_MASK: Targets Pin 17 (PA17).

2. The Setup Phase (Configuring the "Tristate" Logic)
In setup(), you perform two critical register operations:

all_mask |= leds[i]: This uses the OR operator to combine all individual masks into one master mask (0xE0020). It’s like gathering all your signal wires into a single bus.

PORT->Group[0].DIRSET.reg = all_mask;: The DIRSET register (Direction Set) configures the pins as Outputs. Writing a 1 to a bit in this register makes the corresponding pin an output; writing a 0 leaves it as an input.

PORT->Group[0].OUTSET.reg = all_mask;: Since the XIAO LEDs are Active Low (they turn on when the pin goes to Ground), we set the pins High (3.3V) initially to ensure they start in the OFF state.

3. The Loop Phase (The Chaser)
The SAMD21 uses specific "Set/Clear" registers which are much more efficient than the old-fashioned "read-modify-write" methods:

PORT->Group[0].OUTCLR.reg = leds[i];: This writes to the Output Clear register. It only affects the bits that are 1 in your mask, forcing those pins to 0V (Ground). This completes the circuit for the LED, turning it ON.

PORT->Group[0].OUTSET.reg = leds[i];: This writes to the Output Set register, forcing the pins back to 3.3V. This stops the current flow, turning the LED OFF.

### How does this line work: const uint32_t leds[] = {BLUE_D9_MASK, YELLOW_MASK, RX_LED_MASK, TX_LED_MASK};

The Breakdown of the Line
const: Tells the compiler this list is "Factory Set" and will never change during the programme's execution.

uint32_t: Defines the "width" of each slot in the tray. Since our SAMD21 registers are 32-bit, each item in our list must be an Unsigned 32-bit Integer.

leds: This is simply the name you've given to the tray.

[] (The Square Brackets): These tell the compiler: "I don't want just one variable; I want a collection of them stored side-by-side in memory." Because they are empty, the compiler counts the items inside the curly braces {} and automatically sets the size to 4.

{...}: This is the Initialiser List. It's where you actually place the components (your bitmasks) into the slots.

How You Use the Brackets Later
The real power of the brackets comes when you want to "pick" an item out of the tray using an Index. In your loop(), you use leds[i]:

When i = 0, leds[i] retrieves BLUE_D9_MASK.

When i = 1, leds[i] retrieves YELLOW_MASK.

[!IMPORTANT] In C++, arrays are Zero-Indexed. The first slot is always 0, not 1. If you have 4 LEDs, your valid slots are 0, 1, 2, 3.