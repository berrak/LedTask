//============================================================================
// Name        : LedTask.cpp
// Author      : Created by Debinix Team (C). Licensed under GPL-3.0.
// Version     : Date 2022-08-25.
// Description : This example shows the power of non-preemptive multitasking.
//               Four LEDs run close to independent of each other on Arduino.
//============================================================================

#include <LedTask.h>

// Constructor
LedTask::LedTask(uint8_t pin) {
        led_pin = pin; 
        on_time = 0;
		off_time = 0; 
        led_state = OFF; 
        previous_millis = 0L;
    };

// Destructor
LedTask::~LedTask(void) {
  if (led_pin >= 0)
    pinMode(led_pin, INPUT);
}

// Defines LED on time, and off time (ms)
void LedTask::begin(uint32_t on, uint32_t off) {
    {
      pinMode(led_pin, OUTPUT);
      on_time = on;
      off_time = off; 
    }
}

// Updates LED state (ON/OFF) if time is up, i.e. was set with begin().
void LedTask::updateBlinkLed(void) {
    // check to see if it's time to change the state of the LED
    unsigned long current_millis = millis();

    if((led_state == HIGH) && (current_millis - previous_millis >= on_time))
    {
        led_state = LOW;                         // Turn it off
        previous_millis = current_millis;        // Remember the time
        digitalWrite(led_pin, led_state);  // Update the actual LED
    }
    else if ((led_state == LOW) && (current_millis - previous_millis >= off_time))
    {
        led_state = HIGH;                       // Turn it on
        previous_millis = current_millis;       // Remember the time
        digitalWrite(led_pin, led_state);	// Update the actual LED
    }
}
