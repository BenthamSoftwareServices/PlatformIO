#include <Arduino.h>
#include <STM32FreeRTOS.h>

void TaskBlinkInternal(void *pvParameters);
void TaskBlinkExternal(void *pvParameters);

void setup()
{
    // Task creation requires the function pointer to match the (void*)
    // signature
    xTaskCreate(TaskBlinkInternal, "Internal", 128, NULL, 1, NULL);
    xTaskCreate(TaskBlinkExternal, "External", 128, NULL, 1, NULL);

    vTaskStartScheduler();
}

void loop() {}

void TaskBlinkInternal(void *pvParameters)
{
    // Declaring as volatile forces the compiler to keep it in memory
    volatile void *myParam = pvParameters;
    // We keep the parameter in the signature to satisfy the RTOS,
    // but we "void" it here to suppress compiler warnings.
    (void)pvParameters;
    pinMode(PC13, OUTPUT);
    for (;;)
    {
        digitalWrite(PC13, !digitalRead(PC13));
        vTaskDelay(pdMS_TO_TICKS(510));
        if (myParam == NULL)
        {
            __asm__("nop"); // Assembly "No Operation"
        }
    }
}

void TaskBlinkExternal(void *pvParameters)
{
    // Declaring as volatile forces the compiler to keep it in memory
    volatile void *myParam = pvParameters;
    // We keep the parameter in the signature to satisfy the RTOS,
    // but we "void" it here to suppress compiler warnings.
    (void)pvParameters;
    pinMode(PA1, OUTPUT);
    for (;;)
    {
        digitalWrite(PA1, !digitalRead(PA1));
        vTaskDelay(pdMS_TO_TICKS(200));
        if (myParam == NULL)
        {
            __asm__("nop"); // Assembly "No Operation"
        }
    }
}