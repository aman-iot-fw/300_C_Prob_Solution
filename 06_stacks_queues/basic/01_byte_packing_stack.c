#include <stdio.h>
#include <stdint.h>

#define STACK_WORDS 4   // number of 32-bit words

typedef struct {
    uint32_t data[STACK_WORDS];
    uint8_t  byte_offset;   // 0..3
    uint8_t  word_top;      // index of uint32_t
} ByteStack;

/* Initialize stack */
void init_stack(ByteStack *s)
{
    for (int i = 0; i < STACK_WORDS; i++)
        s->data[i] = 0;

    s->byte_offset = 0;
    s->word_top = 0;
}

/* Push one byte */
int push(ByteStack *s, uint8_t value)
{
    if (s->word_top >= STACK_WORDS)
        return -1; // stack overflow

    s->data[s->word_top] |= ((uint32_t)value << (s->byte_offset * 8));
    s->byte_offset++;

    if (s->byte_offset == 4) {
        s->byte_offset = 0;
        s->word_top++;
    }

    return 0;
}

/* Print stack contents */
void print_stack(ByteStack *s)
{
    for (int i = 0; i < STACK_WORDS; i++)
        printf("Word %d: 0x%08X\n", i, s->data[i]);
}

/* Demo */
int main(void)
{
    ByteStack s;
    init_stack(&s);

    push(&s, 0x01);
    push(&s, 0x02);
    push(&s, 0x03);
    push(&s, 0x04);

    print_stack(&s);
    return 0;
}
