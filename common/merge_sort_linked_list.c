/*
 * merge_sort_linked_list.c
 *
 * Merge Sort on a Singly Linked List
 * -----------------------------------
 * Strategy:
 *   1. Find the middle of the list using the slow/fast pointer technique.
 *   2. Recursively split the list into two halves.
 *   3. Sort each half recursively.
 *   4. Merge the two sorted halves back into one sorted list.
 *
 * Time  Complexity : O(n log n)
 * Space Complexity : O(log n)  — call stack depth for recursion
 */

#include <stdio.h>
#include <stdlib.h>

/* ── Node definition ─────────────────────────────────────────────────────── */

typedef struct Node {
    int data;
    struct Node *next;
} Node;

/* ── Helper: create a new node ───────────────────────────────────────────── */

/*
 * newNode()
 * Allocates a new linked-list node with the given value.
 * Returns a pointer to the new node.
 */
Node *newNode(int data) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (!node) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->data = data;
    node->next = NULL;
    return node;
}

/* ── Helper: find the middle node ────────────────────────────────────────── */

/*
 * getMiddle()
 * Uses the slow/fast pointer (Floyd's) technique to find the middle node.
 * For a list of even length the first middle is returned so that the
 * list is split into two roughly equal halves.
 *
 * Example: 1 -> 2 -> 3 -> 4
 *          slow stops at node(2), fast reaches node(4)
 *          => left half: 1->2,  right half: 3->4
 *
 * Returns a pointer to the middle node.
 */
Node *getMiddle(Node *head) {
    if (!head) return head;

    Node *slow = head;       /* advances one step at a time  */
    Node *fast = head->next; /* advances two steps at a time */

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow; /* slow is now at the middle */
}

/* ── Core: merge two sorted lists ────────────────────────────────────────── */

/*
 * mergeSorted()
 * Merges two already-sorted linked lists into a single sorted list.
 * Works by comparing the heads of both lists and linking the smaller
 * node first, then recurring on the remainder.
 *
 * Parameters:
 *   left  – head of the first sorted list
 *   right – head of the second sorted list
 *
 * Returns the head of the merged sorted list.
 */
Node *mergeSorted(Node *left, Node *right) {
    /* Base cases: if either list is empty, return the other */
    if (!left)  return right;
    if (!right) return left;

    Node *result = NULL;

    if (left->data <= right->data) {
        /* left head is smaller — pick it and merge the rest */
        result       = left;
        result->next = mergeSorted(left->next, right);
    } else {
        /* right head is smaller — pick it and merge the rest */
        result       = right;
        result->next = mergeSorted(left, right->next);
    }

    return result;
}

/* ── Core: merge sort ────────────────────────────────────────────────────── */

/*
 * mergeSort()
 * Recursively splits the list into halves, sorts each half, then merges.
 *
 * Parameters:
 *   head – head of the list to sort
 *
 * Returns the head of the fully sorted list.
 */
Node *mergeSort(Node *head) {
    /* Base case: a list of 0 or 1 node is already sorted */
    if (!head || !head->next)
        return head;

    /* Step 1: find the middle of the current list */
    Node *mid = getMiddle(head);

    /* Step 2: split into two halves */
    Node *rightHalf = mid->next; /* second half starts after mid */
    mid->next       = NULL;      /* terminate the first half     */

    /* Step 3: recursively sort both halves */
    Node *left  = mergeSort(head);
    Node *right = mergeSort(rightHalf);

    /* Step 4: merge the two sorted halves */
    return mergeSorted(left, right);
}

/* ── Utility: append a node to the list ─────────────────────────────────── */

/*
 * append()
 * Adds a new node with 'data' at the tail of the list pointed to by *head.
 */
void append(Node **head, int data) {
    Node *node = newNode(data);
    if (!*head) {
        *head = node;
        return;
    }
    Node *curr = *head;
    while (curr->next)
        curr = curr->next;
    curr->next = node;
}

/* ── Utility: print the list ─────────────────────────────────────────────── */

/*
 * printList()
 * Traverses the list and prints each node's data separated by " -> ".
 */
void printList(Node *head) {
    while (head) {
        printf("%d", head->data);
        if (head->next) printf(" -> ");
        head = head->next;
    }
    printf("\n");
}

/* ── Utility: free all nodes ─────────────────────────────────────────────── */

/*
 * freeList()
 * Releases all memory allocated for the linked list.
 */
void freeList(Node *head) {
    Node *tmp;
    while (head) {
        tmp  = head;
        head = head->next;
        free(tmp);
    }
}

/* ── main ────────────────────────────────────────────────────────────────── */

int main(void) {
    Node *head = NULL;

    /* Build an unsorted linked list: 38 -> 27 -> 43 -> 3 -> 9 -> 82 -> 10 */
    int values[] = {38, 27, 43, 3, 9, 82, 10};
    int n        = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < n; i++)
        append(&head, values[i]);

    printf("Original list : ");
    printList(head);

    /* Sort the list using merge sort */
    head = mergeSort(head);

    printf("Sorted list   : ");
    printList(head);

    /* Clean up */
    freeList(head);
    return 0;
}
