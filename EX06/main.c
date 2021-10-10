#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/*
 * Victor Rodrigues da Silva  No 12566140
 * 
 * 
 * recebe os dados para uma lista encadeada circular de inteiros
 * e o total de rotacoes individuais
 * retorna a lista atualizada
*/

int main(int argc, char const *argv[])
{
    int i, j, times, size, rotations, number;
    list_t *numbers;

    numbers = create();

    scanf("%i", &times);

    //repete a leitura de uma lista diferente
    for (i = 0; i < times; i++)
    {
        //recebe os dados
        scanf(" %i", &size);
        scanf(" %i", &rotations);
        for ( j = 0; j < size; j++)
        {
            scanf(" %i", &number);
            insert(numbers, number);
        }
        //saida da lista
        rotate_left(numbers, rotations);
        print(numbers);
        printf("\n");
        clear(numbers);
    }

    destroy(numbers);
    
    return 0;
}
