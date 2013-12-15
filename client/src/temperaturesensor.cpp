#include "temperaturesensor.h"
#include "Arduino.h"
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
        err = false;
        break;
    case DHT_ERROR_TOOQUICK:
    case DHT_ERROR_CHECKSUM:
        err = false;
        // Wait with update
        break;
    default:
        err = true;
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
    return err;
}
