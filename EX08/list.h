#define SIZE 100
typedef int elem;
typedef struct list list_t;

list_t *create();
void destroy(list_t *l);
int insert(list_t *l, elem x);
int size(list_t *l);
int print(list_t *l);
int is_in_list(list_t *l, elem x);
elem query_by_pos(list_t *l, int pos);
int query_by_index(list_t *l, int *exit, int index);
int update_by_index(list_t *l, elem new_value, int index);
int lremove_by_elem(list_t *l, elem cutter);
int remove_first(list_t *l);