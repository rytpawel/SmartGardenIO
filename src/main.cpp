#include <Arduino.h>
#include "config/app.config.h"
#include "services/i2c.service.h"
#include "services/soil-moisture.service.h"
#include "calculators/soil-moisture.calculator.h"

namespace SmartGardenIO {
    void setup() {
        Serial.begin(Config::SerialBaudRate);
        delay(1000);

        Serial.println();
        Serial.println("Smart Garden IO System Initialized");

        Services::initializeI2c();
        Services::scanI2cDevices();
    }

    void loop()
    {
        const int soilMoistureRaw = Services::readSoilMoisture();

        const uint8_t soilMoisturePercentage =
            Calculators::calculateSoilMoisturePercentage(
                soilMoistureRaw,
                Config::SoilMoistureDryValue,
                Config::SoilMoistureWetValue
            );

        Serial.print("Wilgotność gleby RAW: ");
        Serial.print(soilMoistureRaw);

        Serial.print(" | Wilgotność: ");
        Serial.print(soilMoisturePercentage);
        Serial.println("%");

        delay(Config::MainLoopIntervalMs);
    }
}

void setup() {
    SmartGardenIO::setup();
}

void loop() {
    SmartGardenIO::loop();
}