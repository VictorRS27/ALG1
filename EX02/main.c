#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main(int argc, char const *argv[])
{
    list_t *l = create();
    int i, j, operations, operator, tmp;

    for ( i = 1; i < 10000; i++)
    {
        insert(l, i);
    }

    //printf("%li ", query_index(l, 3));

    for ( i = 2; i < size(l); i++)
    {
        for ( j = i+1; j < size(l); j++)
        {
            tmp = query_index(l, j);
            if (tmp % i == 0)
            {
                lremove_by_elem(l, tmp);
            }
        }
    }

    //print(l);
    
    scanf("%i", &operations);

    for ( i = 0; i < operations; i++)
    {
        scanf(" %i", &operator);
        printf("%li ", query_index(l, operator));
    }
    

    destroy(l);
    return 0;
}

