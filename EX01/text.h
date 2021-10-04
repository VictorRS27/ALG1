typedef struct text text_t;

text_t *create();
void read_text(text_t *t);
int size(text_t *t);
char *remove_usual(text_t *t, int *repetitions);
void destroy(text_t *t);
