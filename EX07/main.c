#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

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

char *read_line()
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
        
        if (line[i] == '\r' || line[i] == '\n' || eofReader == EOF)
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
    char *comand, **names_database = malloc(100*sizeof(char *));
    int reader, names_counter = 0;
    list_t *codes = create();
    

    while (eofReader != EOF)
    {
        comand = read_word();
        if (strcmp(comand, "INSERE") == 0)
        {
            scanf(" %d", &reader);
            getchar();
            if(!insert(codes, reader))
            {
                printf("INVALIDO\n");
            }
            else
            {
            names_counter++;
            names_database[reader] = read_line();
            //printf("inseri %s em %d\n", names_database[reader], reader);
            }            
        }
        else if (strcmp(comand, "REMOVE") == 0)
        {
            scanf(" %d", &reader);
            getchar();
            //printf("%d %d\n", lremove_by_elem(codes, reader), reader);
            if(!lremove_by_elem(codes, reader))
            {
                printf("INVALIDO\n");
            }
            else
            {
            names_counter--;            
            //printf("removi %s em %d\n", names_database[reader], reader);
            free(names_database[reader]);                
            }
        }
        else if (strcmp(comand, "IMPRIMIR") == 0)
        {
            if(names_counter != 0)
            {
                for (int i = 0; i < names_counter; i++)
                {                    
                    reader = query_index(codes, i);
                    printf("%d, %s", reader, names_database[reader]);
                    printf("; ");
                }
                printf("\n");
            }
            else
            {
                printf("VAZIA");
            }
            
        }
    }

    for (int i = 0; i < names_counter; i++)
    {
        reader = query_index(codes, i);
        free(names_database[reader]);
    }
    free(names_database);
    destroy(codes);
    return 0;
}
