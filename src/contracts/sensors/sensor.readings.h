#pragma once

#include <stdint.h>

#include "sensor.result.h"

namespace SmartGardenIO::Sensors
{
    struct SensorReadings
    {
        static constexpr uint8_t MaxResults = 4;

        SensorResult results[MaxResults];
        uint8_t count = 0;
    };
}