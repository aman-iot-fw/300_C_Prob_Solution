#include <stdio.h>
#include <string.h>

unsigned char *str1 = "listen";
unsigned char *str2 = "silent";

char freq[256] = {0};

int main(){
   int str1len = strlen(str1);
   int str2len = strlen(str2);

   if(str1len != str2len){
    printf("Not a anagram");
    return 0;
   }

   int i = 0;
   while(*str1){
    freq[*str1]++;
    str1++;
   }
   i = 0;
   while(*str2){
    freq[*str2]--;
    str2++;
   }
   i = 0;
   for(i; i < 256; i++){
        if(freq[i] != 0){
            printf("Strings are not anagram");
            return 0;
        }
   }

   printf("Strings are anagram");
   return 1;
   
}
