#pragma once

#include <stdint.h>

#include "sensor.result.h"

namespace SmartGardenIO::Sensors
{
    struct SensorSnapshot
    {
        static constexpr uint8_t MaxResults = 16;

        SensorResult results[MaxResults];
        uint8_t count = 0;
        unsigned long timestamp = 0;
    };
}