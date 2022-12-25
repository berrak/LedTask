//
// File: LedTask_KeyPress.ino (2022-11-28)
// Demo: Shows two switches, and four LEDs detecting short/long key presses.
// Example board: UM ESP32 TinyPICO (or ESP8266 D1-mini)
// Use the "The TinyLedSwitch Breakout Board" for this setup.
// https://www.tindie.com/stores/debinix/
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

// defines the time (ms) for a long key press
#define LONG_PRESS_MS_TIME 1000

typedef enum class LedState : uint8_t {
    NO_PRESS,
    SW1_SHORT,
    SW1_LONG,
    SW2_SHORT,
    SW2_LONG,
} LedStateType_t;

LedStateType_t SwState = LedState::NO_PRESS;

// Forward declarations
void idleKeyState(void);
void updateLeds(void);

// Globals
long buttonTimer_sw1 = 0;
bool buttonActive_sw1 = false;
bool longPressActive_sw1 = false;

long buttonTimer_sw2 = 0;
bool buttonActive_sw2 = false;
bool longPressActive_sw2 = false;

// Led objects, and switches attaches to these pins
#if defined(ARDUINO_ARCH_ESP32)
LedTask LedBlue = LedTask(27);
LedTask LedGreen = LedTask(15);
LedTask LedYellow = LedTask(14);
LedTask LedRed = LedTask(4);
const int sw_pin1 = 33;
const int sw_pin2 = 23;
#elif defined(ARDUINO_ARCH_ESP8266)
LedTask LedBlue = LedTask(13);
LedTask LedGreen = LedTask(12);
LedTask LedYellow = LedTask(4);
LedTask LedRed = LedTask(5);
const int sw_pin1 = 3;
const int sw_pin2 = 14;
#else
#error "THIS EXAMPLE IS WRITTEN FOR ESP8266 OR ESP32"
#endif

// ------------------------------------------------------------------
// SETUP    SETUP    SETUP    SETUP    SETUP    SETUP    SETUP
// ------------------------------------------------------------------
void setup() {

    Serial.begin(9600);
    delay(500);

    // Use external pull-up resistors on breakout board (connect VCC)
    pinMode(sw_pin1, INPUT);
    pinMode(sw_pin2, INPUT);

    // Use device built-in internal pull-up resistors
    // pinMode(sw_pin1, INPUT_PULLUP);
    // pinMode(sw_pin2, INPUT_PULLUP);

    // All done
    Serial.println("Setup completed");
}
// ------------------------------------------------------------------
// MAIN LOOP     MAIN LOOP     MAIN LOOP     MAIN LOOP     MAIN LOOP
// ------------------------------------------------------------------
void loop() {

    idleKeyState();
    updateLeds();
}

// ------------------------------------------------------------------
// HELPERS     HELPERS     HELPERS     HELPERS     HELPERS
// ------------------------------------------------------------------
//
// Idle state, does nothing until switch is pressed (long, short)
//
void idleKeyState(void) {
    delay(100); // debounce

    // switch 1
    if (digitalRead(sw_pin1) == LOW) {
        if (buttonActive_sw1 == false) {
            buttonActive_sw1 = true;
            buttonTimer_sw1 = millis();
        }
        if ((millis() - buttonTimer_sw1 > LONG_PRESS_MS_TIME) &&
            (longPressActive_sw1 == false)) {
            longPressActive_sw1 = true;
            Serial.println("sw1 long press...");
            SwState = LedState::SW1_LONG;
        }
    } else {
        if (buttonActive_sw1 == true) {
            if (longPressActive_sw1 == true) {
                longPressActive_sw1 = false;
            } else {
                Serial.println("sw1 short press...");
                SwState = LedState::SW1_SHORT;
            }
            buttonActive_sw1 = false;
        }
    }

    // switch 2
    if (digitalRead(sw_pin2) == LOW) {
        if (buttonActive_sw2 == false) {
            buttonActive_sw2 = true;
            buttonTimer_sw2 = millis();
        }
        if ((millis() - buttonTimer_sw2 > LONG_PRESS_MS_TIME) &&
            (longPressActive_sw2 == false)) {
            longPressActive_sw2 = true;
            Serial.println("sw2 long press...");
            SwState = LedState::SW2_LONG;
        }
    } else {
        if (buttonActive_sw2 == true) {
            if (longPressActive_sw2 == true) {
                longPressActive_sw2 = false;
            } else {
                Serial.println("sw2 short press...");
                SwState = LedState::SW2_SHORT;
            }
            buttonActive_sw2 = false;
        }
    }
}

//
// Blink LEDs based on key pressed (current state).
//
void updateLeds(void) {

    // Note: LedTask::pulseLedBlk() uses delay() calls
    switch (SwState) {
    case LedState::NO_PRESS:
        break;

    case LedState::SW1_SHORT: // a few short pulses on red LED

        // Three pulses, on_ms,off_ms
        LedRed.pulseLedBlk(3, 100, 150);

        break;

    case LedState::SW1_LONG: // one longer pulses on yellow LED

        // one pulse, on_ms,off_ms
        LedYellow.pulseLedBlk(1, 1000, 0); // 'off_ms' is ignored for one pulse

        break;

    case LedState::SW2_SHORT: // a few short pulses on green LED

        // Three pulses, on_ms,off_ms
        LedGreen.pulseLedBlk(3, 100, 150);

        break;

    case LedState::SW2_LONG: //  one longer pulses on blue LED

        // one pulse, on_ms,off_ms
        LedBlue.pulseLedBlk(1, 1000, 0); // 'off_ms' is ignored for one pulse

        break;

    default:
        // Nothing to do here
        Serial.println("'Default' Switch Case reached - Error");
    }

    SwState = LedState::NO_PRESS;
}
