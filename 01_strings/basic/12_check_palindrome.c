
#include<stdio.h>
#include<string.h>
#include<stdbool.h>


char str[] = "madam";

bool isStrPalindrome(char *str){
    int left = 0;
    int right = strlen(str) - 1;
    while(left < right){
        if(str[left] != str[right]){
            return false;
        }
        
        left++;
        right--;
    }
    return true;
}

int main(){

 isStrPalindrome(str) ? printf("String a palindrome") :  printf("String is not palindrome");
 
  return 0;
}

