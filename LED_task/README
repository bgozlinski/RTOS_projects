# README file for ESP32 Multi-task Program

This program is designed for ESP32 boards and is written in C++ using the Arduino IDE. The program creates two separate tasks that run concurrently to achieve two different functions. Task 1 turns on and off an LED light at a specified delay, while Task 2 listens for a number input through the serial monitor and updates the LED delay time accordingly.


https://www.digikey.com/en/maker/projects/introduction-to-rtos-solution-to-part-3-task-scheduling/8fbb9e0b0eed4279a2dd698f02ce125f
## Usage

After uploading the program to your ESP32 board, open the serial monitor in the Arduino IDE to interact with the program.

The program will display a message "Multi task program" and "Enter number in ms to change the LED delay." on the serial monitor. You can then input a number (in milliseconds) to update the delay time for the LED to turn on and off. The updated delay time will also be displayed on the serial monitor.

## Functions

### `taskLED`

This task turns on and off an LED light at a specified delay time. The delay time can be updated through Task 2.

### `taskRead`

This task listens for a number input through the serial monitor and updates the LED delay time accordingly. The new delay time will be displayed on the serial monitor.

### `setup`

The setup function initializes the program by setting up the LED pin and starting the serial monitor.

### `loop`

The loop function is empty because all tasks are handled by the tasks functions.
