#define SIZE 100
typedef char* elem;
typedef struct skip_list skip_list_t;

skip_list_t *create();
void *search(skip_list_t *sl, elem target);
void **search_occurrence(skip_list_t *sl, char target);
void free_occurrence_exit(void **exit);
int insert(skip_list_t *sl, void *cargo, elem value);
void *remove_elem(skip_list_t *sl, elem value);
void destroy(skip_list_t *sl);