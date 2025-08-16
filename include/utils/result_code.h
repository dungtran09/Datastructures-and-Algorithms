#pragma once

#include <stdio.h>

#define PRINT_ERROR(source, result)                                            \
  {                                                                            \
    int(fprint_result) = fprintf(stderr, "%s: %s, %s, %s, %d\n", source,       \
                                 Result_ErrorMessage(result), __FILE__,        \
                                 __FUNCTION__, __LINE__);                      \
    if ((fprint_result) < 0)                                                   \
      perror("fprint failed!");                                                \
  }

typedef enum Result {
  /* ===== Success ===== */
  kSuccess = 0,

  /* ===== Parameter Errors (-1xx) ===== */
  kNullParameter = -100,
  kInvalidArgument = -101,
  kOutputPointerIsNotNull = -102,
  kArgumentOutOfRange = -103,
  kArithmeticOverflow = -104,
  kArithmeticUnderflow = -105,
  kInvalidIndex = -106,

  /* ===== State Errors (-2xx) ===== */
  kEmpty = -200,
  kFull = -201,
  kNotFound = -202,
  kDuplicate = -203,
  kCorruptedArray = -204,

  /* ===== Runtime Errors (-3xx) ===== */
  kFailedMemoryAllocation = -300,
  kOverflow = -301,
  kUnderflow = -302,
  kDependancyError = -303,

  /* ===== System Errors (-4xx) ===== */
  kSecurityError = -400,
  kSystemError = -401
} Result;

typedef Result ResultCode;
