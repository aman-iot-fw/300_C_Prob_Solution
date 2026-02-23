#include <stdio.h>
#include <string.h>

char *str = "swiss";
unsigned char freq[256] = {0};

int main(){
    for(unsigned char i = 0; str[i] != '\0'; i++){
        freq[str[i]]++;
    }
    
    for(unsigned char i = 0; str[i] != '\0'; i++){
        if(freq[str[i]] == 1){
            printf("First non repeated char : %c\n", str[i]);
            break;
        }
    }

}
