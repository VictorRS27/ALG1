#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

int main(int argc, char const *argv[])
{
    int eof_reader;
    char key, prev;
    stack_t *text;
    text = create();

    do
    {
        eof_reader = getchar();
        key = eof_reader;
        if (key == ']' || key == ')' || key == '}')
        {
            pop(text, &prev);
            if (key == ']' && prev != '[')
            {
                printf("DESBALANCEADO");
                exit(0);
            }
            if (key == '}' && prev != '{')
            {
                printf("DESBALANCEADO");
                exit(0);
            }
            if (key == ')' && prev != '(')
            {
                printf("DESBALANCEADO");
                exit(0);
            }
        }
        if (key == '[' || key == '(' || key == '{' || key == '"')
        {
            push(text, &key);
        }
        
    } while (eof_reader != EOF);
    
    if (!isEmpty(text))
    {
        printf("DESBALANCEADO");
    }
    else
    {
        printf("BALANCEADO");
    }
    return 0;
}
