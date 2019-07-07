#ifndef COMMON_WASMOBJ_WASMOBJ_H
#define COMMON_WASMOBJ_WASMOBJ_H

#include "common/type.h"

typedef struct internal_wasmobj *wasmobj;

wasmobj wasmobj_init(u32 version);

wasmobj wasmobj_destroy(wasmobj me);

#endif