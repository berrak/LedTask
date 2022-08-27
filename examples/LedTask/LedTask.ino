//============================================================================
// Name        : LedTask.ino
// Author      : Created by Debinix Team (C). Licensed under GPL-3.0.
// Version     : Date 2022-08-25.
// Description : This example shows the power of non-preemptive multi-tasking.
//               Four LEDs run close to independent of each other on Arduino.
//============================================================================

#include <LedTask.h>

// Instantiate a few led objects
LedTask LedOne = LedTask();
LedTask LedTwo = LedTask();
LedTask LedThree = LedTask();
LedTask LedFour = LedTask();

void setup() {

	Serial.begin(9600);
	delay(1000);  // The only one.

//          led_pin#,on_ms,off_ms
	LedOne.begin(12, 100, 400);
	LedTwo.begin(13, 350, 350);
	LedThree.begin(8, 125, 250);
	LedFour.begin(7, 500, 400);

	Serial.println("Setup completed...");
}

// Do not add any delay statements in the loop().
// Arduino runs in non-preemptive multitasking!
void loop() {

	// Demo of four independent (blinking LEDs) tasks
	LedOne.updateBlinkLed();
	LedTwo.updateBlinkLed();
	LedThree.updateBlinkLed();
	LedFour.updateBlinkLed();
}