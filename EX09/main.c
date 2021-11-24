#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "big_numbers_list.h"

/*
 * Victor R. da Silva  nUSP: 12566140
 * 
 * TAD para operacoes basicas com numeros maiores que o limite em bytes
*/

//funcao para a leitura de palavra
int eofReader;
char *read_word()
{
    int i = -1;
    char *line = malloc(sizeof(char));
    do
    {
        i++;
        eofReader = getchar();
        line[i] = eofReader;
        if (i == 0 && (line[i] == '\n' || line[i] == '\r'))
        {
            line[i] = getchar();
        }
        
        if (line[i] == ' ' || line[i] == '\n' || line[i] == '\r' || eofReader == EOF)
        {
            line[i] = '\0';
        }
        else
        {
            line = realloc(line, (i + 2) * sizeof(char));
        }
    } while (line[i] != '\0' && eofReader != EOF);
    return line;
}

int main(int argc, char const *argv[])
{
    int total_tests, reader;
    scanf(" %d", &total_tests);
    getchar();
    char *operation;
    list_t *num1, *num2, *result = NULL;
    
    //repete o numero de operacoes
    for (int i = 0; i < total_tests; i++)
    {
        operation = read_word();
        num1 = create();
        num2 = create();
        
        //leitura dos numeros 
        reader = getchar();
        while (reader != ' ')
        {
            insert(num1, reader);
            reader = getchar();
        } 
            reader = getchar();
        while (reader != '\n')
        {
            insert(num2, reader);
            reader = getchar();
        } 

        printf("%s\n", operation);
        print(num1);
        print(num2);

        //chamadas das respectivas funcoes
        /* if (strcmp(operation, "SUM") == 0)
        {
            result = create();
            result = sum(num1, num2, result);
            print(result);
            destroy(result);
        }
        else */if (strcmp(operation, "BIG") == 0)
        {
            printf("%d\n", is_bigger(num1, num2));
        }
        else if (strcmp(operation, "SML") == 0)
        {
            printf("%d\n", is_smaller(num1, num2));
        }
        else if (strcmp(operation, "EQL") == 0)
        {
            printf("%d\n", is_equal(num1, num2));
        }
        
        printf("\n");
        free(operation);
        destroy(num1);
        destroy(num2);
        destroy(result);
    }
    

    return 0;
}
