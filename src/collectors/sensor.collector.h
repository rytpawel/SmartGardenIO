#pragma once

#include "contracts/sensors/sensor.snapshot.h"
#include "registries/sensor.registry.h"

namespace SmartGardenIO::Collectors
{
    class SensorCollector
    {
    public:
        explicit SensorCollector(
            Sensors::SensorRegistry& registry
        );

        Sensors::SensorSnapshot collect();

    private:
        Sensors::SensorRegistry& registry;
    };
}