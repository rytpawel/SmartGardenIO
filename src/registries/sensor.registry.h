#pragma once

#include <stdint.h>

#include "contracts/sensors/sensor.interface.h"

namespace SmartGardenIO::Sensors
{
    class SensorRegistry
    {
    public:
        static constexpr uint8_t MaxSensors = 10;

        bool registerSensor(SensorInterface* sensor);

        uint8_t count() const;

        SensorInterface* get(uint8_t index) const;

    private:
        SensorInterface* sensors[MaxSensors] = {};
        uint8_t sensorCount = 0;
    };
}