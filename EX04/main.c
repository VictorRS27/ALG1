#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "fila.h"
/*
#define TamFila 100

typedef struct fila
{
    int inicio, fim, total;
    void **itens;
    int tamElem;
} fila_t;

fila_t *criar(int tamElem)
{
    fila_t *f;
    f = (fila_t *)malloc(sizeof(fila_t));
    f->itens = malloc(sizeof(void *) * TamFila);
    f->tamElem = tamElem;
    f->total = 0;
    f->inicio = 0;
    f->fim = 0;
    return f;
}

int isEmpty(fila_t *f)
{
    if (f == NULL)
    {
        return 1;
    }

    if (f->total == 0)
        return 1;
    return 0;
}

int isFull(fila_t *f)
{
    if (f->total == TamFila)

        return 1;
    return 0;
}

int inserir(fila_t *f, void *x)
{
    if (isFull(f) == 1)
        return 0;
    f->total++;
    f->itens[f->fim] = malloc(f->tamElem);
    memcpy(f->itens[f->fim], x, f->tamElem);
    f->fim = (f->fim + 1) % TamFila;
    return 1;
}

int remover(fila_t *f, void *x)
{
    if (isEmpty(f) == 1)
        return 0;
    memcpy(x, f->itens[f->inicio], f->tamElem);
    free(f->itens[f->inicio]);
    f->inicio = (f->inicio + 1) % TamFila;
    f->total--;
    return 1;
}

void destruir(fila_t *f)
{
    while (f->inicio % TamFila < f->fim % TamFila)
    {
        free(f->itens[f->inicio]);
        f->inicio++;
    }
    free(f->itens);
    if (f != NULL)
        free(f);
}*/

typedef struct patient
{
    char *name;
    int condition, age;
} Patient;

char *read_line()
{
    int i = 0, eofReader;
    char *line = malloc(sizeof(char));
    do
    {
        eofReader = getchar();
        line[i] = eofReader;
        if (line[i] == '\n' || line[i] == '\r' || line[i] == ' ')
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

void freeNames(fila_t *queue)
{
    Patient liberator;
    while (!isEmpty(queue))
    {
        remover(queue, &liberator);
        free(liberator.name);
    }
}

int main(int argc, char const *argv[])
{
    fila_t *olderSick = NULL, *older = NULL, *sick = NULL, *normal = NULL;
    Patient in_out_patient;
    char *comand;
    int operations, i = 0;

    olderSick = criar(sizeof(Patient));
    older = criar(sizeof(Patient));
    sick = criar(sizeof(Patient));
    normal = criar(sizeof(Patient));

    scanf("%d\n", &operations);

    do
    {
        //Foi a forma que encontre para ler tudo corretamente, nao sei pq mas
        //somente limpar o buffer com getchar e fflush nao funciona
        //Como ler nao eh o foco do exercicio, ignorem esse rudeza
        do
        {
            comand = read_line();
        } while ((comand[0] == '\n' || comand[0] == '\0'));

        if (strstr(comand, "SAI"))
        {
            if (!isEmpty(olderSick))
            {
                remover(olderSick, &in_out_patient);
                printf("%s %d %d\n", in_out_patient.name, in_out_patient.age, in_out_patient.condition);
                free(in_out_patient.name);
            }
            else if (!isEmpty(sick))
            {
                remover(sick, &in_out_patient);
                printf("%s %d %d\n", in_out_patient.name, in_out_patient.age, in_out_patient.condition);
                free(in_out_patient.name);
            }
            else if (!isEmpty(older))
            {
                remover(older, &in_out_patient);
                printf("%s %d %d\n", in_out_patient.name, in_out_patient.age, in_out_patient.condition);
                free(in_out_patient.name);
            }
            else if (!isEmpty(normal))
            {
                remover(normal, &in_out_patient);
                printf("%s %d %d\n", in_out_patient.name, in_out_patient.age, in_out_patient.condition);
                free(in_out_patient.name);
            }
            else
            {
                printf("FILA VAZIA\n");
            }
        }
        else
        {
            in_out_patient.name = read_line();
            scanf(" %d %d\n", &in_out_patient.age, &in_out_patient.condition);

            if (in_out_patient.condition == 1)
            {
                if (in_out_patient.age >= 60)
                {
                    inserir(olderSick, (void *)&in_out_patient);
                }
                else
                {
                    inserir(sick, (void *)&in_out_patient);
                }
            }
            else if (in_out_patient.age >= 60)
            {
                inserir(older, (void *)&in_out_patient);
            }
            else
            {
                inserir(normal, (void *)&in_out_patient);
            }
        }
        i++;
    } while (i < operations);

    free(comand);
    freeNames(olderSick);
    freeNames(sick);
    freeNames(older);
    freeNames(normal);

    destruir(olderSick);
    destruir(older);
    destruir(sick);
    destruir(normal);

    return 0;
}
