#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main(int argc, char const *argv[])
{
    list_t **poli, *soma;
    int tests, total_polis, reader, som1=1, som2=2;
    
    scanf("%d", &tests);
    for (int i = 0; i < tests; i++)
    {
        scanf(" %d", &total_polis);
        poli = malloc(total_polis * sizeof(list_t *));
        for (int j = 0; j < total_polis; j++)
        {
            getchar();
            getchar();
            poli[j] = create();
            while (getchar() != ')')
            {
                scanf(" %d", &reader);
                //printf("%d ", reader);
                insert(poli[j], reader);
            }
            /* printf("(");
            print(poli[j]);
            printf(")"); */
            
        }
        soma = create();
        for (int j = 0; j < total_polis; j++)
        {
            //printf("polinomio j: %d\n", j);
            for (int k = 0; k < size(poli[j]); k++)
            {
                query_by_index(poli[j], &som1, k);
                query_by_index(soma, &som2, k);
                //printf("%d %d\n", som1, som2);
                update_by_index(soma, som1+som2, k);
            }    
            
            /* printf("(");
            print(soma);
            printf(")");  */       
        }
        printf("(");
        print(soma);
        printf(")\n"); 
        for (int j = 0; j < total_polis; j++)
        {
            destroy(poli[j]);
        }
        destroy(soma);

    }
    
    return 0;
}
