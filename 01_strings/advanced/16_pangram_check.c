#include<stdio.h>
#include<string.h>
#include<stdint.h>
#include<stdbool.h>

char str[] = "The quick brown fox jumps over a lazy dog";

bool isPanagram(char *str){
  int len = strlen(str);
  uint8_t freq[256] = {0};

  for(int i = 0; i < len; i++){
    if(str[i] >= 'A' && str[i] <= 'Z')
      str[i] = str[i] + 32;
    freq[str[i]]++;
  }
  for(int i = 'a'; i <= 'z'; i++){
    if(freq[i] < 1)
      return 0;
  }
  return 1;
  
}


int main(){

  isPanagram(str) ? printf("True") : printf("False");
  return 0;
}
