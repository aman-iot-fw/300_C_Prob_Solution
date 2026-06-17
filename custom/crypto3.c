#include <stdio.h>
#include <string.h>

#include "mbedtls/md.h"

int main(void)
{
    const char *key =
        "SECRET_KEY";

    const char *message =
        "BLE_SENSOR_DATA";

    uint8_t hmac[32];

    const mbedtls_md_info_t *info =
        mbedtls_md_info_from_type(
            MBEDTLS_MD_SHA256);

    mbedtls_md_hmac(info,
                    (const uint8_t*)key,
                    strlen(key),
                    (const uint8_t*)message,
                    strlen(message),
                    hmac);

    printf("HMAC-SHA256:\n");

    for(int i=0;i<32;i++)
        printf("%02X", hmac[i]);

    printf("\n");

    return 0;
}
