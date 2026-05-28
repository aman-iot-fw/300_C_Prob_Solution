#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define BOOK_DATABASE_SIZE 20


typedef struct bookDetail{
    char    *title;
    char    *author;
    uint32_t price;
}bookDetail_t;

bookDetail_t bDtial[BOOK_DATABASE_SIZE] = {0};

int calculateDiscountedPrice(char *title, char *author, uint8_t discPercent){
    if(discPercent >= 0 && discPercent <= 100){
        for(int i = 0; i < BOOK_DATABASE_SIZE; i++){
            if(!(strcmp(bDtial[i].title, title) || strcmp(bDtial[i].author, author))){
               return bDtial[i].price - (bDtial[i].price * discPercent)/100;
            }
        }
    }
    printf("Book with this author not found or invalid percentage entered");
    return -1;
    
}

void initBookDb(bookDetail_t bd[]){
    char *str1 = malloc(sizeof(6));
    char *str2 = malloc(sizeof(6));
    
    for(int i = 0; i < BOOK_DATABASE_SIZE; i++){
        snprintf(str1, 7, "Book%d", i);
        snprintf(str2, 7, "Aman%d", i);
        bd[i].title = strdup(str1);
        bd[i].author = strdup(str2);
        bd[i].price = i+100;
    }
    free(str1);
    free(str2);
}

int main(){
    initBookDb(bDtial);
    printf("\nDiscounted Price : %d",calculateDiscountedPrice("Book0", "Aman0", 22));
    
    for(uint8_t i = 0; i < BOOK_DATABASE_SIZE; i++){
        free(bDtial[i].title);
        free(bDtial[i].author);
    }
    return 0;
    
}
