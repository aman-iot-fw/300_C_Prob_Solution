#include <stdio.h>
#include <stddef.h>   // for size_t, ptrdiff_t
#include <stdint.h>   // for uintptr_t
#include <string.h>   // for memset

// Configuration
#define BUFFER_SIZE 1024   // Total memory pool size in bytes

// Header placed before each allocation (keeps track of size)
typedef struct BlockHeader {
    size_t size;          // size requested by user (without header)
    // You can add more fields later: alignment padding, magic number for debugging, etc.
} BlockHeader;

// Main stack allocator structure
typedef struct StackAllocator {
    uint8_t buffer[BUFFER_SIZE];     // fixed memory pool
    size_t top;                      // current top offset (bytes used)
    // For debugging/validation
    size_t peak_usage;
} StackAllocator;

// Initialize the allocator
void stack_init(StackAllocator* alloc) {
    alloc->top = 0;
    alloc->peak_usage = 0;
    // Optional: fill with debug pattern
    // memset(alloc->buffer, 0xCD, BUFFER_SIZE);
}

// Helper: get current top address
static void* get_top_ptr(StackAllocator* alloc) {
    return &alloc->buffer[alloc->top];
}

// Allocate memory - returns NULL if not enough space
void* stack_allocate(StackAllocator* alloc, size_t size) {
    if (size == 0) {
        return NULL;
    }

    // We need space for header + requested bytes
    // For simplicity, we align to sizeof(size_t) or 8 bytes
    size_t header_size = sizeof(BlockHeader);
    size_t total_needed = header_size + size;

    // Align the allocation to 8 bytes (common and safe)
    size_t alignment = 8;
    size_t padding = (alignment - (alloc->top % alignment)) % alignment;
    total_needed += padding;

    if (alloc->top + total_needed > BUFFER_SIZE) {
        printf("Allocation failed: requested %zu bytes, only %zu free\n",
               size, BUFFER_SIZE - alloc->top);
        return NULL;
    }

    // Place header at current top
    BlockHeader* header = (BlockHeader*)get_top_ptr(alloc);
    header->size = size;

    // Move top past header + padding + requested size
    alloc->top += header_size + padding + size;

    // Update peak usage
    if (alloc->top > alloc->peak_usage) {
        alloc->peak_usage = alloc->top;
    }

    // Return address right after the header (user-visible pointer)
    return (char*)header + header_size + padding;
}

// Free - only allows freeing the most recently allocated block (LIFO)
void stack_free(StackAllocator* alloc, void* ptr) {
    if (!ptr) {
        return;
    }

    // Compute where the header should be (just before the user pointer)
    char* user_ptr = (char*)ptr;
    BlockHeader* header = (BlockHeader*)(user_ptr - sizeof(BlockHeader));

    // Basic validation: check if header is within our buffer and top makes sense
    uintptr_t header_addr = (uintptr_t)header;
    uintptr_t buffer_start = (uintptr_t)alloc->buffer;
    uintptr_t buffer_end = buffer_start + BUFFER_SIZE;

    if (header_addr < buffer_start || header_addr >= buffer_end) {
        printf("Invalid free: pointer not from this allocator\n");
        return;
    }

    // Calculate what the top should be if this is the last allocation
    size_t expected_top = (char*)header - (char*)alloc->buffer + sizeof(BlockHeader) + header->size;

    // For strict LIFO enforcement: top must match exactly
    if (expected_top != alloc->top) {
        printf("Free error: Attempt to free non-top block (LIFO violation)!\n");
        printf("  Current top: %zu bytes\n", alloc->top);
        printf("  Expected after free: %zu bytes\n", expected_top);
        return;
    }

    // Valid LIFO free → roll back
    alloc->top = (char*)header - (char*)alloc->buffer;
    // Optional: poison the memory for debugging
    // memset(&alloc->buffer[alloc->top], 0xFD, BUFFER_SIZE - alloc->top);
}

// Reset everything (like a bulk free)
void stack_reset(StackAllocator* alloc) {
    alloc->top = 0;
}

// Utility: get current used bytes
size_t stack_used(StackAllocator* alloc) {
    return alloc->top;
}

// Utility: get peak usage
size_t stack_peak(StackAllocator* alloc) {
    return alloc->peak_usage;
}

// ────────────────────────────────────────────────
// Example usage & demonstration
// ────────────────────────────────────────────────
int main(void) {
    StackAllocator sa;
    stack_init(&sa);

    printf("Initial: used = %zu bytes\n", stack_used(&sa));

    // Allocate in order: 10, 20, 15 bytes
    void* p1 = stack_allocate(&sa, 10);
    void* p2 = stack_allocate(&sa, 20);
    void* p3 = stack_allocate(&sa, 15);

    printf("\nAfter allocations:\n");
    printf("  p1 = %p  (10 bytes)\n", p1);
    printf("  p2 = %p  (20 bytes)\n", p2);
    printf("  p3 = %p  (15 bytes)\n", p3);
    printf("  Used = %zu bytes, Peak = %zu bytes\n", stack_used(&sa), stack_peak(&sa));

    // Free last one (15 bytes) — should succeed
    printf("\nFreeing p3 (15 bytes)...\n");
    stack_free(&sa, p3);

    printf("After free:\n");
    printf("  Used = %zu bytes\n", stack_used(&sa));

    // This should fail (not LIFO)
    printf("\nTrying to free p1 (not top block)...\n");
    stack_free(&sa, p1);   // Will print error

    // Free p2 (now top)
    printf("\nFreeing p2 (20 bytes)...\n");
    stack_free(&sa, p2);

    printf("After freeing p2:\n");
    printf("  Used = %zu bytes\n", stack_used(&sa));

    // Clean up
    stack_reset(&sa);
    printf("\nReset: used = %zu bytes\n", stack_used(&sa));

    return 0;
}