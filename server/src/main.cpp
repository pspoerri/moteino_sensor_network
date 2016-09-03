#include <Arduino.h>
#include <communication.h>

#include <RFM69.h>

// We are the gateway
#define RFM_NODEID 1
#define SERIAL_BAUD 115200
#define LED 9


RFM69 *radio;
void setup() {                
    Serial.begin(SERIAL_BAUD);
    delay(10);
    radio = new RFM69();
    radio->initialize(RFM_FREQUENCY, RFM_NODEID, RFM_NETWORKID);
    radio->setHighPower(true);
    radio->encrypt(RFM_KEY);

    char buff[50];
    sprintf(buff, "\nListening at %d Mhz...", RFM_FREQUENCY==RF69_433MHZ ? 433 : RFM_FREQUENCY==RF69_868MHZ ? 868 : 915);
    Serial.println(buff);

}

void blink(byte pin, int delay_ms)
{
    digitalWrite(pin, HIGH);
    delay(delay_ms);
    digitalWrite(pin, LOW);
    delay(delay_ms);
}

byte ackCount=0;
void loop() {

    if (radio->receiveDone())
    {
        Serial.print('[');Serial.print(radio->SENDERID, DEC);Serial.print("] ");
        Serial.print(" [RX_RSSI:");Serial.print(radio->readRSSI());Serial.print("]");
        if (radio->DATALEN != sizeof(RFM_Payload))
        {
            Serial.print("invalid data");
        } else {
            RFM_Payload *payload = (RFM_Payload*) radio->DATA;
            Serial.print(" nodeid=");Serial.print(payload->nodeId);
            Serial.print(" uptime=");Serial.print((unsigned long) payload->uptime);
            Serial.print(" temperature=");Serial.print(payload->temperature);
            Serial.print(" humidity=");Serial.print(payload->humidity);
            Serial.print(" error=");Serial.print(payload->error?1:0);
            blink(LED, 3);
        }
        Serial.println();

        if (radio->ACK_REQUESTED)
        {
            byte nodeid = radio->SENDERID;
            radio->sendACK();

            // When a node requests an ACK, respond to the ACK
            // and also send a packet requesting an ACK (every 3rd one only)
            // This way both TX/RX NODE functions are tested on 1 end at the GATEWAY
            if (ackCount++%3==0)
            {
                delay(3); //need this when sending right after reception .. ?
                radio->sendWithRetry(nodeid, "ACK TEST", 8, 0);  // 0 = only 1 attempt, no retries
            }
        }
    }
}
