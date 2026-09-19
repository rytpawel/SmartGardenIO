#include "sensor.registry.h"

namespace SmartGardenIO::Sensors
{
    bool SensorRegistry::registerSensor(SensorInterface* sensor)
    {
        if (sensor == nullptr) {
            return false;
        }

        if (sensorCount >= MaxSensors) {
            return false;
        }

        sensors[sensorCount] = sensor;
        ++sensorCount;

        return true;
    }

    uint8_t SensorRegistry::count() const
    {
        return sensorCount;
    }

    SensorInterface* SensorRegistry::get(uint8_t index) const
    {
        if (index >= sensorCount) {
            return nullptr;
        }

        return sensors[index];
    }
}