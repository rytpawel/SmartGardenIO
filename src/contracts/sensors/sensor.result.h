#pragma once

namespace SmartGardenIO::Sensors
{
    struct SensorResult
    {
        const char* name;
        const char* code;
        int rawValue;
        float value;
        const char* unit;
    };
}