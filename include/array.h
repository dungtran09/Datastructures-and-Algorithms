#pragma once

#include <stddef.h>

#include "./utils/comparators.h"
#include "./utils/result_code.h"

typedef struct {
  sort_strategy comparator;
  size_t n;
  size_t item_size;
  void *array;
} Array;

ResultCode Array_Create(sort_strategy, size_t item_size, Array **);
ResultCode Array_InsertAtHead(Array *, const void *);
ResultCode Array_InsertAtTail(Array *, const void *);
ResultCode Array_Search(const Array *, const void *, void **);
ResultCode Array_Max(const Array *, void **);
ResultCode Array_Predecessor(const Array *, const void *, void **);
ResultCode Array_Rank(const Array *, const void *, size_t *);
void Array_Destroy(Array *);
