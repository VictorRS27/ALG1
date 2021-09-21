#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOTAL 100

typedef struct no
{
    char value;
    int next;
} no_t;

int main(int argc, char const *argv[])
{
    int i, eofReader;
    no_t text [100] = {0};

    do
    {
        eofReader = getchar();
        text[i].value = eofReader;
    }while ();
    
    return 0;
}
