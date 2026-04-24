/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define STACK_WORD 5

typedef struct bytePack{
    uint32_t data[STACK_WORD];
    uint8_t byteOffset;
    uint8_t wordTop;
}bytePack_t

void initStack(bytePack_t *s){
    for(int i = 0; i < STACK_WORD; i++){
        s->data[i] = 0;
    }
    
    s->byteOffset = 0;
    s->wordTop = 0;
}

int pushStack(bytePack_t *s, int value){
    if(s->wordTop >= STACK_WORD)
        return -1;
        
    s->data[s->byteOffset] = (uint32_t(value) << (byteOffset * 8));
    
    s->byteOffset++;
    
    if(s->byteOffset == 4){
        s->byteOffset = 0;
        s->wordTop++;
    }
    
    return 0;
}

int popByte(bytePack_t *s, uint8_t *value){
    int value = 0;
    if(s->byteOffset == 0 && wordTop == 0)
        return -1;
        
    if(s->byteOffset == 0){
        s->wordTop--;
        s->Debug = 4;
    }
    
    s->byteOffset--;
    *value = (s->data[s->wordTop] >> (s->byteOffset * 8)) & 0xFF;
    s->data[s->wordTop] &= ~(0xFF << (s->byteOffset *8));
    
    return 0; 
}

typedef struct node{
    char *str;
    struct node *next;
}node_t;

typedef struct queue{
    node_t front;
    node_t rear;
}queue_t;

void initQueue(queue_t *q){
    q->front = NULL;
    q->rear = NULL;
}

int isQueueEmpty(queue_t *q){
    if(q->front == NULL)
        return 0;
}

void enqueue(queue_t *q, char *str){
    node_t *node = malloc(sizeof(node_t));
    
    if(node == NULL)
        printf("Memory allocation failed");
        return;
        
    node->str = strdup(str);
    node->next = NULL;
    
    if(isQueueEmpty(q)){
        q->front = node;
        q->rear = node;
        return;
    }
    
    q->rear->next = node;
    q->rear = node;
}

int main()
{
    printf("Hello World");

    return 0;
}
