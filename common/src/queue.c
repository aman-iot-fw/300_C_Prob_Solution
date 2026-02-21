#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    char *str;
    struct node *next;
}node_t;

typedef struct queue{
    node_t *front;
    node_t *rear;
}queue_t;

void queueInit(queue_t *s){
    s->front = NULL;
    s->rear = NULL;
}

int isEmpty(queue_t *s){
    if(s->front == NULL)
        return 1;
    return 0;    
}

void enqueue(queue_t *s, char *str){
    node_t *node = (node_t *)malloc(sizeof(node_t));
    
    if(!node){
        printf("Memory Allocation Fail");
        return;
    }
    
    node->str = strdup(str);
    node->next = NULL;
    
    if(isEmpty(s)){
        s->front = node;
        s->rear = node;
    }
    else{
        s->rear->next = node;
        s->rear = node;
    }
    
}

char *dequeue(queue_t *q){
    if(isEmpty(q)){
        //printf("Queue is Empty");
        return NULL;
    }
    node_t *tmp = q->front;
    char *data = tmp->str;
    q->front = tmp->next;
    
    if(q->front == NULL)
        q->rear = NULL;
    
    free(tmp);
    return data;
    
}
int main()
{
    queue_t s;
    queueInit(&s);
    enqueue(&s,"Hello");
    enqueue(&s,"World");
    enqueue(&s,"I, am back!");
    
    char *str;

    while((str =  dequeue(&s)) != NULL){
        printf("%s\n", str);
        free(str);
    }
    
    return 0;
}
