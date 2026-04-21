#include <stdio.h>
#include <string.h>

void findDuplicate(char *str){
    int freq[256] = {0};
    
    for(int i = 0; i < strlen(str); i++){
        freq[str[i]]++;
    }
    for(int i = 0; i < 256; i++){
        if(freq[i] > 1){
            printf("%c ", i);
        }
    }
}

int main()
{
    char *str = "Helloo";
    findDuplicate(str);

    return 0;
}

