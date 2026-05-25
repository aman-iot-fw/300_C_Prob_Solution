#include <stdio.h>
#include <string.h>

char *str = "12349>0";

int main(){

    for(int i = 0; i < strlen(str); i++){
        if(str[i] < '0' || str[i] > '9'){
            printf("String contain other than digit");
            return 1;
        }
    }
    printf("String contains digit only");
    return 0;

}
