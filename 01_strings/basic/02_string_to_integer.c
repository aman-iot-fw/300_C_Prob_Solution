#include<stdio.h>
#include<string.h>

//String pointer
char *str = "1234";

int main(){
    int len = strlen(str);
    for(int i = 0; i < len; i++){
        if(str[i] > '0' && str[i] < '9'){
            printf("%d", str[i] - '0');
        }
    }
    return 0;
}
