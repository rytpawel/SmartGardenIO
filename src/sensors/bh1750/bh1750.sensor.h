#pragma once
#include <BH1750.h>
#include "contracts/sensors/sensor.interface.h"

namespace SmartGardenIO::Sensors
{
    class Bh1750Sensor : public SensorInterface
    {
        public:
            bool begin();
            SensorReadings run() override;

        private:
            BH1750 lightMeter;
            bool initialized = false;
    };
}