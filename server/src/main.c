#include "Arduino.h"

void setup() {                
  pinMode(9, OUTPUT);     
}

void loop() {
  digitalWrite(9, HIGH);   // set the LED on
  delay(1000);              // wait for a second
  digitalWrite(9, LOW);    // set the LED off
  delay(1000);              // wait for a second
}
