#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "fila.h"

#define TamFila 100

typedef struct fila
{
    int inicio, fim, total;
    void **itens;
    int tamElem;
} fila_t;

fila_t *criar( int tamElem)
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
}