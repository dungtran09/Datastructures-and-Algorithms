
#include <stdbool.h>
#include <unistd.h>

static bool intercept_malloc = false;
static size_t intercept_count = 0;

void *__real_malloc(size_t size);
void *__wrap_malloc(size_t size) {
  if (intercept_malloc) {
    ++intercept_count;
    return NULL;
  }

  return __real_malloc(size);
}

void *__real_calloc(size_t nmemb, size_t size);
void *__wrap_calloc(size_t nmemb, size_t size) {
  if (intercept_malloc) {
    ++intercept_count;
    return NULL;
  }
  return __real_calloc(nmemb, size);
}

void *__real_realloc(void *ptr, size_t size);
void *__wrap_realloc(void *ptr, size_t size) {
  if (intercept_malloc) {
    ++intercept_count;
    return NULL;
  }
  return __real_realloc(ptr, size);
}

void InterceptMalloc() { intercept_malloc = true; }

void ResetMalloc() {
  intercept_count = 0;
  intercept_malloc = false;
}

size_t MallocInterceptCount() { return intercept_count; }
