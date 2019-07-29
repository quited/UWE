//
// Created by 31838 on 7/28/2019.
//

#ifndef SRC_COMMON_ERRORS_H
#define SRC_COMMON_ERRORS_H

#include "std.h"
#include "stringer.h"
#include "panic.h"

namespace UWE {
  namespace errors {
    class Error;
    
    using ErrorPtr=unique_ptr<Error>;
    
    class Error : public UWE::helpers::Stringer {
    public:
      virtual bool operator==(const ErrorPtr &) = 0;
    };
    
    template<typename T>
    tuple<T *, bool> BasicTypeCheck(const ErrorPtr &to_comp) {
      auto res = dynamic_cast<T *>(to_comp.get());
      return make_tuple(res, res != nullptr);
    }
    
    namespace {
      class Nil : public Error {
      private:
        uint8_t:0;
      public:
        bool operator==(const ErrorPtr &to_comp) override {
          return get<1>(BasicTypeCheck<Nil>(to_comp));
        }
        
        string String() override {
          return "";
        }
      };
    }
    
    auto gNil = make_unique_noexcept<Nil>();
  }
}
#endif //SRC_COMMON_ERRORS_H
