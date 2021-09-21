#include <stdio.h>
#include <stdlib.h>
#include "list.h"

struct node
{
    elem value;
    struct node *next;
};

struct list
{
    struct node_t *start, *end;
};
