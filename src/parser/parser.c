#include "parser.h"

#include "common/container/array/array.h"
#include "common/container/byte_buffer/byte_buffer.h"
#include "common/spec/magic.h"
#include "common/wasmobj/wasmobj.h"

wasmobj parse(byte_buffer wasm_raw) {

  /* Check Magic Seg */
  array magic_arr = byte_buffer_read(wasm_raw,4);
  if(array_size(magic_arr)==4) {
    for(int i;i<4;i++)
      if(((byte*)array_get_data(magic_arr))[i] != magic[i]) {
        array_destroy(magic_arr);
        return NULL;
      }
  } else {
    array_destroy(magic_arr);
    return NULL;
  }
  array_destroy(magic_arr);

  /* Parse Version Seg */
  array version_arr = byte_buffer_read(wasm_raw,4);
  byte_buffer version_buf = byte_buffer_init();
  byte_buffer_write(version_buf,version_arr,4);
  array_destroy(version_arr);

  wasmobj wasm_obj = wasmobj_init(version_buf);
  if(!wasm_obj){
    byte_buffer_destroy(version_buf);
    return NULL;
  }

  return wasm_obj;
}