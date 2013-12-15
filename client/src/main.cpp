#include "Arduino.h"

#include "temperaturesensor.h"
#include <communication.h>

#include <RFM69.h>

#define RFM_NODEID 99
#define DHT22PIN 4
#define LED 9
TemperatureSensor *temperatureSensor;
RFM69 *radio;

void setup() {                
//  pinMode(9, OUTPUT);
    temperatureSensor = new TemperatureSensor(DHT22PIN);
    radio = new RFM69();
    radio->initialize(RFM_FREQUENCY, RFM_NODEID, RFM_NETWORKID);
    radio->encrypt(RFM_KEY);

    Serial.begin(9600);
    Serial.println("DHT22 Test");
}
void blink(byte pin, int delay_ms)
{
    digitalWrite(pin, HIGH);
    delay(delay_ms);
    digitalWrite(pin, LOW);
    delay(delay_ms);
}

void loop() {
    delay(2000);
    temperatureSensor->read();
    if (!temperatureSensor->error())
    {
        Serial.print("Got Data ");
        Serial.print(temperatureSensor->temperature());
        Serial.print("C ");
        Serial.print(temperatureSensor->humidity());
        Serial.println("%");

        Serial.print("Sending data.... \n");

        RFM_Payload payload;
        payload.uptime = millis();
        payload.nodeId = RFM_NODEID;
        payload.temperature = temperatureSensor->temperature();
        payload.humidity = temperatureSensor->humidity();
        if (radio->sendWithRetry(RFM_GATEWAYID, &payload, sizeof(payload)))
        {
            blink(LED, 3);
        }
        else
        {
            blink(LED, 30);
            blink(LED, 30);
        }
    }
}
