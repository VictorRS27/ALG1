#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/*
 * Victor R. da Silva  nUSP: 12566140
 * 
 * Programa para leitura de N polinomios e a soma de seus coeficientes
 */

int main(int argc, char const *argv[])
{
    list_t **poli, *soma;
    int tests, total_polis, reader, som1=1, som2=2;
    
    //repete os testes de cada caso
    scanf("%d", &tests);
    for (int i = 0; i < tests; i++)
    {
        //repete a cada polinomio a ser somado
        scanf(" %d", &total_polis);
        poli = malloc(total_polis * sizeof(list_t *));
        for (int j = 0; j < total_polis; j++)
        {
            //leitura e inserção dos polinomios
            getchar();
            getchar();
            poli[j] = create();
            while (getchar() != ')')
            {
                scanf(" %d", &reader);
                insert(poli[j], reader);
            }
            
        }
        //cria a lista soma e percorre os polinomios somando cada 
        //coeficiente de seus respectivos expoentes(indexes) 
        soma = create();
        for (int j = 0; j < total_polis; j++)
        {
            for (int k = 0; k < size(poli[j]); k++)
            {
                query_by_index(poli[j], &som1, k);
                query_by_index(soma, &som2, k);
                update_by_index(soma, som1+som2, k);
            }      
        }
        //exitbe a soma formatada
        printf("(");
        print(soma);
        printf(")\n"); 

        //livra variaveis
        for (int j = 0; j < total_polis; j++)
        {
            destroy(poli[j]);
        }
        destroy(soma);

    }
    
    return 0;
}
