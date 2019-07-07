//
// Created by 31838 on 7/7/2019.
//

#include "pointer.h"


#include "debugtool.h"
#include <stdlib.h>

void avoid_null_pointer(void *ptr) {
  if (!ptr) {
    debug_out("invalid operation on null pointer,abort\n");
    abort();
  }
}