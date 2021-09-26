#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

char *read_line()
{
    int i = 0, eofReader;
    char *line = malloc(sizeof(char));
    do
    {
        eofReader = getchar();
        line[i] = eofReader;
        if (line[i] == '\n' || line[i] == '\r' || eofReader == EOF)
        {
            line[i] = '\0';
        }
        else
        {
            line = realloc(line, (i + 2) * sizeof(char));
        }
        i++;
    } while (line[i - 1] != '\0' && eofReader != EOF);
    return line;
}

int main(int argc, char const *argv[])
{
    list_t *phrase;
    char *mistake, *correction;
    int eof_reader, i = -1, j;

    do
    {
        phrase = create();
        do
        {
            eof_reader = getchar();
            if (eof_reader == EOF)
            {
                destroy(phrase);
                exit(0);
            }
            insert(phrase, (char)eof_reader);
        } while ('\n' != (char)eof_reader);

        mistake = read_line();
        correction = read_line();

        while (j != 0)
        {
            replace(phrase, mistake, correction);
        }
        
        for (j = 0; j < size(phrase); j++)
        {
            printf("%c", query_index(phrase, j));
        }

        printf("\n");

        free(mistake);
        free(correction);
        destroy(phrase);

    } while (eof_reader != EOF);

    return 0;
}
