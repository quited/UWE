//
// Created by 31838 on 7/28/2019.
//

#ifndef SRC_COMMON_PANIC_H
#define SRC_COMMON_PANIC_H

#include "config.h"
#include "std.h"

namespace UWE {
  namespace helpers {
    using UWE::configurations::PanicMode;
    
    template<typename T=string>
    [[noreturn]]void panic(const T &msg,
                           const PanicMode mode =
                           UWE::configurations::gPanicMode,
                           const int exit_code = 1
    ) noexcept {
      std::cout << "[PANIC] " << msg << std::endl;
      switch (mode) {
        case PanicMode::kAbort:
          std::abort();
        case PanicMode::kExit:
          std::exit(exit_code);
        case PanicMode::kLoop:
          while (1);
      }
    }
  }
}

#endif //SRC_COMMON_PANIC_H
