#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "fila.h"

/*
 * Victor Rodrigues da Silva  No 12566140
 * 
 * 
 * Uso TAD fila identico ao do professor para confeccao de fila de hospital respeitando prioridades
*/

//define valores importantes a cada paciente
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

//libera os nomes dos pacientes
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
        //Foi a forma que encontrei para ler tudo corretamente, nao sei pq mas
        //somente limpar o buffer com getchar e fflush nao funciona
        //Como ler nao eh o foco do exercicio, ignorem esse rudeza
        do
        {
            comand = read_line();
        } while ((comand[0] == '\n' || comand[0] == '\0'));

        //se o comando SAI for digitado, retira um paciente da respectiva fila dada a prioridade e exibe os dados
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
        //se nao SAI significa que ENTRA, logo, ele le os dados do paciente e inclui na devida lista
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

    //livra as variaveis e destroi as listas

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
