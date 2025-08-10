#include "../include/array.h"
#include "utils/test_helpers.h"
#include "utils/test_malloc_wraper.h"
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>

#define SUT(vals, n, code_block)                                               \
  {                                                                            \
    Array *sut = NULL;                                                         \
    ResultCode result_code = Array_Create(PIntComparator, sizeof(int), &sut);  \
    CU_ASSERT_EQUAL(result_code, kSuccess)                                     \
    for (size_t i = 0; i < (n), i++) {                                         \
      result_code = Array_InsertAtTail(sut, &(vals)[i]);                       \
      CU_ASSERT_EQUAL(result_code, kSuccess);                                  \
    }                                                                          \
    {code_block};                                                              \
    Array_Destroy(sut);                                                        \
  }

static void Array_Create_bad_malloc() {
  FAILED_MALLOC_TEST({
    Array *array = NULL;
    ResultCode result_code = Array_Create(PIntComparator, sizeof(int), &array);
    CU_ASSERT_EQUAL(result_code, kFailedMemoryAllocation);
    CU_ASSERT_PTR_NULL(array);
  });
}

static void Array_Destroy_null_parameter() { Array_Destroy(NULL); }

int RegisterArrayTests() {
  CU_TestInfo Create_tests[] = {CU_TEST_INFO(Array_Create_bad_malloc),
                                CU_TEST_INFO_NULL};

  CU_TestInfo Destroy_tests[] = {CU_TEST_INFO(Array_Destroy_null_parameter),
                                 CU_TEST_INFO_NULL};

  CU_SuiteInfo suites[] = {
      {.pName = "Array_Create", .pInitFunc = noop, .pTests = Create_tests},
      CU_TEST_INFO_NULL};

  return CU_register_suites(suites);
}
