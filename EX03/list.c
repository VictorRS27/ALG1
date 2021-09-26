#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
        printf("%c ", i->value);
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

int unitary_compair(node_t *l, elem current, elem *sub_part, int total)
{
    if (l->value == sub_part[current])
    {
        if (current == total)
        {
            return 1;
        }
        else
        {
            return unitary_compair(l->next, ++current, sub_part, total);
        }
    }
    else
    {
        return 0;
    }
}

node_t *string_finder(list_t *l, elem *x)
{
    node_t *i = l->start, *previous = l->start;
    while (i != NULL)
    {
        if (unitary_compair(i, 0, x, strlen(x) - 1))
            return previous;
        previous = i;
        i = i->next;
    }
    return NULL;
}

/* int replace(list_t *l, elem *to_be_changed, elem *to_change)
{
    if (l == NULL)
        return -1;

    int i = -1, j = 0, k;
    node_t **current = (node_t *)malloc(sizeof(node_t *));

    do
    {
        i++;
        current = (node_t *)realloc(current, (i + 1) * sizeof(node_t *));
        current[i]=string_finder(l, to_be_changed);
    } while (current[i]);

    if (current[0] == NULL)
    {
        free(current);
        return 0;
    }

    node_t *new_values_start, *new_values_end, *filler;
    for ( j = 0; j < i; j++)
    {
        new_values_start = (node_t *)malloc(sizeof(node_t));
        filler = new_values_end = new_values_start;
        new_values_end->value = to_change[0];
        for ( k = 1; k < strlen(to_change); k++)
        {
            new_values_end = (node_t *)malloc(sizeof(node_t));
            new_values_end->value = to_change[k];
            filler->next = new_values_end;
            filler = filler->next;
        }
        
        if (current == l->start)
        {
            l->start = new_values_start;

        }
        
    }
    
    
    free(current);
} */

int replace(list_t *l, elem *to_be_changed, elem *to_change)
{
    if (l == NULL)
        return -1;

    int i = -1, j = 0, k;
    node_t *end_founder;
    list_t *new_values, *old_values;
    new_values = create();
    old_values = create();
    end_founder = old_values->start = string_finder(l, to_be_changed);

    if (end_founder == NULL)
    {
        return 0;
    }
    

    for (i = 0; i < strlen(to_change); i++)
    {
        insert(new_values, to_change[i]);
    }
    for (i = 0; i < strlen(to_be_changed) - 1; i++)
    {
        end_founder = end_founder->next;
    }
    old_values->end = end_founder;

    if (l->start == old_values->start)
    {
        l->start = new_values->start;
    }
    if (l->end == old_values->end)
    {
        l->end = new_values->end;
    }
    else
    {
        new_values->end->next = old_values->end->next;
    }
    l->end->next = NULL;
    old_values->start->next = new_values->start;
    old_values->start = old_values->start->next;
    l->size = l->size - strlen(to_be_changed) + size(new_values);
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

/* elem lremove_by_index(list_t *l, int index)
{
    if (l == NULL)
        return -1;

    int j;
    node_t *i = l->start, *exit;
    if (index == 0)
    {
        l->start = l->start->next;
    }
    else if (index == size(l))
    {
        while (j<index-1)
        {
            
        }
        
    }
    

    return exit->value;
} */

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