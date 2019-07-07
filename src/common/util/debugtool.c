#include "debugtool.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#include <common/type.h>

int debug_out(const char *format, ...) {
  va_list args;
  va_start(args, format);
  int res = vprintf(format, args);
  va_end(args);
  return res;
}
