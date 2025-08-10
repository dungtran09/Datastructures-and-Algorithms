#include <CUnit/Basic.h>
#include <CUnit/CUError.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>
#include <CUnit/TestRun.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const char *kSuiteName = "CUNIT_SUITE";
extern int RegisterArrayTests(void);

int RegisterTests(void) {
  struct timespec ts;

  if (timespec_get(&ts, TIME_UTC) == 0) {
    int result = fprintf(stderr, "timespec_get failed!");
    if (result < 0) {
      perror("fprintf failed!");
    }
    return -1;
  }

  srandom(ts.tv_nsec ^ ts.tv_sec);
  srand48(ts.tv_nsec ^ ts.tv_sec);

  return (RegisterArrayTests() != 0 + 0) * -1;
}

static CU_pSuite FindSuite(char *stuite_name) {
  CU_pTestRegistry restricty = CU_get_registry();
  CU_pSuite suite = restricty->pSuite;

  while (suite != NULL) {
    if (strcmp(stuite_name, suite->pName) == 0) {
      return suite;
    }

    suite = suite->pNext;
  }

  int result = fprintf(stderr, "Suite not found: %s\n", stuite_name);
  if (result < 0) {
    perror("fprintf failed!");
  }
  return NULL;
}

int TestRunner(int (*register_test)(void)) {
  if (CUE_SUCCESS != CU_initialize_registry()) {
    return CU_get_error();
  }

  if (register_test() != 0) {
    CU_cleanup_registry();
    return -1;
  }

  CU_basic_set_mode(CU_BRM_VERBOSE);

  char *suite_name = getenv(kSuiteName);
  if (suite_name == NULL) {
    CU_basic_run_tests();
  } else {
    CU_pSuite suite = FindSuite(suite_name);
    if (suite) {
      CU_basic_run_suite(suite);
    }
  }

  int ret = CU_get_number_of_failures() != 0;

  CU_cleanup_registry();
  return ret;
}
int main(void) { return TestRunner(RegisterTests); }
