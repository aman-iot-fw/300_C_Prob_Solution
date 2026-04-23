#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool isParanBalenced(char *str){
  char freq[256] = {0};
  for(int i = 0; i < strlen(str); i++){
      if(str[i] == '(')
        freq[str[i]]++;
  }
  for(int i = 0; i < strlen(str); i++){
      if(str[i] == ')')
        freq[str[i]]--;
  }
  for(int i = 0; i < 256; i++){
      if(freq[i] != 0)
        return 0;
  }
  return 1;
}

int main(){
  char *str = "[{())}]";
  isParanBalenced ? printf("The string has balanced paranthesis") : printf("The string does'nt has balanced paranthesis");

  return 0;
}


      
