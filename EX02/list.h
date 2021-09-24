
typedef long int elem;
typedef struct list list_t;

list_t *create();
void destroy(list_t *l);
int insert(list_t *l, elem x);
int size(list_t *l);
int print(list_t *l);
int is_in_list(list_t *l, elem x);
elem query_index(list_t *l, int index);
elem lremove_by_index(list_t *l, int index);
int lremove_by_elem(list_t *l, elem cutter);