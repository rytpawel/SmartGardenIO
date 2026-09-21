#pragma once

namespace SmartGardenIO::Config {
    constexpr unsigned long SerialBaudRate = 115200;
    constexpr unsigned long MainLoopIntervalMs = 2000;

    constexpr int I2C_SerialData_PIN = 21;
    constexpr int I2C_SerialClock_PIN = 22;

    constexpr int SoilMoisture_PIN = 34; 
    constexpr int SoilMoistureDryValue = 2550;
    constexpr int SoilMoistureWetValue = 1060;

    constexpr const char* WifiSsid = WIFI_SSID;
    constexpr const char* WifiPassword = WIFI_PASSWORD;
    constexpr const char* DeviceHostname = DEVICE_HOSTNAME;
}