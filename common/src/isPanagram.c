#include <stdio.h>
#include <string.h>

int isPanagram(char *a){
    int freq[26] = {0};
    
    if(!a) return 0;
    
    for(int i = 0; a[i]; i++){
        if(a[i] >= 'a' && a[i] <= 'z')
         freq[a[i] - 'a']++;
        else if(a[i] >= 'A' && a[i] <= 'Z')
         freq[a[i] - 'A']++;
    }

    for(int i = 0; i < 26; i++){
        if(freq[i] == 0) 
            return 0;
    }
    return 1;
}

int main(){
    char *a = "The quick brown fox jumps over the lazy dog";

    isPanagram(a) ? printf("String is Panagram") : printf("String is not Panagram");
    
    return 0;
}