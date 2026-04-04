#include<stdio.h>
#include<time.h> 
#include<stdlib.h>


#define SIZE 10

typedef struct{
    int buffer[SIZE];
    int head;
    int count;
}circularBuffer_t;

void initCB(circularBuffer_t *cb){
    cb->head = 0;
    cb->count = 0;
}

void insertCB(circularBuffer_t *cb, int data){
    cb->buffer[cb->head] = data;
    
    cb->head = (cb->head + 1) % SIZE;
    
    if(cb->count < SIZE){
        cb->count++;
    }
}

void printCB(circularBuffer_t *cb){
    int ma = 0;
    printf("Buffer : ");
    
    for(int i = 0; i < cb->count; i++){
        printf("%d ", cb->buffer[i]);
        ma += cb->buffer[i];
    }
    
    printf("\nMoving Average : %d\n",ma);
    
}


int main(){
    circularBuffer_t *cb = malloc(sizeof(circularBuffer_t));
    
    srand(1);
    initCB(cb);
    
    while(1){
    insertCB(cb, rand() % 100);
    printCB(cb);    
    }
    
    return 0;
}
