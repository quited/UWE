//
// Created by 31838 on 7/28/2019.
//

#ifndef SRC_COMMON_CONFIG_H
#define SRC_COMMON_CONFIG_H

namespace UWE {
  namespace configurations {
    enum class PanicMode {
      kAbort,
      kExit,
      kLoop
    };
    const auto gPanicMode = PanicMode::kAbort;
  }
}

#endif //SRC_COMMON_CONFIG_H
