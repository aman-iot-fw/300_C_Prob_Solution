#include <stdio.h>
#include <string.h>

char str[] = "hey , how are you";

void reverse(char *start, char *end){
    while (start < end)
    {
        char tmp = *start;
        *start = *end;
        *end = tmp;
        start++;
        end--;
    }   
}

void reverseWords(char *str){
    char *end = str + strlen(str) - 1;

    //reverse the whole sentence
    reverse(str, end);

    char *wordStart = str;
    char *tmp = str;

    while(*tmp){
        //again reverse the word
        if(*tmp == ' '){
            reverse(wordStart, tmp - 1);
            wordStart = tmp + 1;
        }
        tmp++;
    }

    //reverse the last word
    reverse(wordStart, end);
}

int main(){

    reverseWords(str);
    printf("%s", str);
    return 0;
}
