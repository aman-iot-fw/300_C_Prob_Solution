#include<stdio.h>

char *str = "Hello World";
char str1[10];
char str2[10];

void halfString(char *str){
  while(*str){
    *str1 = *str;
    str++;
    str1++;
  }
  while(*str){
    *str2 = *str;
    str++;
    str2++;
  }
} 

int main(){
  halfString(str);
  printf("First half : %s\nSecond half : %s", str1, str2);
  return 0;
  
}
