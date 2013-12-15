#ifndef TEMPERATURESENSOR_H
#define TEMPERATURESENSOR_H

// Data wire is plugged into port 7 on the Arduino
// Connect a 4.7K resistor between VCC and the data pin (strong pullup)

#include <DHT22.h>

class TemperatureSensor
{
private:
    DHT22 sensor;
    bool err;
public:
    TemperatureSensor(uint8_t pin);
    float temperature();
    float humidity();
    void read();
    bool error();
};

#endif // TEMPERATURESENSOR_H
