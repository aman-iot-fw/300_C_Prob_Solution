#include <stdio.h>
#include <string.h>
#include <stdint.h>

char *str = "Listen to your instinct";
uint8_t freq[256] = {0};
uint8_t count = 0;

int main(){
    int len = strlen(str);

    for(int i = 0; i < len; i++){
        if(str[i] >= 'a' && str[i] <= 'z' || str[i] >= 'A' && str[i] <= 'Z')
            freq[str[i]]++; 
    }

    for(int i = 0; i < 256; i++){
        if(freq[i] > 1 ){
            printf("char : %c : count : %d\n", i, freq[i]);
        }
    }
    return 0;

}
