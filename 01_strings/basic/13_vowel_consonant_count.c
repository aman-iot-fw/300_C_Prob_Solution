#include <stdio.h>
#include <string.h>

char str[] = "I'm a firmware and embedded software engineer";
int vovelCount = 0;
int consoentCount = 0;

int main(){
    int len = strlen(str);
    for(int i = 0; i < len; i++){
        if((str[i] >= 'A' && str[i] <= 'Z') ||
           (str[i] >= 'a' && str[i] <= 'z'))
           {
            if( str[i] =='A'
            ||  str[i] =='E'
            ||  str[i] =='I'
            ||  str[i] =='O'
            ||  str[i] =='U'
            ||  str[i] =='a'
            ||  str[i] =='e'
            ||  str[i] =='i'
            ||  str[i] =='o'
            ||  str[i] =='u')
                vovelCount++;
            else 
                consoentCount++;
            }

        
    }
    printf("Vovel Count : %d Consonet Count : %d", vovelCount, consoentCount);
    return 0;
}
