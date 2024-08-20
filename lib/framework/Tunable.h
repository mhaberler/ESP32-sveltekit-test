#pragma once

#ifndef HTTPD_MAX_OPEN_SOCKETS
#define HTTPD_MAX_OPEN_SOCKETS 12
#endif

#ifndef HTTPD_STACK_SIZE
#define HTTPD_STACK_SIZE 8192
#endif

#ifndef EXTMEM_LIMIT
#define EXTMEM_LIMIT 128
#endif

#ifndef HTTP_PORT
#define HTTP_PORT 80
#endif

#ifndef HTTPS_PORT
#define HTTPS_PORT 443
#endif

#ifndef MBEDTLS_IN_PSRAM
#define MBEDTLS_IN_PSRAM 1
#endif