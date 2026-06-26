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

void detectCycle(list_t *head){
  list_t *slow = head;
  list_t *fast = head;
  
  while(fast != NULL && fast->next != NULL){
        slow = slow->next;
        fast = fast->next->next;
        
        if(slow == fast){
            printf("List is Circular");
            return;
        }
  }
  printf("List is not Circular");
}

int main(){
  list_t *head = createList(1);
  list_t *node2 = createList(2);
  list_t *node3 = createList(3);
  list_t *node4 = createList(4);
  list_t *node5 = createList(5);
  head->next = node2;
  node2->next = node3;
  node3->next = node4;
  node4->next = node5;
  node5->next = head;
 

  //printList(head);
  detectCycle(head);


  return 0;
}

