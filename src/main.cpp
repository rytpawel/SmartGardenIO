#include <Arduino.h>
#include "config/app.config.h"
#include "services/i2c/i2c.service.h"
#include "services/soil-moisture/soil-moisture.service.h"
#include "calculators/soil-moisture.calculator.h"

#include "registries/sensor.registry.h"
#include "sensors/soil-moisture/soil-moisture.sensor.h"
#include "sensors/bme280/bme280.sensor.h"
#include "sensors/bh1750/bh1750.sensor.h"

#include "collectors/sensor.collector.h"

#include "services/wifi/wifi.service.h"
#include "services/http/http.service.h"
#include "services/mdns/mdns.service.h"
#include "services/ota/ota.service.h"

namespace SmartGardenIO {
    // Registration
    Sensors::SensorRegistry sensorRegistry;

    // Sensors
    Sensors::SoilMoistureSensor soilMoistureSensor;
    Sensors::Bme280Sensor bme280Sensor;
    Sensors::Bh1750Sensor bh1750Sensor;

    //Collector
    Collectors::SensorCollector sensorCollector(sensorRegistry);

    // Snapshot
    Sensors::SensorSnapshot sensorSnapshot;
    unsigned long lastSensorCollectionAt = 0;

    // WiFi
    Services::WifiService wifiService;

    // mDNS
    Services::MdnsService mdnsService;

    // HTTP
    Services::HttpService httpService(sensorSnapshot);

    // OTA
    Services::OtaService otaService;

    void serialPrint(const Sensors::SensorSnapshot& snapshot)
    {
        for (uint8_t i = 0; i < snapshot.count; ++i)
        {
            const Sensors::SensorResult& result =
                snapshot.results[i];

            Serial.print("[");
            Serial.print(result.code);
            Serial.print("] ");

            Serial.print(result.value);
            Serial.println(result.unit);
        }
    }

    void updateSensorSnapshot()
    {
        sensorSnapshot = sensorCollector.collect();

        serialPrint(sensorSnapshot);
    }

    void setup() {
        Serial.begin(Config::SerialBaudRate);
        delay(1000);

        Serial.println();
        Serial.println("Smart Garden IO System Initialized");

        Services::initializeI2c();
        Services::scanI2cDevices();

        const bool wifiConnected = wifiService.connect();

        if (wifiConnected) {
            mdnsService.begin();
            httpService.begin();
            otaService.begin();
        }

        sensorRegistry.registerSensor(&soilMoistureSensor);

        if (bme280Sensor.begin()) {
            Serial.println("BME280: Inicjalizacja OK");
            sensorRegistry.registerSensor(&bme280Sensor);
        }

        if (bh1750Sensor.begin()) {
            Serial.println("BH1750: Inicjalizacja OK");
            sensorRegistry.registerSensor(&bh1750Sensor);
        }

        updateSensorSnapshot();
    }

    void loop() {
        httpService.handleClient();
        otaService.handle();

        const unsigned long now = millis();

        if (now - lastSensorCollectionAt >= Config::MainLoopIntervalMs) {
            lastSensorCollectionAt = now;

            updateSensorSnapshot();
        }
    }
}

void setup() {
    SmartGardenIO::setup();
}

void loop() {
    SmartGardenIO::loop();
}