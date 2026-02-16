#include <stdio.h>
#include <stdlib.h>


typedef struct list{
    int data;
    struct list *next;
}list_t;

void insertEnd(list_t **head, int data){
    list_t *node = malloc(sizeof(list_t));
    node->data = data;
    node->next = NULL;
    
    if(*head == NULL){
        *head = node;
        return;
    }
    
    list_t *tmp = *head;
    while(tmp->next != NULL){
        tmp = tmp->next;
    }
    tmp->next = node;
}

void printList(list_t *head){
    list_t *tmp = head;
    
    printf("\nList Data :");
    while(tmp != NULL){
        printf("%d  ", tmp->data);
        tmp = tmp->next;
    }
}

void findMid(list_t *head){
    
    if(head == NULL){
    printf("List is empty");
    return;
    }
    
    list_t *slow = head;
    list_t *fast = head;

    while(fast != NULL && fast->next != NULL){
        slow = slow->next;
        fast = fast->next->next;
    }
    printf("\nMid Element : %d", slow->data);
    
}


void sortList(list_t *head){
    
    if(head == NULL || head->next ==NULL){
        return;
    }
    
    list_t *i, *j;
    int tmp;
    
    for(i = head; i->next != NULL; i = i->next){
        for(j = i->next; j != NULL; j = j->next){
            if(i->data > j->data){
                tmp = i->data;
                i->data = j->data;
                j->data = tmp;
                
            }
        }
    }
}


int main(){
    list_t *head = NULL;
    insertEnd(&head, 10);
    insertEnd(&head, 50);
    insertEnd(&head, 40);
    insertEnd(&head, 30);
    insertEnd(&head, 20);
    
    printList(head);
    sortList(head);
    printf("\nShorted List : ");
    printList(head);
    findMid(head);
    
    
    
    return 0;
}
