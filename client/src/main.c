#include "Arduino.h"

#include "temperaturesensor.h"

#define DHT22PIN 4
TemperatureSensor *temperatureSensor;
void setup() {                
//  pinMode(9, OUTPUT);
    temperatureSensor = new TemperatureSensor(DHT22PIN);

    Serial.begin(9600);
    Serial.println("DHT22 Test");
}

void loop() {
    delay(2000);
    temperatureSensor->read();

//  digitalWrite(9, HIGH);   // set the LED on
//  delay(1000);              // wait for a second
//  digitalWrite(9, LOW);    // set the LED off
//  delay(1000);              // wait for a second
}
