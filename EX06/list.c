#include <stdio.h>
#include <stdlib.h>
#include "list.h"

typedef struct node
{
    elem value;
    struct node *next, *prev;
} node_t;

struct list
{
    node_t *reference;
    int size;
};

list_t *create()
{
    list_t *l;
    l = (list_t *)malloc(sizeof(list_t));

    l->reference = NULL;
    l->size = 0;
}

void destroy(list_t *l)
{
    if (l != NULL)
    {
        if (l->size != 0)
        {
            node_t *i = l->reference, *j;
            l->reference->prev->next = NULL;
            while (i != NULL)
            {
                j = i->next;
                //printf("livrei: %d\n", i->value);
                free(i);
                i = j;
            }
        }
        free(l);
    }
}

//limpa os dados da lista sem desaloca-la
void clear(list_t *l)
{
    if (l != NULL)
    {
        node_t *i = l->reference, *j;
        l->reference->prev->next = NULL;
        while (i != NULL)
        {
            j = i->next;
            //printf("livrei: %d\n", i->value);
            free(i);
            i = j;
        }
        l->size = 0;
    }
}

int insert(list_t *l, elem x)
{
    node_t *i = (node_t *)malloc(sizeof(node_t));

    i->value = x;

    if (l->size == 0)
    {
        l->reference = i;
        l->reference->prev = i;
        l->reference->next = i;
    }
    else
    {
        l->reference->prev->next = i;
        i->prev = l->reference->prev;
        l->reference->prev = i;
        i->next = l->reference;
    }

    l->size++;
    return 1;
}

int size(list_t *l)
{
    return l->size;
}

int print(list_t *l)
{
    if (l == NULL)
        return 0;

    node_t *i = l->reference;
    do
    {
        printf("%i ", i->value);
        i = i->next;
    }while (i != l->reference);
}

int is_in_list(list_t *l, elem x)
{
    if (l == NULL)
        return -1;

    node_t *i = l->reference->next;
    while (i != l->reference)
    {
        if (i->value == x)
        {
            return 1;
        }
        i = i->next;
    }
    return 0;
}

//move o inicio da lista para esquerda
int rotate_left(list_t *l, int rotations)
{
    if (l == NULL)
    {
        return 0;
    }
    
    int i;
    for ( i = 0; i < rotations; i++)
    {
        l->reference = l->reference->prev;
    }
    return 1;
}