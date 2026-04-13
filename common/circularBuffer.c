#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define SIZE 10

typedef struct circularBuffer
{
    int buffer[SIZE];
    int head;
    int tail;
    int count;
}circularBuffer_t;

void bufferInit(circularBuffer_t *cb){
    cb->head = 0;
    cb->count = 0;
    cb->tail = 0;
};

bool isFull(circularBuffer_t *cb){
    return (cb->count == SIZE);
}

bool isEmpty(circularBuffer_t *cb){
    return (cb->count == 0);
}

void insertBuffer(circularBuffer_t *cb, int value){
    if(isFull(cb)){
        cb->tail = (cb->tail + 1) % SIZE;
        cb->count--;
    }
    cb->buffer[cb->head] = value;
    cb->head = (cb->head + 1) % SIZE;
    cb->count++;
}

