#include <stdio.h>

enum boolean {
	true = 1, false = 0
};

typedef enum boolean bool;

int main(void) {
	bool b;

	b = true;

	if(b)
		printf("verdadeiro\n");

	printf("%lu\n", sizeof(bool));
	return 0;
}
