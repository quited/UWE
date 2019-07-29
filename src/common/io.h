//
// Created by 31838 on 7/28/2019.
//

#ifndef SRC_COMMON_IO_H
#define SRC_COMMON_IO_H

#include "std.h"
#include "errors.h"
#include "types.h"

namespace UWE {
  namespace helpers {
    namespace io {
      using UWE::errors::ErrorPtr;
      using Result=tuple<size_t, ErrorPtr>;
      using Buffer=vector<byte> &;
      
      namespace errors {
        using UWE::errors::Error;
        
        enum class ErrorCode : uint8_t {
          kUnknown,
          kEOF,
          kUnexpectedEOF,
          kNoMore,
          kOther
        };
        namespace {
          class _Error : public Error {
          public:
            const ErrorCode code_;
          public:
            bool operator==(const ErrorPtr &ptr) override {
              auto res = UWE::errors::BasicTypeCheck<_Error>(ptr);
              if (!get<1>(res))return false;
              return get<0>(res)->code_ == code_;
            }
            
            string String() override {
              switch (code_) {
                case ErrorCode::kUnknown:
                  return "unknown error";
                case ErrorCode::kEOF:
                  return "EOF";
                case ErrorCode::kUnexpectedEOF:
                  return "Unexpected EOF";
                case ErrorCode::kOther:
                  return "other error";
              }
            }
            
            explicit _Error(ErrorCode code) : code_(code) {}
          };
          
          ErrorPtr MakeErrorPtrNoexcept(ErrorCode code) noexcept {
            return ErrorPtr(new _Error(code));
          }
        }
        ErrorPtr gUnknown = MakeErrorPtrNoexcept(ErrorCode::kUnknown);
        ErrorPtr gEOF = MakeErrorPtrNoexcept(ErrorCode::kEOF);
        ErrorPtr gUnexpectedEOF = MakeErrorPtrNoexcept(ErrorCode::kUnexpectedEOF);
        ErrorPtr gOther = MakeErrorPtrNoexcept(ErrorCode::kOther);
        ErrorPtr gNoMore = MakeErrorPtrNoexcept(ErrorCode::kNoMore);
      }
      
      class Writer {
      public:
        virtual Result Write(Buffer) = 0;
      };
      
      class Reader {
      public:
        virtual Result Read(Buffer) = 0;
      };
      
      class Closer {
      public:
        virtual const ErrorPtr Close() = 0;
      };
      
      class ReadWriter : public Reader, public Writer {
      };
      
      class ReadWriteCloser : public Reader, public Writer, public Closer {
      };
      
      class ReadCloser : public Reader, public Closer {
      };
      
      class WriteCloser : public Writer, public Closer {
      };
      
      class ReaderFrom {
      public:
        virtual Result ReadFrom(Reader &) = 0;
      };
      
      class WriterTo {
      public:
        virtual Result WriteTo(Writer &) = 0;
      };
    }
  }
}
#endif //SRC_COMMON_IO_H
