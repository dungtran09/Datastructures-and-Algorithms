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
  kSuccess = 0,
  kNullParameter = -1,
  kFailedMemoryAllocation = -2,
  kArithmeticOverflow = -3,
  kInvalidIndex = -4,
  kArgumentOutOfRange = -5,
  kDependancyError = -6,
  kEmpty = -7,
  kNotFound = -8,
  KDuplicate = -9,
  kOutputPointerIsNotNull = -10,
  kSecurityError = -11,
  kSystemError = -12,
  kOverFlow = -13,
  kUnderFlow = -14,
  kInvalidArgument = -15
} Result;

typedef Result ResultCode;

char *Result_ErrorMessage(Result);
