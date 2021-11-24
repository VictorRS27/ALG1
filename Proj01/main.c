#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "skip_list.h"

/*
 * Victor R. da Silva  nUSP: 12566140
 * 
 * Tentativa de montar uma skiplist, montei todas as funcoes, porem nem todas funcionam e nao consegui corrigir a tempo de montar a main
*/

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

typedef struct 
{
    char *word, *definition;
}entry_t;

int main(int argc, char const *argv[])
{
    char *reader = read_word();
    entry_t entry, *out;
    entry.word = reader;
    entry.definition = NULL;
    skip_list_t *dictionary;
    dictionary = create();
    insert(dictionary, &entry, entry.word);
    out = (entry_t *)remove_elem(dictionary, entry.word);
    printf("%p\n", out);
    destroy(dictionary);

    return 0;
}
