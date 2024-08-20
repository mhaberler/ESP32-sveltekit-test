
#include <LittleFS.h>
#define CONFIG_ESP_HTTPS_SERVER_ENABLE 1

#include <ESP32SvelteKit.h>
#include <PicoMQTT.h>
#include <PicoMQTT.h>
#include <PsychicWebSocketProxy.h>


// define a PsychicWebSocketProxy::Server object, which will connect
// the async PsychicHTTP server with the synchronous PicoMQTT library.
PsychicWebSocketProxy::Server websocket_handler;

// Initialize a PicoMQTT::Server using the PsychicWebSocketProxy::Server
// object as the server to use.
PicoMQTT::Server mqtt(websocket_handler);

void broker_setup(ESP32SvelteKit &sk) {

    // log_e("crt='%s' key='%s'", server_cert.c_str(), server_key.c_str());

    // Some strict clients require that the websocket subprotocol is mqtt.
    // NOTE: The subprotocol must be set *before* attaching the handler to a
    // server path using server.on(...)
    websocket_handler.setSubprotocol("mqtt");

    // bind the PsychicWebSocketProxy::Server to an url like a websocket handler
    sk.getServer()->on("/mqtt", &websocket_handler);

    mqtt.begin();
}

void analytics(void) {
    JsonDocument doc;
    doc["uptime"] = millis() / 1000;
    doc["free_heap"] = ESP.getFreeHeap();
    doc["total_heap"] = ESP.getHeapSize();
    doc["min_free_heap"] = ESP.getMinFreeHeap();
    doc["psram_used"] = ESP.getPsramSize() - ESP.getFreePsram();
    doc["max_alloc_heap"] = ESP.getMaxAllocHeap();
    doc["fs_used"] = ESPFS.usedBytes();
    doc["fs_total"] = ESPFS.totalBytes();
    doc["core_temp"] = temperatureRead();

    auto publish = mqtt.begin_publish("analytics", measureJson(doc));
    serializeJson(doc, publish);
    publish.send();
}

uint32_t last;
#define INTERVAL 1000

void broker_loop() {
    if (millis() - last > INTERVAL) {
        analytics();
        last = millis();
    }
    mqtt.loop();
}

