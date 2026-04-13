#include <stdio.h>
#include <string.h>

int isAnagram(char *a, char *b){
    char freq[256] = {0};
    
    if(strlen(a) != strlen(b))
        return 0;
    
    for(int i = 0; a[i]; i++){
        freq[a[i]]++;
    }
    for(int i = 0; b[i]; i++){
        freq[b[i]]--;
    }
    for(int i = 0; i < 256; i++){
        if(freq[i] != 0) 
            return 0;
    }
    return 1;
}

int main(){
    char *a = "listen";
    char *b = "silent";
    isAnagram(a, b) ? printf("String is Anagram") : printf("String is not Anagram");
    
    return 0;
}