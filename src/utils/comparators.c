#include "../../include/utils/comparators.h"

int int_comparator_fn(const void *a, const void *b) {
  return *(const int *)a - *(const int *)b;
}
