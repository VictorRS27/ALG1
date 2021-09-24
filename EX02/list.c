#include <stdio.h>
#include <stdlib.h>
#include "list.h"

typedef struct node
{
    elem value;
    struct node *next;
} node_t;

struct list
{
    node_t *start, *end;
    int size;
};

list_t *create()
{
    list_t *l;
    l = (list_t *)malloc(sizeof(list_t));

    l->end = NULL;
    l->start = NULL;
    l->size = 0;
}

void destroy(list_t *l)
{
    if (l != NULL)
    {
        node_t *i = l->start;
        while (i != NULL)
        {
            l->start = i->next;
            free(i);
            i = l->start;
        }
        free(l);
    }
}

int insert(list_t *l, elem x)
{
    node_t *i = (node_t *)malloc(sizeof(node_t));

    if (l == NULL || i == NULL)
        return 0;

    i->value = x;
    i->next = NULL;

    if (l->start == NULL)
    {
        l->start = i;
        l->end = i;
    }
    else
    {
        l->end->next = i;
    }
    l->end = i;

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

    node_t *i = l->start;
    while (i != NULL)
    {
        printf("%li ", i->value);
        i = i->next;
    }
}

int is_in_list(list_t *l, elem x)
{
    if (l == NULL)
        return -1;

    node_t *i = l->start;
    while (i != NULL)
    {
        if (i->value == x)
        {
            return 1;
        }
        i = i->next;
    }
    return 0;
}

elem query_index(list_t *l, int index)
{
    
    int j = 0;
    node_t *i = l->start;
    while (j < index)
    {
        if (i->next != NULL)
        {
            i = i->next;
        }
        else
        {
            return 0;
        }
        j++;
    }
    return i->value;
}

elem lremove_by_index(list_t *l, int index)
{
    if (l == NULL)
        return -1;

    int j;
    node_t *i = l->start, *exit;
    while (j < index - 1)
    {
        if (i->next != NULL)
        {
            i = i->next;
        }
        else
        {
            return 0;
        }
    }
    exit = i->next;
    free(i->next);
    i->next = i->next->next;

    return exit->value;
}

int lremove_by_elem(list_t *l, elem cutter)
{

    node_t *i = l->start;
    node_t *prev;
    while (i != NULL)
    {
        if (i->value == cutter)
        {
            if (i == l->start)
            {
                l->start = l->start->next;
                free(i);
            }
            else if (i == l->end)
            {
                l->end = prev;
                l->end->next = NULL;
                free(i);
            }
            else
            {
                prev->next = i->next;
                free(i);
            }
            l->size--;
            return 1;
        }
        else
        {
            prev = i;
            i = i->next;
        }
    }
    return 0;
}