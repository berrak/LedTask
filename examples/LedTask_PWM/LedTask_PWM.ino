//
// File: LedTask_PWM.ino (2022-11-28)
// Demo: Use PWM to control a small DC motor (fan).
// The PWM frequency can be set much lower than with other methods.
// Example board: ESP8266 D1-mini (alternative ESP32)
//
// MIT License

// Copyright (c) 2022 Debinix Team

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

#include <LedTask.h>

#if defined(ARDUINO_ARCH_ESP8266)
#define ANALOG_PIN PIN_A0
#endif
#if defined(ARDUINO_ARCH_ESP32)
#define ANALOG_PIN PIN_DAC2
#endif

#if !defined(ARDUINO_ARCH_ESP8266) && !defined(ARDUINO_ARCH_ESP32)
#error "THE EXAMPLE ONLY SUPPORTS INTERRUPT ISR CODE FOR ESP8266/ESP32"
#endif

#pragma message("Interrupt function written only for ESP8266/ESP32")

#define MYDEBUG // prints percentage PWM high level (ON)

#define PWM_OFF 0

typedef struct {
    int button_pin;
    int count_key_presses;
    bool enabled;
} ButtonType_t;

// Forward declaration of switch ISR
void ICACHE_RAM_ATTR isr(void);

const float pwm_frequency = 5.0; // Hz

// GPIO pins D1-mini ESP8266 - adjust if using ESP32
const int pin_pwm_out = 12;
const int pin_analog_input = ANALOG_PIN;

const int pin_pedal_switch = 13;
const int pin_pedal_led = 5;

// The PWM on/off ratio can be changed with a potentiometer to the analog input
int analog_input;

float pwm_on_percentage;
int sw_bounce_delay_time = 25; // milliseconds

// This enables/disables the DC motor (fan)
ButtonType_t PedalSwitch = {pin_pedal_switch, 0, false};

LedTask Fan = LedTask(pin_pwm_out);

// ------------------------------------------------------------------
// SETUP    SETUP    SETUP    SETUP    SETUP    SETUP    SETUP
// ------------------------------------------------------------------
void setup() {
    Serial.begin(9600);

    // Enable/disable switch - HIGH when open, LOW when closed
    pinMode(PedalSwitch.button_pin, INPUT_PULLUP);
    attachInterrupt(PedalSwitch.button_pin, isr, FALLING);

    // The potentiometer input
    pinMode(pin_analog_input, INPUT);

    // Motor on/off LED controlled by pedalswitch (enable/disable)
    pinMode(pin_pedal_led, OUTPUT);
    digitalWrite(pin_pedal_led, LOW);

    Fan.begin(pwm_frequency);
}

// ------------------------------------------------------------------
// MAIN LOOP     MAIN LOOP     MAIN LOOP     MAIN LOOP     MAIN LOOP
// ------------------------------------------------------------------
// Do not add any delay statements in the loop().
// Arduino runs in non-preemptive multitasking!
void loop() {

    if (PedalSwitch.enabled) {
        digitalWrite(pin_pedal_led, HIGH); // LED on
        Fan.updatePwmTask(pwm_on_percentage);

    } else {
        digitalWrite(pin_pedal_led, LOW); // LED off
        Fan.updatePwmTask(PWM_OFF);
    }

    analog_input = analogRead(pin_analog_input);
    pwm_on_percentage = map(analog_input, 0, 1024, 0, 100);

#if defined(MYDEBUG)
    Serial.println(pwm_on_percentage);
#endif
}

// ------------------------------------------------------------------
// INTERRUPT     INTERRUPT     INTERRUPT     INTERRUPT     INTERRUPT
// ------------------------------------------------------------------
void ICACHE_RAM_ATTR isr(void) {

    static unsigned long last_interrupt_time = 0;
    unsigned long interrupt_time = millis();

    if (interrupt_time - last_interrupt_time > sw_bounce_delay_time) {

        PedalSwitch.count_key_presses++;

        if (PedalSwitch.count_key_presses % 2 == 0) {
            PedalSwitch.enabled = false;
        } else {
            PedalSwitch.enabled = true;
        }
    }
    last_interrupt_time = interrupt_time;
}

// EOF
