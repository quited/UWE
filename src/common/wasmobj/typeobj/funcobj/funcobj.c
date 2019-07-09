#include "funcobj.h"

#include <stdlib.h>
#include "common/container/vector/vector.h"
#include "common/util/pointer.h"

struct internal_funcobj {
  vector param;
  vector ret;
};

funcobj funcobj_init(void) {
  funcobj init = malloc(sizeof(funcobj));
  if (!init) return NULL;
  init->param = vector_init(sizeof(TypeCode));
  init->ret = vector_init(sizeof(TypeCode));
  avoid_null_pointer(init->param);
  avoid_null_pointer(init->ret);
  return init;
}

funcobj funcobj_destroy(funcobj me) {
  avoid_null_pointer(me);
  if (me->param) vector_destroy(me->param);
  if (me->ret) vector_destroy(me->ret);
  me->param = NULL;
  me->ret = NULL;
  free(me);
  return NULL;
}

int funcobj_add_param(funcobj me, TypeCode param) {
  avoid_null_pointer(me->param);
  return vector_add_last(me->param, &param);
}

int funcobj_add_ret(funcobj me, TypeCode ret) {
  avoid_null_pointer(me->param);
  return vector_add_last(me->ret, &ret);
}

vector funcobj_get_param(funcobj me) {
  avoid_null_pointer(me->param);
  return me->param;
}

vector funcobj_get_ret(funcobj me) {
  avoid_null_pointer(me);
  avoid_null_pointer(me->ret);
  return me->ret;
}