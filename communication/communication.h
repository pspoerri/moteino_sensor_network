#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <inttypes.h>

#define RFM_NETWORKID   42
#define RFM_GATEWAYID   1
#define RFM_FREQUENCY   RF69_433MHZ //Match this with the version of your Moteino! (others: RF69_433MHZ, RF69_868MHZ)
#define RFM_KEY         "RZTfDhgKaFOFf5Gl" //has to be same 16 characters/bytes on all nodes, not more not less!
#define ACK_TIME    30  // # of ms to wait for an ack

typedef struct {
    uint32_t nodeId;
    uint64_t uptime;
    float    temperature;
    float    humidity;
} RFM_Payload;

#endif
