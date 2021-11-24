typedef char elem;
typedef struct list list_t;

list_t *create();
void destroy(list_t *l);
int insert(list_t *l, elem x);
int size(list_t *l);
int print(list_t *l);
int is_in_list(list_t *l, elem x);
int is_bigger(list_t *t1, list_t *t2);
int is_smaller(list_t *t1, list_t *t2);
int is_equal(list_t *t1, list_t *t2);
list_t *sum(list_t *t1, list_t *t2, list_t *result);