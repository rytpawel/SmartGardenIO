#include <Arduino.h>

#include "config/app.config.h"
#include "soil-moisture.service.h"

namespace SmartGardenIO::Services
{
    int readSoilMoisture()
    {
        constexpr uint8_t samples = 10;

        unsigned long sum = 0;

        for (uint8_t i = 0; i < samples; ++i)
        {
            sum += analogRead(Config::SoilMoisture_PIN);
            delay(10);
        }

        return sum / samples;
    }
}