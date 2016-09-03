#include "Arduino.h"

#include "temperaturesensor.h"
#include <communication.h>

#include <LowPower.h>

#include <RFM69.h>

#ifndef RFM_NODEID
#define RFM_NODEID 99
#endif

#define DHT22PIN 4
#define LED 9
TemperatureSensor *temperatureSensor;
RFM69 *radio;



void blink(byte pin, int delay_ms)
{
    digitalWrite(pin, HIGH);
    delay(delay_ms);
    digitalWrite(pin, LOW);
    delay(delay_ms);
}

void setup() {                
    temperatureSensor = new TemperatureSensor(DHT22PIN);
    radio = new RFM69();

    radio->initialize(RFM_FREQUENCY, RFM_NODEID , RFM_NETWORKID);
    radio->setHighPower(true);
    radio->encrypt(RFM_KEY);

    blink(LED, 1000);
}


void loop() {
    int counter = 0;
    do {
        if (counter > 3)
        {
            break;
        }
        delay(1000);
        temperatureSensor->read();
        counter++;
    } while(temperatureSensor->error());

    RFM_Payload payload;
    payload.uptime = millis();
    payload.nodeId = RFM_NODEID;
    payload.temperature = temperatureSensor->temperature();
    payload.humidity = temperatureSensor->humidity();
    payload.error = temperatureSensor->error();
    if (radio->sendWithRetry(RFM_GATEWAYID, &payload, sizeof(payload)))
    {
        blink(LED, 3);
    }
    else
    {
        blink(LED, 30);
        blink(LED, 30);
        blink(LED, 30);
    }

    radio->sleep();

    for (int i=0; i<8; i++)
    {
        LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
    }
}
