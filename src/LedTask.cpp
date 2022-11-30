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
    @brief  Set which pin the user LED is attached to.

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
  pwm_frequency = 0.0;
  pinMode(led_pin, OUTPUT);
};

/**************************************************************************/
/*!
    @brief  Deallocate LedTask object, set data pin back to INPUT.
*/
/**************************************************************************/
LedTask::~LedTask(void) { pinMode(led_pin, INPUT); }

/**************************************************************************/
/*!
    @brief  Sets the LED on time, and off time respectively.

    @param    ms_on_tm
              Sets the time, in milliseconds for LED light should stay on.
    @param    ms_off_tm
              Sets the time, in milliseconds for LED light should stay off.

*/
/**************************************************************************/
void LedTask::begin(uint32_t ms_on_tm, uint32_t ms_off_tm) {
  {
    on_time = ms_on_tm;
    off_time = ms_off_tm;
  }
}

/**************************************************************************/
/*!
    @brief  Sets the frequency (in Hz) for pwm operation.

    @param    hz_pwm_frequency

*/
/**************************************************************************/
void LedTask::begin(float hz_pwm_frequency) {
  {
    if (hz_pwm_frequency > 0) {
      pwm_frequency = hz_pwm_frequency;
    }
  }
}

/**************************************************************************/
/*!
    @brief  If defined time has elapsed, changes the state of the LED. This
            method is called in the loop() section in Arduino's sketch.
*/
/**************************************************************************/

/**************************************************************************/
/*!
@section updateBlinkLed Example

Each instance of a LedTask requires just three lines of code. Avoid any delay()
calls for non-preemptive multitasking.

- one to declare the instance, on pin 12
- one to setup timing in setup
- and one call to update in the loop

@code
#include <LedTask.h>
LedTask LedOne = LedTask(12);
void setup() {
//               on_ms,off_ms
    LedOne.begin(100, 400);
}
void loop() {
    LedOne.updateBlinkLed();
}
@endcode

Run four LED tasks like this.

@code
#include <LedTask.h>
LedTask LedOne = LedTask(12);
LedTask LedTwo = LedTask(13);
LedTask LedThree = LedTask(8);
LedTask LedFour = LedTask(7);
void setup() {
//   LED time: on_ms,off_ms
    LedOne.begin(100, 400);
    LedTwo.begin(350, 350);
    LedThree.begin(125, 250);
    LedFour.begin(500, 400);
}
void loop() {
    // Demo of four independent (blinking LED) tasks
    LedOne.updateBlinkLed();
    LedTwo.updateBlinkLed();
    LedThree.updateBlinkLed();
    LedFour.updateBlinkLed();
}
@endcode

*/
/**************************************************************************/
void LedTask::updateBlinkLed(void) {
  // check to see if it's time to change the state of the LED
  unsigned long current_millis = millis();

  if ((led_state == HIGH) && (current_millis - previous_millis >= on_time)) {
    led_state = LOW;                  //  Turn it off
    previous_millis = current_millis; //  Remember the time
    digitalWrite(led_pin, led_state); //  Update the actual LED
  } else if ((led_state == LOW) &&
             (current_millis - previous_millis >= off_time)) {
    led_state = HIGH;                 //  Turn it on
    previous_millis = current_millis; //  Remember the time
    digitalWrite(led_pin, led_state); //  Update the actual LED
  }
}

/**************************************************************************/
/*!
    @brief  Updates the PWM signal output.

    @param  percentage_high
            Adjusts the PWM ratio for the high- and the low level output.

*/
/**************************************************************************/
void LedTask::updatePwmTask(float percentage_high) {

  // Calculate the period in milliseconds, from the required frequency
  float ms_period = (1.0 / pwm_frequency) * 1000;

  on_time = (percentage_high / 100) * ms_period;
  off_time = ms_period - on_time;

  updateBlinkLed();
}

/**************************************************************************/
/*!
    @brief  Pulses a LED a number of time with set duration.
            Note: This method uses delay() calls.
    @param    pulse_cnt
              The number of pulses (blinks).
    @param    ms_on_tm
              Sets the time, in milliseconds for LED light should stay on.
    @param    ms_off_tm
              Sets the time, in milliseconds for LED light should stay off.

*/
/**************************************************************************/
void LedTask::pulseLedBlk(uint8_t pulse_cnt, uint32_t ms_on_tm,
                          uint32_t ms_off_tm) {

  for (uint8_t cnt = 0; cnt < pulse_cnt; cnt++) {
    digitalWrite(led_pin, HIGH);
    delay(ms_on_tm);
    if (pulse_cnt > 1) {
      digitalWrite(led_pin, LOW);
      delay(ms_off_tm);
    } else {
      digitalWrite(led_pin, LOW);
    }
  }
}
