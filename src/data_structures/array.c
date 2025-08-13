#include "../../include/array.h"
#include "../utils/result_code.c"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ResultCode Array_Create(sort_strategy comparator, size_t item_size,
                        Array **result) {
  printf("[Array_Create] comparator=%p, item_size=%zu, out=%p\n", comparator,
         item_size, (void *)result);
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

ResultCode Array_InsertAtHead(Array *self, const void *item) {
  if (self == NULL || item == NULL) {
    return kNullParameter;
  }
  if (self->n == 0) {
    ResultCode result_code = Array_CreateFirstItem(self, item);
    if (result_code != kSuccess) {
      return result_code;
    }
  } else {
    void *arr = realloc(self->array, (self->n + 1) * self->item_size);
    if (arr == NULL) {
      return kFailedMemoryAllocation;
    }
    self->array = arr;
    memmove((char *)self->array + self->item_size, self->array,
            self->item_size * self->n);
    self->n++;
    memcpy(self->array, item, self->item_size);
  }

  return kSuccess;
}

ResultCode Array_InsertAtTail(Array *self, const void *item) {
  if (self == NULL || item == NULL) {
    return kNullParameter;
  }

  if (self->item_size == 0) {
    return kInvalidArgument;
  }

  void *arr = realloc(self->array, (self->n + 1) * self->item_size);
  if (arr == NULL) {
    return kFailedMemoryAllocation;
  }
  self->array = arr;
  memcpy((char *)self->array + (self->item_size * self->n), item,
         self->item_size);
  self->n++;
  return kSuccess;
}

ResultCode Array_Enumerate(const Array *self, item_handler callback,
                           void *user_data) {
  if (self == NULL || callback == NULL) {
    return kNullParameter;
  }

  if (self->n == 0 || self->array == NULL) {
    return kSuccess;
  }

  for (size_t pos = 0; pos < self->n; pos++) {
    char *item_ptr = (char *)self->array + (self->item_size * pos);
    callback(item_ptr, user_data);
  }

  return kSuccess;
}

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
