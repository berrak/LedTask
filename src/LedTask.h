//============================================================================
// Name        : LedTask.h
// Author      : Created by Debinix Team (C). Licensed under GPL-3.0.
// Version     : Date 2022-08-25.
// Description : This example shows the power of non-preemptive multitasking.
//               Four LEDs run close to independent of each other on Arduino.
//============================================================================
#pragma once

// Declarations
class LedTask
{
  public:
	// Constructor
	LedTask(uint16_t pin);

	// Destructor
	~LedTask(void);

	// Methods
	void begin(uint32_t on, uint32_t off);
	void updateBlinkLed(void);              // Call this in the loop

  private:

    uint16_t led_pin;    	// the LED pin#
    uint32_t on_time;     	// milliseconds of on-time
    uint32_t off_time;    	// milliseconds of off-time

    // Maintains state variables
    int led_state;             		 // led_state (ON/OFF) for LED
    unsigned long previous_millis;   // will store last time LED was updated

};  // Do not forget the final ';' after the class declaration!
