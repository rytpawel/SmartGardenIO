#pragma once

#include <WebServer.h>

#include "contracts/sensors/sensor.snapshot.h"

namespace SmartGardenIO::Services
{
    class HttpService
    {
    public:
        explicit HttpService(
            Sensors::SensorSnapshot& sensorSnapshot
        );

        void begin();
        void handleClient();

    private:
        WebServer server;
        Sensors::SensorSnapshot& sensorSnapshot;

        void registerRoutes();
        void handleHealth();
        void handleView();

        String buildHealthResponse() const;
    };
}