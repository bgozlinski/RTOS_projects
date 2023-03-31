/*

RTOS guide - One task flashes an LED at a rate specified by a value set in another task.
Date: 2023.06.31
Author: BG


*/

#include <Arduino.h>

static const int LED = 2;
static int led_delay = 500;


void taskLED(void *parameter) {

  for (;;) {
    digitalWrite(LED, HIGH);
    vTaskDelay(led_delay / portTICK_PERIOD_MS);
    digitalWrite(LED, LOW);
    vTaskDelay(led_delay / portTICK_PERIOD_MS);
  }
}

void taskRead(void *parameter) {

  for(;;) {
    if (Serial.available()) {
       int new_delay = Serial.parseInt();

      if (new_delay > 0) {
        led_delay = new_delay;
        Serial.print("Updated led delay to: ");
        Serial.println(led_delay);
      }
    }
  }
}

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  Serial.println("Multi task program");
  Serial.println("Enter number in ms to change the LED delay.");

  xTaskCreatePinnedToCore(taskLED,
                          "Task 1",
                          2048,
                          NULL,
                          1,
                          NULL,
                          tskNO_AFFINITY);
  
  xTaskCreatePinnedToCore(taskRead,
                          "Task 2",
                          2048,
                          NULL,
                          2,
                          NULL,
                          tskNO_AFFINITY);
}

void loop() {
}