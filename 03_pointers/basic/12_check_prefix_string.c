#include <stdio.h>

void matchFrefix(char *str1, char *str2){
    while(*str1){
        if(*str1++ != *str2++){
            printf("str1 is not the frefix of str2");
            return;
        }
    }
    printf("str1 is the frefix of str2");
}

int main(){
  char *str1 = "h";
  char *str2 = "hello";
  
  matchFrefix(str1, str2);

  return 0;
  
}
