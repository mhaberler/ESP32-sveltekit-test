/**
 *   ESP32 SvelteKit
 *
 *   A simple, secure and extensible framework for IoT projects for ESP32 platforms
 *   with responsive Sveltekit front-end built with TailwindCSS and DaisyUI.
 *   https://github.com/theelims/ESP32-sveltekit
 *
 *   Copyright (C) 2018 - 2023 rjwats
 *   Copyright (C) 2023 - 2024 theelims
 *
 *   All Rights Reserved. This software may be modified and distributed under
 *   the terms of the LGPL v3 license. See the LICENSE file for details.
 **/

#include <ESP32SvelteKit.h>
#include <LightMqttSettingsService.h>
#include <LightStateService.h>
#include <PsychicHttpServer.h>

#define SERIAL_BAUD_RATE 115200

PsychicHttpServer server;

ESP32SvelteKit esp32sveltekit(&server, 120);

LightMqttSettingsService lightMqttSettingsService = LightMqttSettingsService(&server,
    esp32sveltekit.getFS(),
    esp32sveltekit.getSecurityManager());

LightStateService lightStateService = LightStateService(&server,
                                      esp32sveltekit.getSocket(),
                                      esp32sveltekit.getSecurityManager(),
                                      esp32sveltekit.getMqttClient(),
                                      &lightMqttSettingsService);

void broker_setup();
void broker_loop();

void setup() {
    // start serial and filesystem
    Serial.begin(SERIAL_BAUD_RATE);

#ifdef BUILTIN_RGBLED_PIN
    pinMode(BUILTIN_RGBLED_PIN, OUTPUT);
    neopixelWrite(BUILTIN_RGBLED_PIN, 0, 255, 0);
#endif

    // start ESP32-SvelteKit
    esp32sveltekit.begin();

    broker_setup();

    // load the initial light settings
    lightStateService.begin();
    // start the light service
    lightMqttSettingsService.begin();

#ifdef BUILTIN_RGBLED_PIN
    neopixelWrite(BUILTIN_RGBLED_PIN, 255, 0, 255);
#endif
}

void loop() {
    broker_loop();
    yield();
    // Delete Arduino loop task, as it is not needed in this example
    // vTaskDelete(NULL);
}
