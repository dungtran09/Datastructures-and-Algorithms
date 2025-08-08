typedef int (*sort_strategy)(const void *x, const void *y);
typedef void (*freer)(void *x);
int PIntComparator(const void *a, const void *b);
