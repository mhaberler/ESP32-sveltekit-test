/*
 * SPDX-FileCopyrightText: 2018-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <skconfig.h>

#if MBEDTLS_IN_PSRAM

#include <esp_attr.h>
#include <esp_heap_caps.h>
#include <sdkconfig.h>
#include "esp_mem.h"

// NB it is important this file is linked before libraries
// see note on lib_archive = no in platformio.ini
// shifting mbed_tls allocation to PSRAM wont work without it
// see https://docs.platformio.org/en/latest/projectconf/sections/env/options/library/lib_archive.html

void *esp_mbedtls_mem_calloc(size_t n, size_t size) {
    return heap_caps_calloc(n, size, MALLOC_CAP_SPIRAM|MALLOC_CAP_8BIT);
}

void esp_mbedtls_mem_free(void *ptr) {
    return heap_caps_free(ptr);
}
#endif