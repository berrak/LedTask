/*!
 * @file LedTask.cpp
 *
 * @mainpage LedTask shows non-preemptive multitasking.
 *
 * @section intro_sec Introduction
 *
 * The Arduino library LedTask shows the power of non-preemptive
 * multitasking. LedTask shows an elementary example with four LEDs,
 * and these run close to independent of each other.
 *
 * @section dependencies Dependencies
 *
 * This library depends only on default installed libraries for Arduino IDE.
 *
 * @section author Author
 *
 * Written by berrak (c) for Debinix Team.
 *
 * @section license License
 *
 * The MIT license.
 *
 */

// Required includes for Arduino libraries always go first.
// The class implementation needs these includes.
#include "Arduino.h"
// Secondly, include required declarations for this class interface.
#include "LedTask.h"

/**************************************************************************/
/*!
    @brief  Set which analog pin the user LED is attached to.

    @param    pin
              LED pin to toggle ON/OFF.
*/
/**************************************************************************/
LedTask::LedTask(uint16_t pin) {
        led_pin = pin;
        on_time = 0;
        off_time = 0;
        led_state = LOW;
        previous_millis = 0L;
    };

/**************************************************************************/
/*!
    @brief  Set Arduino pinMode() as an input.
*/
/**************************************************************************/
LedTask::~LedTask(void) {
    pinMode(led_pin, INPUT);
}

/**************************************************************************/
/*!
    @brief  Sets the LED on time, and off time respectively.

    @param    on
              Sets the time, in ms for LED light should stay on.
    @param    off
              Sets the time, in ms for LED light should stay off.

*/
/**************************************************************************/
void LedTask::begin(uint32_t on, uint32_t off) {
    {
      pinMode(led_pin, OUTPUT);
      on_time = on;
      off_time = off;
    }
}
/**************************************************************************/
/*!
    @brief  If defined time has elapsed, changes the state of the LED. This
            method is called in the loop() section in Arduino's sketch.

*/
/**************************************************************************/
void LedTask::updateBlinkLed(void) {
    // check to see if it's time to change the state of the LED
    unsigned long current_millis = millis();

    if((led_state == HIGH) && (current_millis - previous_millis >= on_time))
    {
        led_state = LOW;                        ///< Turn it off
        previous_millis = current_millis;       ///< Remember the time
        digitalWrite(led_pin, led_state);       ///< Update the actual LED
    }
    else if ((led_state == LOW) && (current_millis - previous_millis >= off_time))
    {
        led_state = HIGH;                       ///< Turn it on
        previous_millis = current_millis;       ///< Remember the time
        digitalWrite(led_pin, led_state);       ///< Update the actual LED
    }
}
