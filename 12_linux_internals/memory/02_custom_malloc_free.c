#include <stdio.h>
#include <unistd.h>  // For sbrk()
#include <stddef.h>  // For size_t, NULL

// Minimum block size (header + some data)
#define MIN_ALLOC_SIZE 4096  // Page size for efficiency

// Block header structure
typedef struct Block {
    size_t size;          // Size of the block (excluding header)
    struct Block *next;   // Next block in free list
    int free;             // 1 if free, 0 if allocated
} Block;

// Global free list head (starts as NULL)
static Block *free_list = NULL;

// Helper: Find the best-fit free block >= requested size
static Block *find_best_fit(size_t size) {
    Block *best = NULL;
    Block *current = free_list;

    while (current) {
        if (current->free && current->size >= size) {
            if (!best || current->size < best->size) {
                best = current;
            }
        }
        current = current->next;
    }
    return best;
}

// Helper: Request more memory from OS using sbrk()
static Block *request_space(size_t size) {
    void *request = sbrk(size + sizeof(Block));
    if (request == (void *)-1) {
        return NULL;  // sbrk failed
    }

    Block *block = (Block *)request;
    block->size = size;
    block->free = 0;  // Allocated
    block->next = NULL;

    return block;
}

// Helper: Split a block if it's larger than needed
static void split_block(Block *block, size_t size) {
    if (block->size > size + sizeof(Block)) {
        Block *new_block = (Block *)((char *)block + sizeof(Block) + size);
        new_block->size = block->size - size - sizeof(Block);
        new_block->free = 1;
        new_block->next = block->next;

        block->size = size;
        block->next = new_block;
    }
}

// Custom malloc: Allocate 'size' bytes
void *my_malloc(size_t size) {
    if (size == 0) return NULL;

    // Align size to 8 bytes for safety
    size = (size + 7) & ~7;

    Block *block = find_best_fit(size);

    if (block) {
        // Found a free block
        block->free = 0;
        split_block(block, size);
    } else {
        // No free block → expand heap
        block = request_space(size);
        if (!block) {
            return NULL;
        }

        // Add to free list (though it's allocated, next might be free)
        if (free_list) {
            Block *last = free_list;
            while (last->next) last = last->next;
            last->next = block;
        } else {
            free_list = block;
        }
    }

    // Return pointer after header
    return (void *)((char *)block + sizeof(Block));
}

// Helper: Get block from user pointer
static Block *get_block(void *ptr) {
    return (Block *)((char *)ptr - sizeof(Block));
}

// Helper: Merge adjacent free blocks
static void coalesce() {
    Block *current = free_list;
    while (current && current->next) {
        if (current->free && current->next->free) {
            // Merge
            current->size += sizeof(Block) + current->next->size;
            current->next = current->next->next;
        } else {
            current = current->next;
        }
    }
}

// Custom free: Deallocate memory at 'ptr'
void my_free(void *ptr) {
    if (!ptr) return;

    Block *block = get_block(ptr);
    block->free = 1;

    // Coalesce to merge adjacent free blocks
    coalesce();
}

int main() {
    // Test the custom malloc/free
    printf("Testing custom malloc/free...\n");

    void *p1 = my_malloc(10);
    if (p1) printf("Allocated 10 bytes at %p\n", p1);

    void *p2 = my_malloc(20);
    if (p2) printf("Allocated 20 bytes at %p\n", p2);

    my_free(p1);
    printf("Freed p1\n");

    void *p3 = my_malloc(15);
    if (p3) printf("Allocated 15 bytes at %p (should reuse p1's space)\n", p3);

    my_free(p2);
    my_free(p3);

    printf("All freed.\n");

    return 0;
}
