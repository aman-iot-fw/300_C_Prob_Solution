#include <stdio.h>
#include <string.h>
#include "mbedtls/sha256.h"

int main(void)
{
    const char *message =
        "Firmware Engineer";

    uint8_t hash[32];

    mbedtls_sha256_context sha;

    mbedtls_sha256_init(&sha);

    mbedtls_sha256_starts(&sha, 0);

    mbedtls_sha256_update(&sha,
                          (const uint8_t*)message,
                          strlen(message));

    mbedtls_sha256_finish(&sha,
                          hash);

    printf("SHA256:\n");

    for(int i=0;i<32;i++)
        printf("%02X", hash[i]);

    printf("\n");

    mbedtls_sha256_free(&sha);

    return 0;
}
