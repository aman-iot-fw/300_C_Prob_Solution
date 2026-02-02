#include <stdio.h>
#include <stdlib.h>

// Node for tracking allocations
typedef struct AllocNode {
    void *ptr;             // Allocated pointer
    size_t size;           // Size of allocation
    struct AllocNode *next; // Next node
} AllocNode;

// Global head of allocation list
static AllocNode *alloc_head = NULL;

// Helper: Add allocation to the list
static void add_allocation(void *ptr, size_t size) {
    AllocNode *new_node = (AllocNode *)malloc(sizeof(AllocNode));
    if (!new_node) {
        fprintf(stderr, "Failed to track allocation\n");
        return;
    }
    new_node->ptr = ptr;
    new_node->size = size;
    new_node->next = alloc_head;
    alloc_head = new_node;
}

// Helper: Remove allocation from the list
static void remove_allocation(void *ptr) {
    AllocNode *current = alloc_head;
    AllocNode *prev = NULL;

    while (current) {
        if (current->ptr == ptr) {
            if (prev) {
                prev->next = current->next;
            } else {
                alloc_head = current->next;
            }
            free(current);  // Free the node
            return;
        }
        prev = current;
        current = current->next;
    }
    fprintf(stderr, "Warning: Freeing untracked pointer %p\n", ptr);
}

// Custom malloc with tracking
void *my_malloc(size_t size) {
    void *ptr = malloc(size);
    if (ptr) {
        add_allocation(ptr, size);
    }
    return ptr;
}

// Custom free with tracking
void my_free(void *ptr) {
    if (ptr) {
        remove_allocation(ptr);
        free(ptr);
    }
}

// Function to check for leaks (call at end)
void check_leaks() {
    AllocNode *current = alloc_head;
    if (!current) {
        printf("No memory leaks detected.\n");
        return;
    }

    printf("Memory leaks detected:\n");
    while (current) {
        printf("Leak Detected at %zu bytes (address %p)\n", current->size, current->ptr);
        AllocNode *temp = current;
        current = current->next;
        free(temp);  // Clean up tracking node
    }
    alloc_head = NULL;
}

int main() {
    // Simulate the example
    void *alloc1 = my_malloc(5);
    void *alloc2 = my_malloc(7);
    my_free(alloc1);  // Free the 5-byte allocation

    // Check for leaks
    check_leaks();

    return 0;
}