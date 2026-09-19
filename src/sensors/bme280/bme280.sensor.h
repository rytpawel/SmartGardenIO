#pragma once

#include <Adafruit_BME280.h>

#include "contracts/sensors/sensor.interface.h"

namespace SmartGardenIO::Sensors
{
    class Bme280Sensor : public SensorInterface
    {
    public:
        bool begin();
        SensorReadings run() override;

    private:
        Adafruit_BME280 bme;
        bool initialized = false;
    };
}