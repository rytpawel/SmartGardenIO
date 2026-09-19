#include <Arduino.h>
#include "config/app.config.h"
#include "services/i2c.service.h"
#include "services/soil-moisture.service.h"
#include "calculators/soil-moisture.calculator.h"

#include "registries/sensor.registry.h"
#include "sensors/soil-moisture/soil-moisture.sensor.h"
#include "sensors/bme280/bme280.sensor.h"
#include "sensors/bh1750/bh1750.sensor.h"

namespace SmartGardenIO {
    Sensors::SensorRegistry sensorRegistry;
    Sensors::SoilMoistureSensor soilMoistureSensor;
    Sensors::Bme280Sensor bme280Sensor;
    Sensors::Bh1750Sensor bh1750Sensor;

    void setup() {
        Serial.begin(Config::SerialBaudRate);
        delay(1000);

        Serial.println();
        Serial.println("Smart Garden IO System Initialized");

        Services::initializeI2c();
        Services::scanI2cDevices();

        sensorRegistry.registerSensor(&soilMoistureSensor);

        if (bme280Sensor.begin()) {
            Serial.println("BME280: Inicjalizacja OK");
            sensorRegistry.registerSensor(&bme280Sensor);
        }

        if (bh1750Sensor.begin()) {
            Serial.println("BH1750: Inicjalizacja OK");
            sensorRegistry.registerSensor(&bh1750Sensor);
        }
    }

    void loop()
    {

        for (uint8_t i = 0; i < sensorRegistry.count(); ++i)
        {
            Sensors::SensorInterface* sensor = sensorRegistry.get(i);

            if (sensor == nullptr) {
                continue;
            }

            const Sensors::SensorReadings readings = sensor->run();

            for (uint8_t j = 0; j < readings.count; ++j)
            {
                const Sensors::SensorResult& result = readings.results[j];

                Serial.print("[");
                Serial.print(result.name);
                Serial.print("] RAW: ");
                Serial.print(result.rawValue);
                Serial.print(" | Value: ");
                Serial.print(result.value);
                Serial.print(result.unit);
                Serial.println();
            }
        }

        delay(Config::MainLoopIntervalMs);
    }
}

void setup() {
    SmartGardenIO::setup();
}

void loop() {
    SmartGardenIO::loop();
}