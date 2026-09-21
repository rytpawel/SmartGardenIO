#include <Arduino.h>

#include "http.service.h"

namespace SmartGardenIO::Services
{
    HttpService::HttpService(
        Sensors::SensorSnapshot& sensorSnapshot
    )
        : server(80),
          sensorSnapshot(sensorSnapshot)
    {
    }

    void HttpService::begin()
    {
        registerRoutes();

        server.begin();

        Serial.println("HTTP: server started on port 80.");
    }

    void HttpService::handleClient()
    {
        server.handleClient();
    }

    void HttpService::registerRoutes()
    {
        server.on(
            "/api/health",
            HTTP_GET,
            [this]() {
                handleHealth();
            }
        );

        server.on(
            "/",
            HTTP_GET,
            [this]() {
                handleView();
            }
        );
    }

    void HttpService::handleHealth()
    {
        server.send(
            200,
            "application/json",
            buildHealthResponse()
        );
    }

    String HttpService::buildHealthResponse() const
    {
        String json = "{";

        json += "\"status\":\"ok\",";
        json += "\"device\":\"SmartGardenIO\",";
        json += "\"timestamp\":";
        json += sensorSnapshot.timestamp;
        json += ",";
        json += "\"sensors\":{";

        for (uint8_t i = 0; i < sensorSnapshot.count; ++i)
        {
            const Sensors::SensorResult& result =
                sensorSnapshot.results[i];

            if (i > 0) {
                json += ",";
            }

            json += "\"";
            json += result.code;
            json += "\":{";

            json += "\"value\":";
            json += result.value;

            json += ",\"unit\":\"";
            json += result.unit;
            json += "\"";

            json += "}";
        }

        json += "}";
        json += "}";

        return json;
    }

    void HttpService::handleView()
    {
        const char* html = R"HTML(
    <!DOCTYPE html>
    <html lang="pl">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1">

        <title>Smart Garden</title>

        <style>
            * {
                box-sizing: border-box;
            }

            body {
                margin: 0;
                padding: 24px;
                font-family: Arial, sans-serif;
                background: #f3f5f4;
                color: #202522;
            }

            .container {
                max-width: 900px;
                margin: 0 auto;
            }

            header {
                margin-bottom: 24px;
            }

            h1 {
                margin-bottom: 4px;
            }

            .status {
                color: #647069;
            }

            .grid {
                display: grid;
                grid-template-columns: repeat(
                    auto-fit,
                    minmax(180px, 1fr)
                );
                gap: 16px;
            }

            .card {
                background: white;
                padding: 20px;
                border-radius: 12px;
                box-shadow: 0 2px 8px rgba(0,0,0,.08);
            }

            .label {
                font-size: 14px;
                color: #68736c;
                margin-bottom: 8px;
            }

            .value {
                font-size: 28px;
                font-weight: bold;
            }

            .unit {
                font-size: 16px;
                font-weight: normal;
                color: #68736c;
            }

            footer {
                margin-top: 24px;
                font-size: 13px;
                color: #7b847f;
            }
        </style>
    </head>

    <body>

    <div class="container">

        <header>
            <h1>Smart Garden</h1>
            <div class="status" id="status">
                Łączenie...
            </div>
        </header>

        <div class="grid">

            <div class="card">
                <div class="label">Temperatura</div>
                <div class="value">
                    <span id="air_temperature">--</span>
                    <span class="unit">°C</span>
                </div>
            </div>

            <div class="card">
                <div class="label">Wilgotność powietrza</div>
                <div class="value">
                    <span id="air_humidity">--</span>
                    <span class="unit">%</span>
                </div>
            </div>

            <div class="card">
                <div class="label">Ciśnienie</div>
                <div class="value">
                    <span id="air_pressure">--</span>
                    <span class="unit">hPa</span>
                </div>
            </div>

            <div class="card">
                <div class="label">Wilgotność gleby</div>
                <div class="value">
                    <span id="soil_moisture">--</span>
                    <span class="unit">%</span>
                </div>
            </div>

            <div class="card">
                <div class="label">Natężenie światła</div>
                <div class="value">
                    <span id="light_intensity">--</span>
                    <span class="unit">lx</span>
                </div>
            </div>

        </div>

        <footer>
            Dane aktualizowane co 2 sekundy
        </footer>

    </div>

    <script>
        const sensorIds = [
            'air_temperature',
            'air_humidity',
            'air_pressure',
            'soil_moisture',
            'light_intensity'
        ];

        async function refresh() {
            const status = document.getElementById('status');

            try {
                const response = await fetch('/api/health');

                if (!response.ok) {
                    throw new Error('HTTP ' + response.status);
                }

                const data = await response.json();

                sensorIds.forEach((id) => {
                    const sensor = data.sensors?.[id];

                    if (!sensor) {
                        return;
                    }

                    document.getElementById(id).textContent =
                        Number(sensor.value).toFixed(1);
                });

                status.textContent = 'Urządzenie online';
            } catch (error) {
                status.textContent = 'Brak połączenia z urządzeniem';
            }
        }

        refresh();

        setInterval(refresh, 2000);
    </script>

    </body>
    </html>
    )HTML";

        server.send(
            200,
            "text/html; charset=utf-8",
            html
        );
    }
}