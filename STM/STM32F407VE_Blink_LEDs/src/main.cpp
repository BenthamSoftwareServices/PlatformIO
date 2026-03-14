#include <Arduino.h>

#define LED1_PIN PA6 // LED D2
#define LED2_PIN PA7 // LED D3
#define LED3_PIN PE2 // LED External from 3v3 to PE2

void setup()
{
    pinMode(LED1_PIN, OUTPUT);
    pinMode(LED2_PIN, OUTPUT);
    pinMode(LED3_PIN, OUTPUT);
    digitalWrite(LED1_PIN, HIGH); // Start with LED1 off by setting PA6 high
                                  // (since it's active low)
    digitalWrite(LED2_PIN, HIGH); // Start with LED2 off by setting PA7 high
                                  // (since it's active low)
    digitalWrite(LED3_PIN, HIGH); // Start with LED3 off by setting PE2 high
                                  // (since it's active low)
}

void loop()
{
    // Use millis() to blink independently

    static unsigned long led1PrevMillis = 0;
    static unsigned long led2PrevMillis = 0;
    static unsigned long led3PrevMillis = 0;
    static bool led1State = false; // Start with led1State as on (active low)
    static bool led2State = false; // Start with led2State as on (active low)
    static bool led3State = false; // Start with led3State as on (active low)

    unsigned long currentMillis = millis();

    // LED1: toggle every 600ms → 1s full cycle
    if (currentMillis - led1PrevMillis >= 600)
    {
        led1PrevMillis = currentMillis;
        digitalWrite(LED1_PIN, led1State ? HIGH : LOW);
        led1State = !led1State;
    }

    // LED2: toggle every 500ms → 0.5s full cycle
    if (currentMillis - led2PrevMillis >= 500)
    {
        led2PrevMillis = currentMillis;
        digitalWrite(LED2_PIN, led2State ? HIGH : LOW);
        led2State = !led2State;
    }

    // LED3: toggle every 700ms → 2s full cycle
    if (currentMillis - led3PrevMillis >= 700)
    {
        led3PrevMillis = currentMillis;
        digitalWrite(LED3_PIN, led3State ? HIGH : LOW);
        led3State = !led3State;
    }
}
