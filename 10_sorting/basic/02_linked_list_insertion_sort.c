#include <stdio.h>
#include <stdlib.h>

// Definition for singly-linked list node
struct Node {
    int data;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node into the sorted list
void sortedInsert(struct Node** sortedHead, struct Node* newNode) {
    struct Node* current;

    // Case: Insert at head (newNode is smallest)
    if (*sortedHead == NULL || (*sortedHead)->data >= newNode->data) {
        newNode->next = *sortedHead;
        *sortedHead = newNode;
    } else {
        // Find insertion point
        current = *sortedHead;
        while (current->next != NULL && current->next->data < newNode->data) {
            current = current->next;
        }
        // Insert after current
        newNode->next = current->next;
        current->next = newNode;
    }
}

// Function to sort the linked list using insertion sort
struct Node* insertionSortList(struct Node* head) {
    struct Node* sorted = NULL;  // Head of sorted list
    struct Node* current = head; // Traverse original list
    struct Node* next;

    while (current != NULL) {
        // Save next node
        next = current->next;
        // Insert current into sorted list
        sortedInsert(&sorted, current);
        // Move to next
        current = next;
    }

    return sorted;
}

// Utility to print the list
void printList(struct Node* head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

int main() {
    // Example: 4 -> 2 -> 1 -> 5
    struct Node* head = createNode(4);
    head->next = createNode(2);
    head->next->next = createNode(1);
    head->next->next->next = createNode(5);

    printf("Original list: ");
    printList(head);

    head = insertionSortList(head);

    printf("Sorted list: ");
    printList(head);

    // Free memory (optional for this example)
    struct Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}
