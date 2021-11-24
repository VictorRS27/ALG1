#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "skip_list.h"

#define MAX(a, b) (a > b) ? a : b

typedef struct node
{
    void *cargo;
    elem reference;
    struct node *next, *down;
    int level;
} node_t;

struct skip_list
{
    node_t *up_left;
    int size;
};

skip_list_t *create()
{
    skip_list_t *sl = malloc(sizeof(skip_list_t));

    node_t *header = malloc(sizeof(node_t));
    header->reference = NULL;
    header->next = NULL;
    header->down = NULL;
    header->level = 0;

    sl->up_left = header;
    sl->size = 1;
    return sl;
}

void *search(skip_list_t *sl, elem target)
{
    node_t *sentinel = sl->up_left;

    while (sentinel->level > 0)
    {
        while (sentinel->next != NULL && strcmp(sentinel->next->reference, target) < 0)
        {
            sentinel = sentinel->next;
        }
        sentinel = sentinel->down;
    }

    while (sentinel->next != NULL && strcmp(sentinel->next->reference, target) < 0)
    {
        sentinel = sentinel->next;
    }

    //printf("%p", sentinel->reference);

    if (sentinel->reference != NULL && strcmp(sentinel->reference, target) != 0)
    {
        return NULL;
    }
    else
    {
        return sentinel->cargo;
    }
}

void **search_occurrence(skip_list_t *sl, char target)
{
    node_t *sentinel = sl->up_left;

    while (sentinel->level > 0)
    {

        while (sentinel != NULL && sentinel->reference[0] == target)
        {
            sentinel = sentinel->next;
        }

        sentinel = sentinel->down;
    }

    int i=0;
    void **exit = malloc(sizeof(void*));
    while (sentinel != NULL && sentinel->reference[0] == target)
    {
        exit[i] = sentinel->cargo;
        sentinel = sentinel->next;
    }
    return exit;
}

void free_occurrence_exit(void **exit)
{
    free(exit);
}

int raffle()
{
    srand(time(NULL));
    int exit = 0, raffler;
    do
    {
        raffler = rand();
        exit++;
    } while (raffler%2 == 0);
    return 7;
}

node_t *create_node(elem reference, node_t *down, node_t *next, int level)
{
    node_t *exit = malloc(sizeof(node_t));
    exit->reference = reference;
    exit->down = down;
    exit->next = next;
    exit->level = level;
    return exit;
}

void create_new_level(skip_list_t *sl)
{
    node_t *new_top = malloc(sizeof(node_t));
    new_top->reference = NULL;
    new_top->next = NULL;
    new_top->level = sl->up_left->level + 1;
    new_top->down = sl->up_left;
    sl->up_left = new_top;
    sl->size++;
}

int insert(skip_list_t *sl, void *cargo, elem value)
{
    if (sl == NULL || search(sl, value) != NULL)
    {
        return 0;
    }

    int curr_level = 0, max_level = raffle();
    node_t *sentinel = sl->up_left;
    node_t **lowers = malloc((MAX(max_level, sl->size)+1) * sizeof(node_t *));

    while (sentinel->level > 0)
    {

        while (sentinel->next != NULL && strcmp(sentinel->next->reference, value) < 0)
        {
            sentinel = sentinel->next;
        }
        lowers[sentinel->level] = sentinel;
        sentinel = sentinel->down;
    }

    //printf("%p, %p, %d", sentinel, sentinel->next, sentinel->level);
    while (sentinel->next != NULL && strcmp(sentinel->next->reference, value) < 0)
    {
        sentinel = sentinel->next;
    }
    lowers[sentinel->level] = sentinel;

    for (int i = 0; i < sl->size; i++)
    {
        printf("%p, %p\n", lowers[i], lowers[i]->reference);
        sentinel = sentinel->down;
    }

    node_t *new;
    while (curr_level < sl->size && curr_level < max_level)
    {
        //printf("%i, %i, %i, %d\n", curr_level, sl->size, max_level, MAX(max_level, sl->size) );
        new = create_node(value, NULL, NULL, curr_level);
        if (curr_level == 0)
        {
            new->down = NULL;
            new->cargo = cargo;
        }
        else
        {
            new->down = lowers[curr_level - 1]->next;
        }
        new->next = lowers[curr_level]->next;
        lowers[curr_level]->next = new;
        curr_level++;
    }

    for (int i = 0; i < sl->size; i++)
    {
        printf("%p, %p\n", lowers[i], lowers[i]->reference);
        sentinel = sentinel->down;
    }
    
    while (curr_level < max_level)
    {
        create_new_level(sl);
        //printf("%d, %d, %d, %p\n", curr_level, sl->size, max_level, lowers[curr_level - 1]->next->reference);
        sl->up_left->next = create_node(value, lowers[curr_level - 1]->next, NULL, curr_level);
        lowers[curr_level] = sl->up_left;
        curr_level++;
    }

    free(lowers);
    return 1;
}

void remove_next(node_t *prev)
{
    node_t *aux;
    if (prev->next != NULL)
    {
        aux = prev->next->next;
        free(prev->next);
        prev->next = aux;;
    }
}

void *remove_elem(skip_list_t *sl, elem value)
{
    if (sl == NULL || search(sl, value) == NULL)
    {
        return NULL;
    }

    int curr_level = 0;
    node_t *sentinel = sl->up_left;
    node_t **lowers = malloc((sl->size+1) * sizeof(node_t *));

    while (sentinel->level > 0)
    {

        while (sentinel->next != NULL && strcmp(sentinel->next->reference, value) < 0)
        {
            sentinel = sentinel->next;
        }
        lowers[sentinel->level] = sentinel;
        sentinel = sentinel->down;
    }

    while (sentinel->next != NULL && strcmp(sentinel->next->reference, value) < 0)
    {
        sentinel = sentinel->next;
    }
    lowers[sentinel->level] = sentinel;

    sentinel = sl->up_left;

    for (int i = 0; i < sl->size; i++)
    {
        printf("%p, %p", lowers[i], sentinel);
        sentinel = sentinel->down;
    }
    
    void *exit = lowers[0]->cargo;

    while (curr_level < sl->size)
    {
        if (lowers[curr_level]->next != NULL && strcmp(lowers[curr_level]->next->reference, value) == 0)
        {
            remove_next(lowers[curr_level]);
        }
        curr_level++;
    }
    free(lowers);
    return exit;
}

void destroy(skip_list_t *sl)
{
    node_t *tmp1, *tmp2, *sentinel;
    while (sl->up_left != NULL)
    {
        sentinel = sl->up_left;
        tmp2 = sl->up_left->down;
        while (sentinel != NULL)
        {
            tmp1 = sentinel->next;
            free(sentinel);
            sentinel = tmp1;
        }
        sl->up_left = tmp2;
    }
    free(sl);
}