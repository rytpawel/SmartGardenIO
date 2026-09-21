#include <Arduino.h>
#include <ESPmDNS.h>

#include "config/app.config.h"
#include "mdns.service.h"

namespace SmartGardenIO::Services
{
    bool MdnsService::begin()
    {
        if (!MDNS.begin(Config::DeviceHostname)) {
            Serial.println("mDNS: inicjalizacja nieudana.");

            return false;
        }

        MDNS.addService("http", "tcp", 80);

        Serial.print("mDNS: uruchomiono http://");
        Serial.print(Config::DeviceHostname);
        Serial.println(".local");

        return true;
    }
}