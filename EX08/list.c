#include <stdio.h>
#include <stdlib.h>
#include "list.h"

typedef struct node
{
    elem value;
    int index;
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
    i->index = l->size;

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
        if (i != l->start)
        {
            printf(",");
        }
        
        printf("%i", i->value);
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

// procura o valor de um item na lista dada sua posicao
elem query_by_pos(list_t *l, int pos)
{

    int j = 0;
    node_t *i = l->start;
    while (j < pos)
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

//busca um valor da lista pelo index
int query_by_index(list_t *l, int *exit, int index)
{
    if (index<0)
    {
        return 0;
    }

    if (l->start == NULL)
    {
        *exit = 0;
        return 1;
    }
    
    
    node_t *i = l->start;
    while (i->index != index)
    {
        if (i->next == NULL)
        {
            *exit = 0;
            return 0;
        }
        i = i->next;
    }
    *exit = i->value;
    return 1;
}


// troca ou adiciona um valor a lista pelo index
int update_by_index(list_t *l, elem new_value, int index)
{
    if (index<0)
    {
        return 0;
    }
    
    if (l->start == NULL)
    {
        insert(l, 0);
    }
    
    node_t *i = l->start;
    while (i->index != index)
    {
        if (i->next == NULL)
        {
            insert(l, 0);
        }
        i = i->next;
    }
    if (i == NULL)
    {
        insert(l, new_value);
    }
    else
    {
        i->value = new_value;
    }
    
    return 1;
}

// remove a primeira ocorrencia de um elemento na lista
int lremove_by_elem(list_t *l, elem cutter)
{

    node_t *i = l->start;
    node_t *prev;
    while (i != NULL)
    {
        if (i->value == cutter)
        {
            //printf("%d\n", i->value);
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

int remove_first(list_t *l)
{
    node_t *tmp;
    elem x = l->start->value;
    if (l->start != NULL)
    {
        tmp = l->start;
        l->start = l->start->next;
        free(tmp);
    }
    else
    {
        return -1;
    }
    return x;
}