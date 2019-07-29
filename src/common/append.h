//
// Created by 31838 on 7/28/2019.
//

#ifndef SRC_COMMON_APPEND_H
#define SRC_COMMON_APPEND_H

#include "types.h"
#include "std.h"

namespace UWE {
  namespace helpers {
    enum class AppendMode : uint8_t {
      kCopy,
      kMove,
      kFullyCopy,
      kFullyMove
    };

    // This function appends vec2 to vec1
    template<typename T>
    vector<T> Append(vector<T> &vec1, vector<T> &vec2,
      // Mode indicates behaviour of the Append function .
      // Note that after move operation,the data that have been moved will be invalid,
      // which means that the data cannot be access from its original vector,
      // and the vector can be safely reset or deleted.
                     const AppendMode mode = AppendMode::kFullyMove) {
      using std::make_move_iterator;
      switch (mode) {
        case AppendMode::kCopy:
          // Data of vec2 will be copied to vec1,then vec1 will be returned.
          // Meanwhile, vec2 remains unchanged.
        {
          vec1.insert(vec1.end(), vec2.begin(), vec2.end());
          return vec1;
        }
        case AppendMode::kMove:
          // Data inside vec2 will be moved to vec1 instead of copy.
          // After the operation,data inside vec2 will remain unchanged.
          // Note that this flag is only benefit to complex data type.
        {
          vec1.insert(vec1.end(),
                      make_move_iterator(vec2.begin()),
                      make_move_iterator(vec2.end()));
          return vec2;
        }
        case AppendMode::kFullyCopy:
          // A new vector will be constructed to contains data of vec1 and vec2.
          // Note that data inside vec1 and vec2 will be fully copied and remains unchanged.
          // This method performs exactly as same as kMove when vectors contain simple data type,
          // For example builtin type int,uint8_t,etc.
        {
          auto vec_res = vector<T>();
          vec_res.reserve(vec1.size() + vec2.size());
          vec_res.insert(vec_res.end(), vec1.begin(), vec1.end());
          vec_res.insert(vec_res.end(), vec2.begin(), vec2.end());
          return vec_res;
        }


        case AppendMode::kFullyMove:
          // A new vector will be constructed to contains data inside vec1 and vec2.
          // After the operation,data inside vec1 and vec2 will remain unchanged.
          // Unlike kFullyCopy, move operation will be performed instead of copy.
          // Note that this flag is only benefit to complex data type.
        {
          auto vec_res = vector<T>();
          vec_res.reserve(vec1.size() + vec2.size());
          vec_res.insert(vec_res.end(),
                         make_move_iterator(vec1.begin()),
                         make_move_iterator(vec1.end()));
          vec_res.insert(vec_res.end(),
                         make_move_iterator(vec2.begin()),
                         make_move_iterator(vec2.end()));
          return vec_res;
        }
      }
    }

//    template<typename T>
//    vector<T> Append(vector<T> &vec1, valarray<T> &arr,
//                     const AppendMode mode = AppendMode::kFullyMove) {
//      using std::make_move_iterator;
//      switch (mode) {
//        case AppendMode::kCopy: {
//          vec1.insert(vec1.end(), arr.begin(), arr.end());
//          return vec1;
//        }
//        case AppendMode::kMove: {
//          vec1.insert(vec1.end(),
//                      make_move_iterator(arr.begin()),
//                      make_move_iterator(arr.end()));
//          return arr;
//        }
//        case AppendMode::kFullyCopy: {
//          auto vec_res = vector<T>();
//          vec_res.reserve(vec1.size() + arr.size());
//          vec_res.insert(vec_res.end(), vec1.begin(), vec1.end());
//          vec_res.insert(vec_res.end(), arr.begin(), arr.end());
//          return vec_res;
//        }
//
//
//        case AppendMode::kFullyMove: {
//          auto vec_res = vector<T>();
//          vec_res.reserve(vec1.size() + arr.size());
//          vec_res.insert(vec_res.end(),
//                         make_move_iterator(vec1.begin()),
//                         make_move_iterator(vec1.end()));
//          vec_res.insert(vec_res.end(),
//                         make_move_iterator(arr.begin()),
//                         make_move_iterator(arr.end()));
//          return vec_res;
//        }
//      }
//    }
//
//    template<typename T, size_t arr_size>
//    vector<T> Append(vector<T> &vec1, array<T, arr_size> &arr,
//                     const AppendMode mode = AppendMode::kFullyMove) {
//      using std::make_move_iterator;
//      switch (mode) {
//        case AppendMode::kCopy: {
//          vec1.insert(vec1.end(), arr.begin(), arr.end());
//          return vec1;
//        }
//        case AppendMode::kMove: {
//          vec1.insert(vec1.end(),
//                      make_move_iterator(arr.begin()),
//                      make_move_iterator(arr.end()));
//          return arr;
//        }
//        case AppendMode::kFullyCopy: {
//          auto vec_res = vector<T>();
//          vec_res.reserve(vec1.size() + arr.size());
//          vec_res.insert(vec_res.end(), vec1.begin(), vec1.end());
//          vec_res.insert(vec_res.end(), arr.begin(), arr.end());
//          return vec_res;
//        }
//
//
//        case AppendMode::kFullyMove: {
//          auto vec_res = vector<T>();
//          vec_res.reserve(vec1.size() + arr.size());
//          vec_res.insert(vec_res.end(),
//                         make_move_iterator(vec1.begin()),
//                         make_move_iterator(vec1.end()));
//          vec_res.insert(vec_res.end(),
//                         make_move_iterator(arr.begin()),
//                         make_move_iterator(arr.end()));
//          return vec_res;
//        }
//      }
//    }
  }
}
#endif //SRC_COMMON_APPEND_H
