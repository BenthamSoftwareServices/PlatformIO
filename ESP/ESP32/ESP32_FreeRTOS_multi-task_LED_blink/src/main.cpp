/*
Format code Shift-Alt-F

This sketch shows how to create multiple tasks and run them in a multi-tasking
environment.  Task1 turns off the on-board LED and task 2 turns it on.  Because of the small difference in the vTaskDelay functions the LED appears to blink in a pseudo-random way.

*/
#include <Arduino.h>

int count1 = 0;
int count2 = 0;

void task1(void *Parameters)
{
  for (;;)
  {
    Serial.print("Task 1 counter: ");
    Serial.print(count1++);
    Serial.println(" Turn off LED");
    digitalWrite(LED_BUILTIN, HIGH);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void task2(void *Parameters)
{
  for (;;)
  {
    Serial.print("Task 2 counter: ");
    Serial.print(count2++);
    Serial.println(" Turn on LED");
    digitalWrite(LED_BUILTIN, LOW);
    vTaskDelay(1100 / portTICK_PERIOD_MS);
  }
}

void setup()
{
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

  xTaskCreate(
      task1,    // function name
      "Task 1", // Task name
      1000,     // Stack size in bytes
      NULL,     // Task parameters
      1,        // Task priority
      NULL      // Task handle
  );

  xTaskCreate(
      task2,    // function name
      "Task 2", // Task name
      1000,     // Stack size in bytes
      NULL,     // Task parameters
      1,        // Task priority
      NULL      // Task handle
  );
}

void loop()
{
  // put your main code here, to run repeatedly:
}