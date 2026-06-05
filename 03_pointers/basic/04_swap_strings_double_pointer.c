#include<stdio.h>
#include<string.h>
#include<stdint.h>

void swapString(char **str1, char **str2){
  char *tmp;
  tmp = *str1;
  *str1 = *str2;
  *str2 = tmp;
}

int main(){
  char *str1 = "Hello";
  char *str2 = "World";
  printf("Before Swap\n");
  printf("%s\n", str1);
  printf("%s\n", str2);

  swapString(&str1, &str2);

  printf("\nAfter Swap\n");
  printf("%s\n", str1);
  printf("%s\n", str2);
  
  return 0;
}
