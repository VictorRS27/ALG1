#define TamFila 100

typedef struct fila fila_t;

fila_t *criar(int tamElem);
int isEmpty(fila_t *f);
int isFull(fila_t *f);
int inserir(fila_t *f, void *x);
int remover(fila_t *f, void *x);
void destruir(fila_t *f);