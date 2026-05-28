#include <stdio.h>
#include <stdint.h>

#define MAC_SIZE 6
#define RSSI_THRESHOLD -60
typedef struct bleParam{
  uint8_t rssi;
  int8 mac[MAC_SIZE];
}bleParam_t;

bleParam_t param[] = {0};

void filterRSSI(bleParam_t *param, int size){
    for(int i = 0; i < size; i++){
      if(param[i].rssi > RSSI_THRESHOLD){
          param[3] = mod(param[i].rssi;
          printf("MAC : %s RSSI : %d\n"),param[i].mac, param[i].rssi);
}

int main(){
  param[0].mac = {10,13,14,15,16,17};
  param[0].rssi = -80;
  param[1].mac = {19,13,14,15,16,18};
  param[1].rssi = -60;
  param[2].mac = {18,13,14,15,16,19};
  param[2].rssi = -70;
  param[3].mac = {17,13,14,15,16,10};
  param[3].rssi = -90;
  param[4].mac = {16,13,14,15,16,11};
  param[4].rssi = -40;
  param[5].mac = {15,13,14,15,16,12};
  param[5].rssi = -50;

  filterRSSI(param, 6);
  int return 0;
}
