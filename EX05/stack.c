#include <stdlib.h>
#include <string.h>
#include "stack.h"

struct stack
{
    int top;
    elem items[Stack_Size];
};

stack_t *create()
{
    stack_t *s = (stack_t *)malloc(sizeof(stack_t));

    s->top = -1;
    return s;
}

void destroy(stack_t *s)
{
    if (s != NULL)
    {
        free(s);
    }
    s = NULL;
}

int isFull(stack_t *s)
{
    if (s->top == Stack_Size - 1)
        return 1;
    else
        return 0;
}

int isEmpty(stack_t *s) 
{
    if (s->top == -1)
        return 1;
    else
        return 0;
}

int push(stack_t *s, elem *x)
{
    if (isFull(s) == 1)
    {
        return -1;
    }
    s->top = s->top + 1;
    s->items[s->top] = x;
    return 1;
}

int pop(stack_t *s, elem *x)
{
    if (isEmpty(s) == 1)
    {
        return 0;
    }
    
    *x = s->items[s->top];
    s->top -= 1;
    return 1;
}

int top_value(stack_t *s, elem *x)
{
    if (isEmpty(s) == 1)
    {
        return 0;
    }
    *x = s->items[s->top];
    return 1;
}