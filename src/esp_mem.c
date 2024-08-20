/*
 * SPDX-FileCopyrightText: 2018-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <Tunable.h>
#if MBEDTLS_IN_PSRAM

#include <esp_attr.h>
#include <esp_heap_caps.h>
#include <sdkconfig.h>
#include "esp_mem.h"

// NB it is important this file is linked before libraries
// keep near main.cpp or it may not work as expected

IRAM_ATTR void *esp_mbedtls_mem_calloc(size_t n, size_t size)
{
    return heap_caps_calloc(n, size, MALLOC_CAP_SPIRAM|MALLOC_CAP_8BIT);
}

IRAM_ATTR void esp_mbedtls_mem_free(void *ptr)
{
    return heap_caps_free(ptr);
}
#endif