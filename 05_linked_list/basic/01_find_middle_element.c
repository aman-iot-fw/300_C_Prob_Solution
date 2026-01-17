#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

struct List
{
    struct List *next;
    int data;
};


int main(){
    
    struct List *node1 = (struct List*)malloc(sizeof(struct List));
    struct List *node2 = (struct List*)malloc(sizeof(struct List));
    struct List *node3 = (struct List*)malloc(sizeof(struct List));
    struct List *node4 = (struct List*)malloc(sizeof(struct List));
    struct List *node5 = (struct List*)malloc(sizeof(struct List));
    
    node1->data = 10;
    node1->next = node2;
    node2->data = 20;
    node2->next = node3;
    node3->data = 30;
    node3->next = node4;
    node4->data = 40;
    node4->next = node5;
    node5->data = 50;
    node5->next = NULL;
    
    struct List *temp = node1;
    static uint8_t count =0;
    while(temp != NULL){
        count +=1;
        temp = temp->next;
    }
    
    temp = node1;
    for(uint8_t i = 0; i < (count/2); i++){
        temp = temp->next;
    }
    printf("Mid element : %d",temp->data );
    
    return 0;
}
