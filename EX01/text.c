#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "text.h"

//define o tipo palavra que contem a palavra e seu total de repeticoes
typedef struct word
{
    char *word;
    int repetitions;
} word_t;

//cria text como o tipo de dado que armazenara as palavras e to total de palavras
struct text
{
    word_t *words;
    int size, size_to_desaloc;
};

//cria um texto e aloca o espaco da primeira palavra, ainda vazia
text_t *create()
{
    text_t *t;
    t = (text_t *)malloc(sizeof(text_t));
    t->words = (word_t *)malloc(sizeof(word_t));
    t->words->repetitions = 0;
    t->size = 0;
    return t;
}

//auxiliar para ler uma palavra ate ' ', aloca-la e devolver o ponteiro para o inicio 
char *read_word(char *end_line)
{
    int i = 0;
    char *word = malloc(sizeof(char));
    do
    {
        *(end_line) = getchar();
        word[i] = *(end_line);
        if (word[i] == '\r')
        {
            word[i] = '\n';
        }

        if (word[i] == ' ' || word[i] == '\n')
        {
            word[i] = '\0';
        }
        else
        {
            word = realloc(word, (i + 2) * sizeof(char));
        }
        i++;
    } while (word[i - 1] != '\0');
    
    return word;
}

//insertion sort usado para ordenar as repeticoes em ordem crescente e secundariamente em ordem alfabetica das palavras
void insertion_sort(text_t *t)
{
    int i, change = 1;
    word_t tmp;

    while (change == 1)
    {
        change = 0;
        for (i = 0; i < t->size - 1; i++)
        {
            if (strcmp(t->words[i].word, t->words[i+1].word)<0)
            {
                change = 1;
                tmp = t->words[i];
                t->words[i] = t->words[i+1];
                t->words[i+1] = tmp;
            } 
        }
    }
    change = 1;
    while (change == 1)
    {
        change = 0;
        for (i = 0; i < t->size - 1; i++)
        {
            if (t->words[i].repetitions > t->words[i + 1].repetitions)
            {
                change = 1;
                tmp = t->words[i];
                t->words[i] = t->words[i + 1];
                t->words[i + 1] = tmp;
            }
        }
    }
}

//le um texto alocando suas palavras diferentes, contabilizando as repeticoes ordenando com a funcao anterior
void read_text(text_t *t)
{
    int i = 0, j, found;
    char end_line;
    t->words[0].word = read_word(&end_line);
    if (0 == (int)t->words[i].word[0])
    {
        t->words[0].word = read_word(&end_line);
    }
    
    t->words[0].repetitions = 1;
    t->size = 0;
    do
    {
        found = 0;
        i++;
        t->words = (word_t *)realloc(t->words, (i + 1) * sizeof(word_t));
        t->words[i].word = read_word(&end_line);
        t->words[i].repetitions = 1;
        for (j = (i - 1); j >= 0; j--)
        {
            if (strcmp(t->words[i].word, t->words[j].word) == 0)
            {
                t->words[j].repetitions++;
                found = 1;
                free(t->words[i].word);
            }
        }
        if (found == 1 && end_line != '\n')
        {
            i--;
        }
        else
        {
            t->size++;
        }

    } while (end_line != '\n');
    t->size_to_desaloc = t->size;
    insertion_sort(t);
}

//retorna o total de palavras no texto
int size(text_t *t)
{
    return t->size;
}

//retira a palavra mais frequente de acesso 
char *remove_usual(text_t *t, int *repetitions)
{
    t->size--;
    *(repetitions) = t->words[t->size].repetitions;
    return t->words[t->size].word;
}

//livra cada palavra, depois o vetor palavras e por fim o texto
void destroy(text_t *t)
{
    int i;
    for (i = 0; i < t->size_to_desaloc; i++)
    {
        free(t->words[i].word);
    }
    free(t->words);
    free(t);
}
