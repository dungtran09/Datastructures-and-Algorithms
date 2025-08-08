#include "../../include/utils/result_code.h"

char *Result_ErrorMessage(Result result) {
  switch (result) {
  case kSuccess:
    return "Success";
  case kNullParameter:
    return "A required parameter is NULL!";
  case kFailedMemoryAllocation:
    return "Failed to allocate memory!";
  case kArithmeticOverflow:
    return "Arithmetic Overflow!";
  case kInvalidIndex:
    return "Invqlid index!";
  case kArgumentOutOfRange:
    return "The specified valiue is outside the range of valid values";
  case kDependancyError:
    return "Error code from a dependency!";
  case kEmpty:
    return "List is empty!";
  case kNotFound:
    return "The requested object was not found!";
  case KDuplicate:
    return "The parameter is a duplicate of an exiting item!";
  case kOutputPointerIsNotNull:
    return "An output parameter pointer is not null. These are intended to be "
           "populated by the function";
  case kSecurityError:
    return "There was a security related error!";
  case kSystemError:
    return "Underlying OS error!";
  case kOverFlow:
    return "Overflow - Request exceeds maximun size!";
  case KUnderFlow:
    return "Underflow - Request exceeds minimum size!";
  default:
    return "Unknow result code!";
  }
}
