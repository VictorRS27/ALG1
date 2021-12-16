#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treaps.h"

/*
 * Victor R. da Silva  nUSP: 12566140
 * 
 * TAD arvore treaps
*/

//funacao auxiliar para leitura
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

int main(void) {
	arvore_t *a = criar();
	int total_cmds, key, prio;
	char *cmd;

	scanf(" %d", &total_cmds);
	getchar();

	for (int i = 0; i < total_cmds; i++)
	{
		cmd = read_word();
		if (strcmp(cmd, "insercao") == 0)
		{
			scanf(" %d %d", &key, &prio);
			getchar();
			if(inserir(a, key, prio) == 0)
			{
				printf("”Elemento ja existente\n");
			}
		}
		else if (strcmp(cmd, "impressao") == 0)
		{
			cmd = read_word();
			if (strcmp(cmd, "preordem") == 0)
			{
				pre_ordem(a->raiz);
			}
			else if (strcmp(cmd, "ordem") == 0)
			{
				em_ordem(a->raiz);
			}
			else if (strcmp(cmd, "posordem") == 0)
			{
				pos_ordem(a->raiz);
			}
			else
			{
				largura(a->raiz);
			}
		}
		else if (strcmp(cmd, "remocao") == 0)
		{
			scanf(" %d", &key);
			getchar();
			remover(&a->raiz, key);
		}
		else if (strcmp(cmd, "busca") == 0)
		{
			scanf(" %d", &key);
			getchar();
			busca(a->raiz, key);
		}
	}
	


	
	
	free(cmd);
	finalizar(a->raiz);
	return 0;
}