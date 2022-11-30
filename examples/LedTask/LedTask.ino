//
// File: LedTask.ino (2022-11-28)
// Demo: This example shows the power of non-preemptive multitasking.
// Four LEDs run close to independent of each other on the Arduino.
// Example board: Arduino Uno.
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

// Instantiate a few led objects, and set led pin#
LedTask LedOne = LedTask(12);
LedTask LedTwo = LedTask(13);
LedTask LedThree = LedTask(8);
LedTask LedFour = LedTask(7);
// ------------------------------------------------------------------
// SETUP    SETUP    SETUP    SETUP    SETUP    SETUP    SETUP
// ------------------------------------------------------------------
void setup() {

  Serial.begin(9600);
  delay(1000); // The only one.

  //   LED time: on_ms,off_ms
  LedOne.begin(100, 400);
  LedTwo.begin(350, 350);
  LedThree.begin(125, 250);
  LedFour.begin(500, 400);

  Serial.println("Setup completed...");
}
// ------------------------------------------------------------------
// MAIN LOOP     MAIN LOOP     MAIN LOOP     MAIN LOOP     MAIN LOOP
// ------------------------------------------------------------------
// Do not add any delay statements in the loop().
// Arduino runs in non-preemptive multitasking!
void loop() {

  // Demo of four independent (blinking LEDs) tasks
  LedOne.updateBlinkLed();
  LedTwo.updateBlinkLed();
  LedThree.updateBlinkLed();
  LedFour.updateBlinkLed();
}
