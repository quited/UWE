#include "wasmobj.h"

#include <stdlib.h>
#include <common/util/endian.h>
#include "common/container/byte_buffer/byte_buffer.h"
#include "common/util/pointer.h"
#include "common/type.h"
#include "common/wasmobj/typeobj/typeobj.h"

struct internal_wasmobj {
  byte version;
  typeobj type;
};

wasmobj wasmobj_init(byte_buffer buf) {
  if (byte_buffer_read_available(buf) < 4)return NULL;
  wasmobj init = malloc(sizeof(wasmobj));
  if(!init) return NULL;
  array version = byte_buffer_read(buf, 4);
  if (!version)return NULL;

  byte v = ((byte *) array_get_data(version))[0];
  //if endian of host is big endian,revert v so that we can compare it correctly
  if (!host_endian())v = revert_endian(v);
  //currently wasm version 1 is the oly valid version
  if (v != 1)return NULL;
  init->version = v;

  return init;
}

wasmobj wasmobj_destroy(wasmobj me) {
  avoid_null_pointer(me);
  free(me);
  return NULL;
}