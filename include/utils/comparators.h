typedef int (*sort_strategy)(const void *x, const void *y);
typedef void (*freer)(void *x);
int int_comparator_fn(const void *a, const void *b);
