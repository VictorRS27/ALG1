#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "text.h"

#define MIN(a,b) ((a) < (b) ? (a) : (b))

/*
 * Victor Rodrigues da Silva  No 12566140
 * 
 * 
 * Le um texto e exibe um valor x informado das palavras mais frequentes e suas respectivas totais ocorrencias
*/

int main(int argc, char const *argv[])
{
    int i, show_repetitions, total_to_show;
    char *show_word, exit;
    text_t *phrase;

    phrase = create();
    //repete as frases ate EOF
    do
    {
        read_text(phrase);
        scanf("%i", &total_to_show);
        total_to_show = MIN(total_to_show, size(phrase));
        //retira oos dados da palavras mais frequente e escreve
        for ( i = 0; i < total_to_show; i++)
        {
            show_word = remove_usual(phrase, &show_repetitions);
            printf("%s %d\n", show_word, show_repetitions);
        }
        exit = getchar();
        //controla a separacao de linha no final
        if (exit != EOF)
        {
            printf("\n");
        }
        
    } while (exit != EOF);
    destroy(phrase);
    return 0;
}
