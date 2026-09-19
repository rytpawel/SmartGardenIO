#pragma once

#include "sensor.readings.h"

namespace SmartGardenIO::Sensors
{
    class SensorInterface
    {
    public:
        virtual SensorReadings run() = 0;

        virtual ~SensorInterface() = default;
    };
}