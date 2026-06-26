#include<stdio.h>
#include<stdlib.h>

typedef struct list{
  int data;
  struct list *next;
}list_t;

list_t* createList(int data){
  list_t *node = malloc(sizeof(list_t));
  if(node == NULL){
    printf("Mem Allocation Failed");
    return NULL;
  }
    

  node->data = data;
  node->next = NULL;
  return node;
}

void insertStart(list_t **head, int data){
  list_t *node = createList(data);
  if(*head == NULL){
    *head = node;
    return;
  }

  list_t *tmp = *head;
  *head = node;
  node->next = tmp;
}

void printList(list_t *head){
    
  list_t *node = head;    
  if(node == NULL){
  printf("List Is Empty");
  return;
  }

  printf("List : ");
  while(node != NULL){
    printf("%d ",node->data);
    node = node->next;
  }

  printf("\n");
}

list_t* reverseList(list_t *head){
    list_t *prev = NULL;
    list_t *current = head;
    list_t *next = NULL;
    
    while(current != NULL){
        next = current->next;
        
        current->next = prev;
        
        prev = current;
        
        current = next; 
    }
    return prev;
}

int main(){
  list_t *head = NULL;
  insertStart(&head, 4);
  insertStart(&head, 3);
  insertStart(&head, 2);
  insertStart(&head, 1);

  printList(head);
  printList(reverseList(head));

  return 0;
}
