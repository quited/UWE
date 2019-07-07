//
// Created by 31838 on 7/7/2019.
//

#ifndef UWE_CHECK_ME_H
#define UWE_CHECK_ME_H

#include <stdlib.h>

void check_me(void *me) {
  if (!me) {
    abort();
  }
}

#endif //UWE_CHECK_ME_H
