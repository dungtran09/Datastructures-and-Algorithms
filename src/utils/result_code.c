#include "../../include/utils/result_code.h"

char *Result_ErrorMessage(Result result) {
  switch (result) {
  /* ===== Success ===== */
  case kSuccess:
    return "Success.";

  /* ===== Parameter Errors ===== */
  case kNullParameter:
    return "A required parameter is NULL.";
  case kInvalidArgument:
    return "Invalid argument.";
  case kArgumentOutOfRange:
    return "The specified value is outside the valid range.";
  case kInvalidIndex:
    return "Invalid index.";
  case kOutputPointerIsNotNull:
    return "Output pointer must be NULL before calling this function.";
  case kArithmeticOverflow:
    return "Arithmetic overflow.";
  case kArithmeticUnderflow:
    return "Arithmetic underflow.";

  /* ===== State Errors ===== */
  case kEmpty:
    return "The array is empty.";
  case kNotFound:
    return "Requested item not found.";
  case kDuplicate:
    return "The item already exists (duplicate).";
  case kCorruptedArray:
    return "Array structure is corrupted.";

  /* ===== Runtime Errors ===== */
  case kFailedMemoryAllocation:
    return "Failed to allocate memory.";
  case kOverflow:
    return "Data size exceeds maximum capacity.";
  case kUnderflow:
    return "Data size below minimum capacity.";
  case kDependancyError:
    return "Error returned from a dependency.";

  /* ===== System Errors ===== */
  case kSecurityError:
    return "Security-related error.";
  case kSystemError:
    return "Underlying operating system error.";

  /* ===== Default ===== */
  default:
    return "Unknown result code.";
  }
}
