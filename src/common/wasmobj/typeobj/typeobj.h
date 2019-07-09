#ifndef COMMON_WASMOBJ_TYPEOBJ_TYPEOBJ_H
#define COMMON_WASMOBJ_TYPEOBJ_TYPEOBJ_H

#include "common/container/array/array.h"
#include "common/container/byte_buffer/byte_buffer.h"
#include "common/wasmobj/typeobj/funcobj/funcobj.h"

typedef struct internal_typeobj *typeobj;

typeobj typeobj_init(byte_buffer seg_raw);

typeobj typeobj_destroy(typeobj me);

funcobj typeobj_get_at(typeobj me, int index);

int typeobj_get_size(typeobj me);

#endif