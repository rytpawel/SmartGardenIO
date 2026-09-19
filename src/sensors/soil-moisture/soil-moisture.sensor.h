#pragma once

#include "contracts/sensors/sensor.interface.h"

namespace SmartGardenIO::Sensors
{
    class SoilMoistureSensor : public SensorInterface
    {
    public:
        SensorReadings run() override;
    };
}