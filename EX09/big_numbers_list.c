#include <stdio.h>
#include <stdlib.h>
#include "big_numbers_list.h"

typedef struct node
{
    elem value;
    int index;
    struct node *next;
} node_t;

struct list
{
    node_t *start, *end;
    int size;
};

list_t *create()
{
    list_t *l;
    l = (list_t *)malloc(sizeof(list_t));

    l->end = NULL;
    l->start = NULL;
    l->size = 0;
}

void destroy(list_t *l)
{
    if (l != NULL)
    {
        node_t *i = l->start;
        while (i != NULL)
        {
            l->start = i->next;
            free(i);
            i = l->start;
        }
        free(l);
    }
}


int insert(list_t *l, elem x)
{
    node_t *i = (node_t *)malloc(sizeof(node_t));

    if (l == NULL || i == NULL)
        return 0;

    i->value = x;
    i->next = NULL;
    i->index = l->size;

    if (l->start == NULL)
    {
        l->start = i;
        l->end = i;
    }
    else
    {
        l->end->next = i;
    }
    l->end = i;

    l->size++;
    return 1;
}


int size(list_t *l)
{
    return l->size;
}

int print(list_t *l)
{
    if (l == NULL)
        return 0;

    node_t *i = l->start;
    while (i != NULL)
    {
        printf("%c", i->value);
        i = i->next;
    }
    printf("\n");
}

int is_in_list(list_t *l, elem x)
{
    if (l == NULL)
        return -1;

    node_t *i = l->start;
    while (i != NULL)
    {
        if (i->value == x)
        {
            return 1;
        }
        i = i->next;
    }
    return 0;
}

//auxiliar para limpar os zeros a esquerda
void clear_zeros(list_t *t)
{
    node_t *tmp, *i = t->start;
    if (t->start->value != '-')
    {
        while (i->value == (char)0)
        {
            t->start = i->next;
            free(i);
            i = t->start;
        }
    }
    else
    {
        i = i->next;
        while (i->value == (char)0)
        {
            t->start->next = i->next;
            free(i);
            i = t->start->next;
        }
    }
    
    
    
}

//diz se um numero em lista é maior q o outro
int is_bigger(list_t *t1, list_t *t2)
{
    clear_zeros(t1);
    clear_zeros(t2);
    //verifica tamanho e sinal entre os numeros
    if (t1->start->value == '-' && t2->start->value != '-')
    {
        return 0;
    }
    if (t1->start->value != '-' && t2->start->value == '-')
    {
        return 1;
    }
    if (t1->end->index < t2->end->index)
    {
        return 0;
    }
    if (t1->end->index > t2->end->index)
    {
        return 1;
    }
    //se iguais passa a verificar numero a numero
    node_t *count_t1 = t1->start, *count_t2 = t2->start;
    while (count_t1 != t1->end)
    {
        if (count_t1->value != '-')
        {
            if ( (int)count_t2->value > (int)count_t1->value)
            {
                return 0;
            }
            if ( (int)count_t2->value < (int)count_t1->value)
            {
                return 1;
            }
            count_t1 = count_t1->next;
            count_t2 = count_t2->next;
        }
        
    }
    return 0;
}

//verifica se m numero em lista é menor que o outro
int is_smaller(list_t *t1, list_t *t2)
{
    clear_zeros(t1);
    clear_zeros(t2);
    //verifica tamanho e sinal entre os numeros
    if (t1->start->value == '-' && t2->start->value != '-')
    {
        return 1;
    }
    if (t1->start->value != '-' && t2->start->value == '-')
    {
        return 0;
    }
    if (t1->end->index < t2->end->index)
    {
        return 1;
    }
    if (t1->end->index > t2->end->index)
    {
        return 0;
    }
    
    //se iguais passa a verificar numero a numero
    node_t *count_t1 = t1->start, *count_t2 = t2->start;
    while (count_t1 != NULL )
    {
        if (count_t1->value != '-')
        {
            if ( (int)count_t2->value > (int)count_t1->value)
            {
                return 1;
            }
            if ( (int)count_t2->value < (int)count_t1->value)
            {
                return 0;
            }
            count_t1 = count_t1->next;
            count_t2 = count_t2->next;
        }
        
    }
    return 0;
}

//verifica se dois numeos sao iguais
int is_equal(list_t *t1, list_t *t2)
{
    clear_zeros(t1);
    clear_zeros(t2);
    node_t *count_t1 = t1->start, *count_t2 = t2->start;
    //verificacoes de sinal e tamanho
    if (t1->end->index == t2->end->index )
    {
        if ((t1->start->value != '-' && t2->start->value != '-') || (t1->start->value == '-' && t2->start->value == '-'))
        {
            //verificacoes individuais
            while (count_t1 != t1->end)
            {
                if (count_t1->value != count_t2->value)
                {
                    return 0;
                }
                count_t1 = count_t1->next;
                count_t2 = count_t2->next;
            }
            
        }
        else
        {
            return 0;
        }
        
    }
    else
    {
        return 0;
    }
    return 1;
}

//soma dois numeros em lista
//errada pois fiz a logica para caso a lista comecasse da direita
//nao tive tempo de corrigir depois que percebi que era ao contrario
list_t *sum(list_t *t1, list_t *t2, list_t *result)
{
    int sobra = 0, parcial_result = 0;
    node_t *count_t1 = t1->start, *count_t2 = t2->start, *count_result = result->start;

    //soma dois numeros positivos
    if ((t1->start->value != '-' && t2->start->value != '-'))
    {
        
        //soma até onde tem o mesmo tamanho
        while (count_t1 != NULL && count_t2 != NULL)
        {
            parcial_result = ((int)count_t2->value + (int)count_t1->value) + sobra;
            sobra = parcial_result /10;
            insert(result, (char) parcial_result - sobra * 10  );
            count_t1 = count_t1->next;
            count_t2 = count_t2->next;
        }
        //insere no resultado as casas que um numero possa ter a mais q o outro
        while (count_t2 != NULL)
        {
            insert(result, (char)((int)count_t2->value + sobra));
            sobra = 0;
            count_t2 = count_t2->next;
        }
        while (count_t1 != NULL)
        {
            insert(result, (char)((int)count_t1->value + sobra));
            sobra = 0;
            count_t1 = count_t1->next;
        }
        //adiciona a sobra da soma
        if (sobra != 0)
        {
            insert(result, (char)sobra);
        }
        return result;
    }

    //soma dois numeros negativos
    if ((t1->start->value == '-' && t2->start->value == '-'))
    {
        count_t1 = count_t1->next;
        count_t2 = count_t2->next;
        //soma até onde tem o mesmo tamanho
        while (count_t1 != NULL && count_t2 != NULL)
        {
            parcial_result = ((int)count_t2->value + (int)count_t1->value) + sobra;
            sobra = parcial_result /10;
            insert(result, (char) parcial_result - sobra * 10  );
            count_t1 = count_t1->next;
            count_t2 = count_t2->next;
        }
        //insere no resultado as casas que um numero possa ter a mais q o outro
        while (count_t2 != t2->end)
        {
            insert(result, (char)((int)count_t2->value + sobra));
            sobra = 0;
            count_t2 = count_t2->next;
        }
        while (count_t1 != t1->end)
        {
            insert(result, (char)((int)count_t1->value + sobra));
            sobra = 0;
            count_t1 = count_t1->next;
        }
        //adiciona a sobra da soma
        if (sobra != 0)
        {
            insert(result, (char)sobra);
        }
        insert(result, '-');
        return result;
    }
    //soma o primeiro positivo com o segundo negativo
    if (is_bigger(t1, t2))
    {
        if (t2->start == '-')
        {
            count_t2++;
        }
        
        while (count_t2->value != NULL)
        {
            parcial_result = ((int)count_t1->value - (int)count_t2->value) - sobra;
            sobra = parcial_result < 0 ? 1 : 0;
            if (sobra == 1)
            {
                parcial_result = parcial_result + 10;
            }
            insert(result, (char) parcial_result );
            count_t1 = count_t1->next;
            count_t2 = count_t2->next;
        }      
        while (count_t1 != NULL)
        {
            parcial_result = (int)count_t1->value - sobra;
            sobra = parcial_result < 0 ? 1 : 0;
            if (sobra == 1)
            {
                parcial_result = parcial_result + 10;
            }
            insert(result, (char) parcial_result );
            count_t1 = count_t1->next;
        }   
        return result;
    }

    //soma o primeiro negativo com o segundo positivo
    if (is_smaller(t1, t2))
    {
        while (count_t1->value != '-')
        {
            parcial_result = ((int)count_t2->value - (int)count_t1->value) - sobra;
            sobra = parcial_result < 0 ? 1 : 0;
            if (sobra == 1)
            {
                parcial_result = parcial_result + 10;
            }
            insert(result, (char) parcial_result );
            count_t2 = count_t2->next;
            count_t1 = count_t1->next;
        }      
        while (count_t2 != NULL)
        {
            parcial_result = (int)count_t2->value - sobra;
            sobra = parcial_result < 0 ? 1 : 0;
            if (sobra == 1)
            {
                parcial_result = parcial_result + 10;
            }
            insert(result, (char) parcial_result );
            count_t2 = count_t2->next;
        }   
        return result;
    }
    
}