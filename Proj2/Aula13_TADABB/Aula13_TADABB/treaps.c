#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "treaps.h"

struct no
{
	no_t *esq, *dir;
	elem info;
	int prio;
};

arvore_t *criar()
{
	arvore_t *a = (arvore_t *)malloc(sizeof(arvore_t));
	a->raiz = NULL;
	return a;
}

int esta_vazia(arvore_t *a)
{
	assert(a != NULL);
	if (a->raiz == NULL)
		return 1;
	return 0;
}

void finalizar(no_t *raiz)
{
	if (raiz != NULL)
	{
		finalizar(raiz->esq);
		finalizar(raiz->dir);
		free(raiz);
	}
}

void imprimir(no_t *raiz)
{
	if (raiz != NULL)
	{
		printf("%d(", raiz->info);
		imprimir(raiz->esq);
		printf(",");
		imprimir(raiz->dir);
		printf(")");
	}
	else
	{
		printf("null");
	}
}

int altura(no_t *raiz)
{
	if (raiz == NULL)
		return 0;

	int alt_esq = 1 + altura(raiz->esq);
	int alt_dir = 1 + altura(raiz->dir);

	if (alt_esq > alt_dir)
		return alt_esq;
	else
		return alt_dir;
}

void pre_ordem(no_t *raiz)
{
	if (raiz != NULL)
	{
		printf("%d ", raiz->info);
		pre_ordem(raiz->esq);
		pre_ordem(raiz->dir);
	}
}

void em_ordem(no_t *raiz)
{
	if (raiz != NULL)
	{
		em_ordem(raiz->esq);
		printf("%d ", raiz->info);
		em_ordem(raiz->dir);
	}
}

void pos_ordem(no_t *raiz)
{
	if (raiz != NULL)
	{
		pos_ordem(raiz->esq);
		pos_ordem(raiz->dir);
		printf("%d ", raiz->info);
	}
}

void largura(no_t *raiz)
{
	assert(raiz);
	no_t **fila = (no_t **)malloc(sizeof(no_t *));
	int first = 0, last = 1;
	fila[0] = raiz;
	do
	{
		fila = realloc(fila, (last+2) * sizeof(no_t *));
		printf("%d ", fila[first]->info);
		first++;
		fila[last] = fila[last]->esq;
		last++;
		fila[last] = fila[last]->dir;
		last++;
	} while (first != last);
	free(fila);
}

int busca(no_t *raiz, elem x)
{
	if (raiz == NULL)
	{
		return 0;
	}
	else if (raiz->info == x)
	{
		return 1;
	}
	else if (x < raiz->info)
	{
		return busca(raiz->esq, x);
	}
	else
	{
		return busca(raiz->dir, x);
	}
}

// variavel global criada para economizar tempo de adaptar a funcao para retornar ponteiro
no_t *head;
// funcao recursiva para insercao subordianada a "inserir"
int inserir_treap(no_t **raiz, no_t *prev, int side, elem x, int y)
{
	no_t *tmp;
	if (*raiz == NULL)
	{
		*raiz = (no_t *)malloc(sizeof(no_t));
		(*raiz)->info = x;
		(*raiz)->prio = y;
		(*raiz)->esq = NULL;
		(*raiz)->dir = NULL;
		return 1;
	}
	else if (x == (*raiz)->info)
	{
		return 0;
	}
	else if (x < (*raiz)->info)
	{
		if (inserir_treap(&(*raiz)->esq, (*raiz), 1, x, y))
		{
			// rotação direita
			if ((*raiz)->esq->prio > (*raiz)->prio)
			{
				tmp = (*raiz);
				// esquema para mudara raiz em arvore
				if (prev != NULL)
				{
					if (side == 1)
					{
						prev->esq = (*raiz)->esq;
					}
					else
					{
						prev->dir = (*raiz)->esq;
					}
				}
				else
				{
					tmp->esq = (*raiz)->dir;
					(*raiz)->dir = tmp;
					head = (*raiz);
					return 2;
				}

				tmp->esq = (*raiz)->dir;
				(*raiz)->dir = tmp;
			}
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		if (inserir_treap(&(*raiz)->dir, (*raiz), 2, x, y))
		{
			// rotação esquerda
			if ((*raiz)->dir->prio > (*raiz)->prio)
			{
				tmp = (*raiz);
				if (prev != NULL)
				{
					if (side == 1)
					{
						prev->esq = (*raiz)->esq;
					}
					else
					{
						prev->dir = (*raiz)->esq;
					}
				}
				else
				{
					tmp->dir = (*raiz)->esq;
					(*raiz)->esq = tmp;
					head = (*raiz);
					return 2;
				}
				tmp->dir = (*raiz)->esq;
				(*raiz)->esq = tmp;
			}
			return 1;
		}
		else
		{
			return 0;
		}
	}
}

int inserir(arvore_t *raiz, elem x, int y)
{
	int exit = inserir_treap(&raiz->raiz, NULL, 0, x, y);
	if (exit == 2)
	{
		raiz->raiz = head;
		exit = 1;
	}
	return exit;
}

int remover(no_t **raiz, elem x)
{
	if (*raiz == NULL)
	{
		return 0;
	}
	else if (x < (*raiz)->info)
	{
		return remover(&(*raiz)->esq, x);
	}
	else if (x > (*raiz)->info)
	{
		return remover(&(*raiz)->dir, x);
	}
	else
	{
		if ((*raiz)->esq == NULL && (*raiz)->dir == NULL)
		{
			free(*raiz);
			*raiz = NULL;
			return 1;
		}
		else if ((*raiz)->esq == NULL)
		{
			no_t *aux = *raiz;
			*raiz = (*raiz)->dir;
			free(aux);
			return 1;
		}
		else if ((*raiz)->dir == NULL)
		{
			no_t *aux = *raiz;
			*raiz = (*raiz)->esq;
			free(aux);
			return 1;
		}
		else
		{
			no_t *aux = (*raiz);
			if ((*raiz)->esq->prio < (*raiz)->dir->prio)
			{
				(*raiz) = (*raiz)->dir;
				aux->dir = (*raiz)->esq;
				(*raiz)->esq = aux;
				return remover(&(*raiz)->esq, x);
			}
			else
			{
				(*raiz) = (*raiz)->esq;
				aux->esq = (*raiz)->dir;
				(*raiz)->dir = aux;
				return remover(&(*raiz)->dir, x);
			}
		}
	}
}
