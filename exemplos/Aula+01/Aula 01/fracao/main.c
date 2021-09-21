#include <stdio.h>
#include "fracao.h"

int main(void) {

	fracao_t *f = criar(1, 2);
	fracao_t *f2 = criar(3, 4);

	fracao_t *f3 = somar(f, f2);

	imprimir(f3);

	destruir(f);
	destruir(f2);
	destruir(f3);
	return 0;
}
