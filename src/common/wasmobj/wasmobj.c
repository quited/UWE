#include "wasmobj.h"

#include <stdlib.h>
#include "common/container/array/array.h"
#include "common/type.h"
#include "common/wasmobj/typeobj/typeobj.h"

struct internal_wasmobj {
  array version;
  typeobj type;
};

wasmobj wasmobj_init(array version) {
  if(array_size(version)<4) return NULL;
  wasmobj init = malloc(sizeof(wasmobj));
  init->version = version;
  return init;
}

wasmobj wasmobj_destroy(wasmobj me) {
  array_destroy(me->version);
  me->version = NULL;
  free(me);
  return NULL;
}