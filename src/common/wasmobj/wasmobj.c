#include "wasmobj.h"

#include <stdlib.h>
#include "common/container/byte_buffer/byte_buffer.h"
#include "common/util/pointer.h"
#include "common/type.h"
#include "common/wasmobj/typeobj/typeobj.h"

struct internal_wasmobj {
  byte_buffer version;
  typeobj type;
};

wasmobj wasmobj_init(byte_buffer version) {
  if(byte_buffer_read_available(version)!=4) return NULL;
  wasmobj init = malloc(sizeof(wasmobj));
  if(!init) return NULL;
  init->version = version;
  return init;
}

wasmobj wasmobj_destroy(wasmobj me) {
  avoid_null_pointer(me);
  if(me->version) byte_buffer_destroy(me->version);
  me->version = NULL;
  free(me);
  return NULL;
}