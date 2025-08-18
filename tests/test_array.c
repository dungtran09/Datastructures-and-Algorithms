#include "../include/array.h"
#include "ctype.h"
#include "utils/test_helpers.h"
#include "utils/test_malloc_wraper.h"
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int *data;
  size_t size;
} TestArray;

#define SUT(vals, n, code_block)                                               \
  {                                                                            \
    Array *sut = NULL;                                                         \
    ResultCode result_code =                                                   \
        Array_Create(int_comparator_fn, sizeof(int), &sut);                    \
    CU_ASSERT_EQUAL(result_code, kSuccess)                                     \
    for (size_t i = 0; i < (n), i++) {                                         \
      result_code = Array_InsertAtTail(sut, &(vals)[i]);                       \
      CU_ASSERT_EQUAL(result_code, kSuccess);                                  \
    }                                                                          \
    {code_block};                                                              \
    Array_Destroy(sut);                                                        \
  }
/***** Array_create *****/
static void Array_Create_bad_malloc() {
  FAILED_MALLOC_TEST({
    Array *array = NULL;
    ResultCode result_code =
        Array_Create(int_comparator_fn, sizeof(int), &array);
    CU_ASSERT_EQUAL(result_code, kFailedMemoryAllocation);
    CU_ASSERT_PTR_NULL(array);
  });
}

static void Array_Create_inits_values() {
  Array *arr = NULL;
  ResultCode result_code = Array_Create(int_comparator_fn, sizeof(int), &arr);
  CU_ASSERT_EQUAL(result_code, kSuccess);

  CU_ASSERT_PTR_EQUAL(int_comparator_fn, arr->comparator);
  CU_ASSERT_PTR_EQUAL(sizeof(int), arr->item_size);
  CU_ASSERT_EQUAL(0, arr->n);
  CU_ASSERT_PTR_NULL(arr->array);

  Array_Destroy(arr);
}

/***** Array_InsertAtHead *****/
static void Array_InsertAtHead_null_parameter() {
  const int n = 5;
  const int items[] = {1, 2, 3, 4, 5, 6};
  const int expected[] = {6, 5, 4, 3, 2, 1};

  Array *arr = NULL;
  ResultCode result_code = Array_Create(int_comparator_fn, sizeof(int), &arr);
  CU_ASSERT_EQUAL(result_code, kSuccess);

  for (size_t i = 0; i < n; i++) {
    result_code = Array_InsertAtHead(arr, &items[i]);
    CU_ASSERT_EQUAL(result_code, kSuccess);
  }

  CU_ASSERT_EQUAL(n, arr->n);
  CU_ASSERT_EQUAL(0, memcmp(expected, arr->array, sizeof(int) * n));
  Array_Destroy(arr);
}

static void Array_InsertAtHead_bad_malloc() {
  int first = 1;
  Array *arr = NULL;
  ResultCode result_code = Array_Create(int_comparator_fn, sizeof(int), &arr);
  CU_ASSERT_EQUAL(result_code, kSuccess);

  result_code = Array_InsertAtHead(arr, &first);
  CU_ASSERT_EQUAL(result_code, kFailedMemoryAllocation);
  CU_ASSERT_EQUAL(0, arr->n);

  Array_Destroy(arr);
}

static void Array_InsertAtHead_first_item() {}

static void Array_InsertAtHead_standard() {}

static void Array_InsertAtHead_bad_malloc_on_realloc() {}

/****__*****/

static void Array_Destroy_null_parameter() { Array_Destroy(NULL); }

/****__*****/
static TestArray *_readArrayFile(const char *path) {
  printf("Opening file: %s\n", path);
  FILE *fp = fopen(path, "r");
  if (!fp) {
    perror("Failed to open file!");
    return NULL;
  }
  TestArray *tarr = malloc(sizeof(TestArray));
  if (!tarr) {
    fclose(fp);
    return NULL;
  }
  if (fscanf(fp, "%zu", &tarr->size) != 1) {
    fclose(fp);
    free(tarr);
    return NULL;
  }

  tarr->data = malloc(sizeof(int) * tarr->size);
  if (!tarr->data) {
    printf("[ERROR] Memory allocation failed for data array\n");
    fclose(fp);
    free(tarr);
    return NULL;
  }
  printf("Array size: %zu\n", tarr->size);

  for (size_t i = 0; i < tarr->size; i++) {
    if (fscanf(fp, "%d", &tarr->data[i]) != 1) {
      printf("Failed to read element %zu\n", i);
      fclose(fp);
      free(tarr->data);
      free(tarr);
      return NULL;
    }
    printf("Read element %zu = %d\n", i, tarr->data[i]);
  }

  fclose(fp);
  return tarr;
}

static void _sumCallback(const void *x, void *user_data) {
  int *sum = (int *)user_data;

  *sum += *(int *)x;
}
static int _sumArray(Array *arr, int initial_val) {
  int sum = initial_val;
  printf("[DEBUG] _sumArray: start sum = %d\n", sum);
  Array_Enumerate(arr, _sumCallback, &sum);
  printf("[DEBUG] _sumArray: final sum = %d\n", sum);
  return sum;
}

static void _testArrayFile(const char *path, int expected_sum) {
  printf("[_testArrayFile] Called with path='%s', expected_sum=%d\n", path,
         expected_sum);
  TestArray *tarr = _readArrayFile(path);
  printf("[_testArrayFile] _readArrayFile returned: %p\n", (void *)tarr);

  CU_ASSERT_PTR_NOT_NULL_FATAL(tarr);
  printf("[_testArrayFile] tarr->size=%zu\n", tarr->size);
  Array *arr = NULL;

  ResultCode result_code = Array_Create(int_comparator_fn, sizeof(int), &arr);
  printf("[_testArrayFile] Array_Create result=%d, arr=%p\n", result_code,
         (void *)arr);

  CU_ASSERT_EQUAL(result_code, kSuccess);

  for (size_t i = 0; i < tarr->size; i++) {
    printf("[_testArrayFile] Inserting element[%zu] = %d\n", i, tarr->data[i]);
    result_code = Array_InsertAtTail(arr, &tarr->data[i]);
    printf("[_testArrayFile] Array_InsertAtTail result=%d\n", result_code);
    CU_ASSERT_EQUAL(result_code, kSuccess);
  }

  int actual_val = _sumArray(arr, 0);
  printf("[_testArrayFile] _sumArray returned actual_val=%d\n", actual_val);
  CU_ASSERT_EQUAL(actual_val, expected_sum);
  printf("[_testArrayFile] Destroying array...\n");
  Array_Destroy(arr);
  printf("[_testArrayFile] Freeing tarr->data and tarr...\n");

  free(tarr->data);
  free(tarr);
  printf("[_testArrayFile] Completed successfully.\n");
}

static int _parserExpectedFromFilename(const char *filename) {
  printf("[_parserExpectedFromFilename] Input filename='%s'\n", filename);
  const char *p = filename;
  while (*p && !isdigit((unsigned char)*p)) {
    p++;
  }
  if (!*p) {
    fprintf(stderr, "[ERROR] No number found in filename: %s\n", filename);
    return -9999;
  }

  int result = atoi(p);

  printf("[_parserExpectedFromFilename] Extracted number=%d\n", result);
  return result;
}

void Array_SolveFiles(void) {
  printf("[Array_SolveFiles] Opening directory 'test_data'\n");
  DIR *dir = opendir("test_data");
  CU_ASSERT_PTR_NOT_NULL_FATAL(dir);

  struct dirent *entry;

  char path[512];
  while ((entry = readdir(dir)) != NULL) {
    printf("[Array_SolveFiles] Found entry: name='%s', type=%d\n",
           entry->d_name, entry->d_type);
    if (entry->d_type == DT_REG) {
      snprintf(path, sizeof(path), "test_data/%s", entry->d_name);
      printf("[Array_SolveFiles] Processing file path='%s'\n", path);
      int expected_sum = _parserExpectedFromFilename(entry->d_name);
      _testArrayFile(path, expected_sum);
    }
  }

  closedir(dir);
  printf("[Array_SolveFiles] Directory closed\n");
}

static void Array_SolveFiles_test(void) { Array_SolveFiles(); }

int RegisterArrayTests() {

  CU_TestInfo Create_Destroy_tests[] = {
      CU_TEST_INFO(Array_Create_bad_malloc),
      CU_TEST_INFO(Array_Create_inits_values),
      CU_TEST_INFO(Array_Destroy_null_parameter), CU_TEST_INFO_NULL};
  CU_TestInfo InsertAtHead_tests[] = {CU_TEST_INFO(Array_InsertAtHead_standard),
                                      CU_TEST_INFO(Array_Create_bad_malloc),
                                      CU_TEST_INFO_NULL};
  ;
  CU_TestInfo FileData_tests[] = {CU_TEST_INFO(Array_SolveFiles_test),
                                  CU_TEST_INFO_NULL};
  CU_SuiteInfo suites[] = {
      {.pName = "Array_Create_Destroy",
       .pInitFunc = noop,
       .pTests = Create_Destroy_tests},
      {.pName = "Array_FileData", .pInitFunc = noop, .pTests = FileData_tests},
      {.pName = "Array_InsertAtHead",
       .pInitFunc = noop,
       .pTests = InsertAtHead_tests},
      CU_SUITE_INFO_NULL};

  return CU_register_suites(suites);
}
