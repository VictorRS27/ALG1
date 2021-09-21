#include <stdio.h>
#include <stdlib.h>

#define LIMIT 10000
struct no
{
    long int value;
    struct no *next;
};

struct no *start, *end, *primes;

void cutMupliers(struct no *primes)
{
    int divider = primes->value;
    struct no *cutter = primes, *tmp;

    while (cutter != NULL && cutter->next != NULL)
    {
        if (cutter->next->value % divider == 0)
        {
            tmp = cutter->next->next;
            free(cutter->next);
            cutter->next = tmp;
        }
        cutter = cutter->next;
    }
}

int main(void)
{
    int i , j, totalToShow;
    start = NULL;
    end = NULL;
    primes = (struct no *)malloc(sizeof(struct no));
    primes->value = 2;
    primes->next = NULL;
    start = primes;
    end = primes;

    for (i = 3; i <= LIMIT; i++)
    {
        primes = (struct no *)malloc(sizeof(struct no));
        primes->value = i;
        primes->next = NULL;
        end->next = primes;
        end = primes;
    }

    primes = start;
    while (primes->next != NULL)
    {
        cutMupliers(primes);
        primes = primes->next;
    }

    
    scanf("%d", &totalToShow);
    long int *valuesToShow = malloc(totalToShow * sizeof(long int));
    for ( i = 0; i < totalToShow; i++)
    {
        scanf(" %li", &valuesToShow[i]);
        primes = start;
        for ( j = 1; j < valuesToShow[i]; j++)
        {
            primes = primes->next;
        }
        valuesToShow[i] = primes->value;       
    }
    
    for ( i = 0; i < totalToShow; i++)
    {
        printf("%li ", valuesToShow[i]);
        
    }
    free(valuesToShow);

    primes = start;
    while (primes != NULL)
    {
        start = start->next;
        free(primes);
        primes = start;
    }
    return 0;
}