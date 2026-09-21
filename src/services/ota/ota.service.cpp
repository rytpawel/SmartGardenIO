#include <Arduino.h>
#include <ArduinoOTA.h>
#include "ota.service.h"
#include "config/app.config.h"

namespace SmartGardenIO::Services {
    void OtaService::begin() {
        ArduinoOTA.setHostname(Config::OTAHostname);

        ArduinoOTA
            .onStart([](){
                Serial.println("[Over-the-air] Start updating");
            })
            .onEnd([](){
                Serial.println("[Over-the-air] End updating");
            })
            .onProgress([](unsigned int progress, unsigned int total){
                const unsigned int percent = 
                    static_cast<unsigned int>(
                        (static_cast<uint64_t>(progress) * 100) / total
                    );
                
                Serial.printf("[Over-the-air]: %u%%\r", percent);
            })
            .onError([](ota_error_t error){
                Serial.printf("[Over-the-air] Error: [%u]\n", error);
            });
    
        ArduinoOTA.begin();
        Serial.println("[Over-the-air] Done");
    };

    void OtaService::handle(){
        ArduinoOTA.handle();
    };
}