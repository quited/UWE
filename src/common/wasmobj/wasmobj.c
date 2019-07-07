#include "wasmobj.h"

#include <stdlib.h>
#include "common/type.h"
#include "common/wasmobj/typeobj/typeobj.h"

struct internal_wasmobj {
  u32 version;
  typeobj type;
};

wasmobj wasmobj_init(u32 version) {
  wasmobj init = malloc(sizeof(wasmobj));
  init->version = version;
  return init;
}

wasmobj wasmobj_destroy(wasmobj me) {
  free(me);
  return NULL;
}