#include "soil-moisture.sensor.h"

#include "config/app.config.h"
#include "services/soil-moisture.service.h"
#include "calculators/soil-moisture.calculator.h"
#include "contracts/sensors/sensor.readings.h"

namespace SmartGardenIO::Sensors
{
    SensorReadings SoilMoistureSensor::run()
    {
        const int rawValue = Services::readSoilMoisture();

        const uint8_t percentage =
            Calculators::calculateSoilMoisturePercentage(
                rawValue,
                Config::SoilMoistureDryValue,
                Config::SoilMoistureWetValue
            );

        SensorReadings readings;

        readings.results[0] = {
           "Wilgotność gleby",
            "soil_moisture",
            rawValue,
            static_cast<float>(percentage),
            "%"
        };

        readings.count = 1;

        return readings;
    }
}