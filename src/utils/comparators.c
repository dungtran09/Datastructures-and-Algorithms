#include "comparators.h"

int PIntComparator(const void *a, const void *b) {
  return *(const int *)a - *(const int *)b;
}
