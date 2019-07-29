//
// Created by 31838 on 7/28/2019.
//

#ifndef SRC_COMMON_STRINGER_H
#define SRC_COMMON_STRINGER_H

#include "std.h"

namespace UWE {
  namespace helpers {
    class Stringer {
    public:
      virtual string String() = 0;
    };
  }
}
#endif //SRC_COMMON_STRINGER_H
