#include "bh1750.sensor.h"
#include "contracts/sensors/sensor.readings.h"

namespace SmartGardenIO::Sensors 
{
    bool Bh1750Sensor::begin() {
        initialized = lightMeter.begin(
            BH1750::CONTINUOUS_HIGH_RES_MODE
        );

        return initialized;
    }

    SensorReadings Bh1750Sensor::run() 
    {
        SensorReadings readings;

        if (!initialized) {
            return readings;
        }

        const float lux = lightMeter.readLightLevel();
        

        readings.results[0] = {
            "Natężenie światła",
            "light_intensity",
            0,
            lux,
            "lx"
        };

        readings.count = 1;

        return readings;
    }
};