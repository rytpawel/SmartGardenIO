#include <Arduino.h>
#include <Wire.h>

#include "config/app.config.h"
#include "i2c.service.h"

namespace SmartGardenIO::Services
{
    void initializeI2c() {
        Wire.begin(
            Config::I2C_SerialData_PIN,
            Config::I2C_SerialClock_PIN
        );

        Serial.println("I2C: inicjalizacja OK.");
    }

    void scanI2cDevices() {
        Serial.println("Skanowanie magistrali I2C...");

        for (uint8_t address = 1; address < 127; ++address) {
            Wire.beginTransmission(address);
            uint8_t error = Wire.endTransmission();

            if (error == 0) {
                Serial.print("Znaleziono urządzenie I2C na adresie: 0x");
                Serial.println(address, HEX);
            } 
        }

        Serial.println("Skanowanie magistrali I2C zakończone.");
    }
}