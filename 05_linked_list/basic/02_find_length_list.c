#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Create a new node
Node *createNode(int data) {
    Node *tempNode = (Node *)malloc(sizeof(Node));
    if (tempNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);  
    }
    tempNode->data = data;
    tempNode->next = NULL;
    return tempNode;
}

// Insert at end 
void insertAtEnd(Node **head, int data) {
    Node *newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node *temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

// Find length 
int findLength(Node *head) {
    int count = 0;  
    Node *tempNode = head;
    while (tempNode != NULL) {
        count++;
        tempNode = tempNode->next;
    }
    return count;
}

int main() {
    Node *head = NULL;  // Start empty

    // Build list using insert
    insertAtEnd(&head, 1);
    insertAtEnd(&head, 2);
    insertAtEnd(&head, 3);
    insertAtEnd(&head, 4);
    insertAtEnd(&head, 5);

    // Get and print length
    int length = findLength(head);
    printf("Length is %d\n", length);

    // Free the list
    Node *current = head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}