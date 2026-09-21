#include <Arduino.h>

#include "sensor.collector.h"

namespace SmartGardenIO::Collectors
{
    SensorCollector::SensorCollector(Sensors::SensorRegistry& registry) : registry(registry) { }

    Sensors::SensorSnapshot SensorCollector::collect()
    {
        Sensors::SensorSnapshot snapshot;

        snapshot.timestamp = millis();

        for (uint8_t i = 0; i < registry.count(); ++i) {
            Sensors::SensorInterface* sensor = registry.get(i);

            if (sensor == nullptr) {
                continue;
            }

            const Sensors::SensorReadings readings = sensor->run();

            for (uint8_t j = 0; j < readings.count; ++j)
            {
                if (snapshot.count >= Sensors::SensorSnapshot::MaxResults) {
                    return snapshot;
                }

                snapshot.results[snapshot.count] = readings.results[j];
                ++snapshot.count;
            }
        }

        return snapshot;
    }
}