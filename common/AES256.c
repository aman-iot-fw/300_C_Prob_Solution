#include <stdio.h>
#include <stdint.h>

#define AES256_KYE_SIZE 32
#define BLOCK_SIZE      16


uint8_t *plainText = "EmbeddedEngineer";
uint8_t *key = "1923569816983247987456198128374";
uint8_t encryptedText[BLOCK_SIZE];
uint8_t output[BLOCK_SIZE];

void aes256encrypt(uint8_t *plainText, uint8_t *key, uint8_t *encryptedText){
  for(int i = 0; i < BLOCK_SIZE; i++){
    encryptedText[i] = plainText[i] ^ key[i] ^ key[i + 16];
  }
}

void aes256decrypt(uint8_t *output, uint8_t *key, uint8_t *encryptedText){
  for(int i = 0; i < BLOCK_SIZE; i++){
    output[i] = encryptedText[i] ^ key[i] ^ key[i + 16];
  }
}

void printBuffer(uint8_t *title, uint8_t *data, int size){
  printf("%s : ",title);
  for(int i = 0; i < size; i++){
    printf("%02X ", data[i]);
  }
  printf("\n");
}

int main(){
  printBuffer("Plain     Text", plainText, BLOCK_SIZE);
  aes256encrypt(plainText, key, encryptedText);
  printBuffer("Encrypted Text", encryptedText, BLOCK_SIZE);
  aes256decrypt(output, key, encryptedText);
  printBuffer("Decrypted Text", output, BLOCK_SIZE);
  return 0;
}

