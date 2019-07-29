//
// Created by 31838 on 7/28/2019.
//

#ifndef SRC_COMMON_STD_H
#define SRC_COMMON_STD_H

#include <string>
#include <tuple>
#include <valarray>
#include <vector>
#include <memory>
#include <iterator>

namespace UWE {
  using std::tuple;
  using std::make_tuple;
  using std::get;
  
  using std::string;
  using std::valarray;
  using std::vector;
  using std::array;
  
  using std::unique_ptr;
  using std::shared_ptr;
  
  template<typename T, typename... Args>
  std::unique_ptr<T> make_unique(Args &&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
  }
  
  template<typename T, typename... Args>
  std::unique_ptr<T> make_unique_noexcept(Args &&...args) noexcept {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
  }
  
  using std::move;
  using std::begin;
  using std::end;
  using std::copy;
}

#endif //SRC_COMMON_STD_H
