#define Stack_Size 400

typedef struct stack stack_t;
typedef char elem;

stack_t *create();
void destroy(stack_t *s);
int isFull(stack_t *s);
int isEmpty(stack_t *s);
int push(stack_t *s, elem *x);
int pop(stack_t *s, elem *x);
int top_value(stack_t *s, elem *x);
