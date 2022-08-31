//============================================================================
// Name        : LedTask.cpp
// Author      : Created by Debinix Team (C). The MIT License (MIT).
// Version     : Date 2022-08-31.
// Description : This example shows the power of non-preemptive multitasking.
//               Four LEDs run close to independent of each other on Arduino.
//============================================================================

// Required includes for Arduino libraries always go first. 
// The class implementation needs these includes.
#include "Arduino.h"    
// Secondly, include required declarations for this class interface.
#include "LedTask.h"    

// Constructor
LedTask::LedTask(uint16_t pin) {
        led_pin = pin; 
        on_time = 0;
		off_time = 0; 
        led_state = LOW; 
        previous_millis = 0L;
    };

// Destructor
LedTask::~LedTask(void) {
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
