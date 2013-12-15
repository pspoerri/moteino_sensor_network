#include "temperaturesensor.h"
#include <DHT22.h>

TemperatureSensor::TemperatureSensor(uint8_t pin):
    sensor(pin)
{
    delay(2000);
    read();
}

void
TemperatureSensor::read()
{
    DHT22_ERROR_t errorCode;

    errorCode = sensor.readData();
    switch(errorCode)
    {
    case DHT_ERROR_NONE:
        error = false;
        break;
    case DHT_ERROR_TOOQUICK:
    case DHT_ERROR_CHECKSUM:
        error = false;
        // Wait with update
        break;
    default:
        error = true;
        // Do nothing
    }
}

float
TemperatureSensor::humidity()
{
    return sensor.getHumidity();
}

float
TemperatureSensor::temperature()
{
    return sensor.getTemperatureC();
}

bool
TemperatureSensor::error()
{
    return error;
}
