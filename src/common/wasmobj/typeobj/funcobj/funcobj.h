#ifndef COMMON_WASMOBJ_TYPEOBJ_FUNCOBJ_FUNCOBJ_H
#define COMMON_WASMOBJ_TYPEOBJ_FUNCOBJ_FUNCOBJ_H

#include "common/container/vector/vector.h"
#include "common/wasmspec/typecode.h"

typedef struct internal_funcobj * funcobj;

funcobj funcobj_init(void);

funcobj funcobj_destroy(funcobj me);

int funcobj_add_param(funcobj me, TypeCode param);

int funcobj_add_ret(funcobj me, TypeCode ret);

vector funcobj_get_param(funcobj me);

vector funcobj_get_ret(funcobj me);

#endif