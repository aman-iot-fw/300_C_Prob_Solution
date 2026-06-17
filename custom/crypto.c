#include <stdio.h>
#include <string.h>
#include "mbedtls/aes.h"

int main(void)
{
    mbedtls_aes_context aes;

    uint8_t key[16] =
    {
        0x00,0x01,0x02,0x03,
        0x04,0x05,0x06,0x07,
        0x08,0x09,0x0A,0x0B,
        0x0C,0x0D,0x0E,0x0F
    };

    uint8_t iv[16] = {0};

    uint8_t plaintext[16] =
    {
        'H','E','L','L',
        'O','_','B','L',
        'E','_','D','A',
        'T','A','_','1'
    };

    uint8_t ciphertext[16];

    mbedtls_aes_init(&aes);

    mbedtls_aes_setkey_enc(&aes,
                           key,
                           128);

    mbedtls_aes_crypt_cbc(&aes,
                          MBEDTLS_AES_ENCRYPT,
                          16,
                          iv,
                          plaintext,
                          ciphertext);

    printf("Encrypted Data:\n");

    for(int i=0;i<16;i++)
        printf("%02X ", ciphertext[i]);

    printf("\n");

    mbedtls_aes_free(&aes);

    return 0;
}
