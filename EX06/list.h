
typedef int elem;
typedef struct list list_t;

list_t *create();
void destroy(list_t *l);
int insert(list_t *l, elem x);
int size(list_t *l);
int print(list_t *l);
int is_in_list(list_t *l, elem x);
int rotate_left(list_t *l, int rotations);
void clear(list_t *l);