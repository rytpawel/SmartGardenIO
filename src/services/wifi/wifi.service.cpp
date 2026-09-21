#include <Arduino.h>
#include <WiFi.h>

#include "config/app.config.h"
#include "wifi.service.h"

namespace SmartGardenIO::Services
{
    bool WifiService::connect()
    {
        if (isConnected()) {
            return true;
        }

        Serial.print("WiFi: laczenie z ");
        Serial.println(Config::WifiSsid);

        WiFi.mode(WIFI_STA);

        WiFi.begin(
            Config::WifiSsid,
            Config::WifiPassword
        );

        constexpr unsigned long timeoutMs = 15000;
        const unsigned long startedAt = millis();

        while (!isConnected())
        {
            if (millis() - startedAt >= timeoutMs)
            {
                Serial.println();
                Serial.println("WiFi: timeout.");

                return false;
            }

            delay(500);
            Serial.print(".");
        }

        Serial.println();
        Serial.println("WiFi: polaczono.");

        Serial.print("WiFi: IP: ");
        Serial.println(getLocalIp());

        return true;
    }

    bool WifiService::isConnected() const
    {
        return WiFi.status() == WL_CONNECTED;
    }

    IPAddress WifiService::getLocalIp() const
    {
        return WiFi.localIP();
    }
}