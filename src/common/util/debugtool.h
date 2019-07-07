#ifndef COMMON_UTIL_DEBUGTOOL_H
#define COMMON_UTIL_DEBUGTOOL_H

int debug_out(const char *format, ...);

void avoid_null_pointer(void *ptr);

#endif