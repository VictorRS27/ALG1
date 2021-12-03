#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abb.h"

/*
 * Victor R. da Silva  nUSP: 12566140
 * 
 * TAD arvore binaria 
*/

//auxiliar para leitura de palavra
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
	arvore_t *T = criar();
	char *operator;
	int valor;
    
	while (1)
	{	
        //le o comando
		operator = read_word();
        
        //finaliza o loop de instrucoes
        if (eofReader == EOF)
        {
            break;
        }

        //executa insercoes
		if (strcmp(operator, "insercao") == 0)
		{
			scanf(" %d", &valor);
            getchar();
            //printf("%d\n", valor);
			inserir(&T->raiz, valor);
		}
		else
		{
			//le o tipo de impressao
			operator = read_word();
            
            //verifica a validade da impressao e executa
			if (esta_vazia(T))
			{
				printf("VAZIA\n");
			}
			else
			{
				if (strcmp(operator, "pre-ordem") == 0)
				{
					pre_ordem(T->raiz);
				    printf("\n");
				}
				else if (strcmp(operator, "em-ordem") == 0)
				{
					em_ordem(T->raiz);
				    printf("\n");
				}
				else if (strcmp(operator, "pos-ordem") == 0)
				{
					pos_ordem(T->raiz);
				    printf("\n");
				}
			}
			
		}
	}

    //destroi a arvore na memoria
	finalizar(T->raiz);

	
	return 0;
}