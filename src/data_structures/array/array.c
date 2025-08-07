#include "array.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

static ResultCode Array_CreateFirstItem(Array *self, const void *item) {

  return 0;
}

ResultCode Array_Create(size_t item_size, Array **result) { return 0; }

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
