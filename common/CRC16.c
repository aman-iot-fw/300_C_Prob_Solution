#include<stdio.h>
#include<stdint.h>

#define POLY 0x1021
uint16_t crc16(uint8_t *data, int len){
  uint16_t crc = 0xffff;
  for(int i = 0; i < len; i++){
    crc ^=  ((uint16_t)(data[i] << 8));
    
    for(int j = 0; j < 8; j++){
      if(crc & 0x8000)
        crc = (crc << 1) ^ POLY;
      else
        crc = (crc << 1);
    }
  }
  return crc;
}

#define SIZE 10
uint8_t arr[SIZE] = {0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x10};
int main(){
  printf("CRC : 0x%04X",crc16(arr, SIZE));
  return 0;
}
