#ifndef COMMON_WASMSPEC_TYPECODE_H
#define COMMON_WASMSPEC_TYPECODE_H

typedef enum internal_typecode {
  I32 = 0x7f,
  I64 = 0x7e,
  F32 = 0x7d,
  F64 = 0x7c
} TypeCode;

#endif