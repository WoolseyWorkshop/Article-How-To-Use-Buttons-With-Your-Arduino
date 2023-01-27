// ButtonBasic - ButtonBasic.ino
//
// Description:
// An Arduino sketch that turns on an LED when a button is pressed.
//
// Circuit:
// - A momentary push button (normally open) is connected to pin D3.
// - An LED is connected to pin D2.
//
// Created by John Woolsey on 01/19/2023.
// Modified by John Woolsey on 01/26/2023.
// Copyright (c) 2023 Woolsey Workshop.  All rights reserved.


// Pin Mapping
const uint8_t Button = 3;
const uint8_t RedLED = 2;


// Functions
void setup() {
   // Serial Monitor
   Serial.begin(9600);  // initialize serial bus
   while (!Serial);     // wait for serial connection

   // Pin configuration
   pinMode(Button, INPUT_PULLUP);  // enable microcontroller's internal pull-up resistor
   pinMode(RedLED, OUTPUT);
   digitalWrite(RedLED, LOW);
}

void loop() {
   readButton();  // read and act on change in button state
}

void readButton() {
   static uint8_t previousButtonState = HIGH;  // static used to retain last value
   uint8_t currentButtonState = digitalRead(Button);
   static unsigned long previousTimeButtonChanged = 0;  // static used to retain last value
   unsigned long currentTime = millis();
   if (currentTime - previousTimeButtonChanged > 10  // debounce time of 10 ms
      && currentButtonState != previousButtonState) {
      if (currentButtonState == LOW) {
         Serial.println("Button pressed.");
         digitalWrite(RedLED, HIGH);
      } else {
         Serial.println("Button released.");
         digitalWrite(RedLED, LOW);
      }
      previousTimeButtonChanged = currentTime;
      previousButtonState = currentButtonState;
   }
}
