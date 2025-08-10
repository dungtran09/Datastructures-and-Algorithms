#include "../../include/array.h"
#include "../utils/result_code.c"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static ResultCode Array_CreateFirstItem(Array *self, const void *item) {
  if (self == NULL || item == NULL)
    return kNullParameter;

  self->array = malloc(self->item_size);

  if (self->array == NULL)
    return kFailedMemoryAllocation;

  memcpy(self->array, item, self->item_size);
  self->n++;

  return kSuccess;
}

ResultCode Array_Create(sort_strategy comparator, size_t item_size,
                        Array **result) {
  if (comparator == NULL || result == NULL)
    return kNullParameter;

  if (*result != NULL) {
    return kOutputPointerIsNotNull;
  }

  Array *array = calloc(sizeof(Array), 1);

  if (array == NULL) {
    return kFailedMemoryAllocation;
  }

  array->item_size = item_size;
  array->comparator = comparator;

  *result = array;
  return kSuccess;
}

ResultCode Array_InsertAtHead(Array *self, const void *item) { return 0; }

ResultCode Array_InsertAtTail(Array *self, const void *item) { return 0; }

ResultCode Array_Search(const Array *self, const void *item, void **result) {
  return 0;
}

ResultCode Array_Max(const Array *self, void **result) { return 0; }

ResultCode Array_Predecessor(const Array *self, const void *item,
                             void **result) {
  return 0;
}

ResultCode Array_Rank(const Array *self, const void *item, size_t *result) {
  return 0;
}

void Array_Destroy(Array *self) {
  if (self == NULL)
    return;

  free(self->array);
  free(self);
}
