#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Node structure for the queue
typedef struct Node {
    char *message;          // Stored string message
    struct Node *next;      // Pointer to next node
} Node;

// Queue structure
typedef struct StringQueue {
    Node *front;            // Front of the queue
    Node *rear;             // Rear of the queue
} StringQueue;

// Initialize the queue
void initQueue(StringQueue *q) {
    q->front = NULL;
    q->rear = NULL;
}

// Check if queue is empty
int isEmpty(StringQueue *q) {
    return q->front == NULL;
}

// Enqueue: Add a message to the rear
void enqueue(StringQueue *q, const char *msg) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }
    newNode->message = strdup(msg);  // Copy the string
    newNode->next = NULL;

    if (isEmpty(q)) {
        q->front = newNode;
        q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

// Dequeue: Remove and return the front message
char *dequeue(StringQueue *q) {
    if (isEmpty(q)) {
        fprintf(stderr, "Queue is empty\n");
        return NULL;
    }

    Node *temp = q->front;
    char *msg = temp->message;  // Return the message (caller must free if needed)

    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;  // Queue is now empty
    }

    free(temp);  // Free the node
    return msg;
}

// Free the entire queue (cleanup)
void freeQueue(StringQueue *q) {
    while (!isEmpty(q)) {
        char *msg = dequeue(q);
        free(msg);  // Free the duplicated string
    }
}

int main() {
    StringQueue q;
    initQueue(&q);

    // Enqueue examples
    enqueue(&q, "HELLO");
    enqueue(&q, "WORLD");

    // Dequeue and print
    char *msg1 = dequeue(&q);
    if (msg1) {
        printf("Dequeue: %s\n", msg1);
        free(msg1);  // Free after use
    }

    char *msg2 = dequeue(&q);
    if (msg2) {
        printf("Dequeue: %s\n", msg2);
        free(msg2);
    }

    // Cleanup (though not necessary here as program ends)
    freeQueue(&q);

    return 0;
}