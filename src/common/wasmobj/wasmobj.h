#ifndef COMMON_WASMOBJ_WASMOBJ_H
#define COMMON_WASMOBJ_WASMOBJ_H

#include "common/container/byte_buffer/byte_buffer.h"
#include "common/type.h"

typedef struct internal_wasmobj *wasmobj;

wasmobj wasmobj_init(byte_buffer buf);

wasmobj wasmobj_destroy(wasmobj me);

#endif