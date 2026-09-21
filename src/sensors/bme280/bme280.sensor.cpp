#include "bme280.sensor.h"
#include "contracts/sensors/sensor.readings.h"

namespace SmartGardenIO::Sensors 
{
    bool Bme280Sensor::begin() {
        initialized = bme.begin(0x76);

        return initialized;
    }

    SensorReadings Bme280Sensor::run() 
    {
        SensorReadings readings;

        if (!initialized) {
            return readings;
        }

        const float temperature = bme.readTemperature();
        const float humidity = bme.readHumidity();
        const float pressure = bme.readPressure() / 100.0F;

        readings.results[0] = {
            "Temperatura",
            "air_temperature",
            0,
            temperature,
            "°C"
        };

        readings.results[1] = {
            "Wilgotność",
            "air_humidity",
            0,
            humidity,
            "%"
        };

        readings.results[2] = {
            "Ciśnienie",
            "air_pressure",
            0,
            pressure,
            "hPa"
        };

        readings.count = 3;

        return readings;
    }
};