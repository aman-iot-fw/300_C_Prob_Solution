
/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct list{
    int data;
    struct list *next;
}list_t;

list_t* createNode(int data){
    list_t *node = malloc(sizeof(list_t));
    
    if(node == NULL){
        printf("Memory allocaiton failed");
        return NULL;
    }
    
    node->data = data;
    node->next = NULL;
    return node;
}

void printList(list_t *head){
    list_t *node = head;
    
    while(node != NULL){
        printf("%d->", node->data);
        node = node->next;
    }
    printf("NULL");
}

void insertEnd(list_t **head, int data){
    list_t *node = createNode(data);
    
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

void findMid(list_t *head){
    if(head == NULL){
        printf("List is Empty");
    }
    
    list_t *slow = head;
    list_t *fast = head;
    
    while(fast != NULL && fast->next != NULL){
        slow = slow->next;
        fast = fast->next->next;
    }
    printf("\n\nMid Element : %d\n\n", slow->data);
    
}

void sortList(list_t *head){
    int tmp;
    for(list_t *i = head; i != NULL; i = i->next){
        for(list_t *j = i->next; j != NULL; j = j->next){
            if(i->data > j->data){
                tmp = i->data;
                i->data = j->data;
                j->data = tmp;
            }
        }
    }
}

void insertStart(list_t **head, int data){
    list_t *node = createNode(data);
    
    if(*head == NULL){
        *head = node;
        return;
    }
    
    list_t *tmp = *head;
    *head = node;
    (*head)->next = tmp;
}

int countSetBits(int value){
    int count = 0;
    while(value){
        value &= (value - 1);
        count++;
    }
    return count;
}

bool isPowerOfTwo(int value){
    return (value > 0) && (value & (value-1) == 0);
}

int posOfFirstSetBit(int value){
    int pos = 1;
    while(!(value & 1)){
        value >>= 1;
        pos++;
    }
    return pos;
}

void swap(int *a, int *b){
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}

unsigned int reverse(unsigned int value){
    unsigned int rev = 0;
    for(int i = 0; i < 32; i++){
        rev <<= 1;
        rev |= (value & 1);
        value >>= 1;
    }
    return rev;
}

void *myMemcpy(void *dst, const void *src, int len){
    char *d = dst;
    const char *s = src;
    while(len--){
        *d++ = *s++;
    }
    return dst;
}

void *myMemset(void *ptr, size_t size, int value){
    unsigned char *p = ptr;
    while(size--){
        *p++ = (unsigned char)value;
    }
    return ptr;
}

void reverseString(char *str){
    int i = 0; 
    int j = strlen(str)-1;
    
    while(i < j){
        char tmp;
        tmp = str[i];
        str[i++] = str[j];
        str[j--] = tmp;
    }
}

int mystrlen(const char *str){
    int len;
    while(*str++)
        len++;
    return len;
}

void removeDuplicates(char *str) {
    int hash[256] = {0};
    int i, j = 0;

    for (i = 0; str[i]; i++) {
        if (!hash[str[i]]) {
            hash[str[i]] = 1;
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

int isAnagram(char *a, char *b) {
    int count[256] = {0};

    for (int i = 0; a[i]; i++)
        count[a[i]]++;

    for (int i = 0; b[i]; i++)
        count[b[i]]--;

    for (int i = 0; i < 256; i++)
        if (count[i] != 0)
            return 0;

    return 1;
}

int missing(int arr[], int n) {
    int sum = n * (n + 1) / 2;
    int arrSum = 0;

    for (int i = 0; i < n - 1; i++)
        arrSum += arr[i];

    return sum - arrSum;
}

int main()
{
    // list_t *head = createNode(10);
    // insertEnd(&head, 6);
    // insertEnd(&head, 8);
    // insertEnd(&head, 4);
    // insertEnd(&head, 9);
    
    // insertStart(&head, 5);
    
    // printList(head);
    
    // findMid(head);
    // sortList(head);
    // printList(head);
    
    char str[] = "Hello";
    printf("\n%s", str);
    reverseString(str);
    printf("\n%s", str);
    

    return 0;
}
