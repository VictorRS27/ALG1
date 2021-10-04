#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

/*
 * Victor Rodrigues da Silva  No 12566140
 * 
 * 
 * le caracteres ( { [ " ] } ) e diz se as aberturas e fechamentos estao balanceados
*/

int main(int argc, char const *argv[])
{
    int eof_reader, flag;
    char key, prev;
    stack_t *text;
    text = create();

    //repete leituras de linha texto
    do
    {
        flag = 0;
        //le cada caractere e verifica infracao de balanceamento
        do
        {
            eof_reader = getchar();
            //lida com \r\n
            if (eof_reader == '\r')
            {
                eof_reader = getchar();
            }
            key = eof_reader;

            //lida com " sendo iguais pra abrir e fechar / adiciona caracteres a pilha
            top_value(text, &prev);
            if (key == '"' && prev == '"')
            {
                pop(text, &prev);
            }
            else if (key == '[' || key == '(' || key == '{' || key == '"')
            {
                push(text, &key);
            }

            //verifica se o caractere de fechamento segue as regras e retira da pilha
            if (key == ']' || key == ')' || key == '}')
            {
                pop(text, &prev);
                if (prev == 0 && flag == 0)
                {
                    printf("NÃO BALANCEADO\n");
                    flag = 1;
                    eof_reader = '\n';
                }
                if (key == ']' && prev != '[' && flag == 0)
                {
                    printf("NÃO BALANCEADO\n");
                    flag = 1;
                    eof_reader = '\n';
                }
                if (key == '}' && prev != '{' && flag == 0)
                {
                    printf("NÃO BALANCEADO\n");
                    flag = 1;
                    eof_reader = '\n';
                }
                if (key == ')' && prev != '(' && flag == 0)
                {
                    printf("NÃO BALANCEADO\n");
                    flag = 1;
                    eof_reader = '\n';
                }
            }
            
            
        } while (key != '\n' && eof_reader != EOF);
        
        //lida com o caso de aberturas sem fechamento
        if (flag != 1)
        {
            if (!isEmpty(text))
            {
                printf("NÃO BALANCEADO\n");
            }
            else
            {
                printf("BALANCEADO\n");
            }
        }
        
        //esvazia a pilha 
        while (!isEmpty(text))
        {
            pop(text, &prev);
        }
        
    } while (eof_reader != EOF);
        destroy(text);

    return 0;
}
