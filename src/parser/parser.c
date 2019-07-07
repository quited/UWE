#include "parser.h"

#include "common/container/array/array.h"
#include "common/container/byte_buffer/byte_buffer.h"
#include "common/wasmspec/magic.h"
#include "common/wasmspec/section_id.h"
#include "common/util/debugtool.h"
#include "common/wasmobj/wasmobj.h"

wasmobj parse(byte_buffer wasm_raw) {

  /* Check Magic Seg */
  array magic_arr = byte_buffer_read(wasm_raw,4);
  if(array_size(magic_arr)==4) {
    for(int i;i<4;i++)
      if(((byte*)array_get_data(magic_arr))[i] != magic[i]) {
        array_destroy(magic_arr);
        debug_out("Magic Seg check fail\n");
        return NULL;
      }
  } else {
    array_destroy(magic_arr);
    debug_out("Magic Seg read fail\n");
    return NULL;
  }
  array_destroy(magic_arr);

  /* Parse Version Seg */
  array version_arr = byte_buffer_read(wasm_raw,4);
  byte_buffer version_buf = byte_buffer_init();
  byte_buffer_write(version_buf,version_arr,4);
  wasmobj wasm_obj = wasmobj_init(version_buf);
  if(!wasm_obj){
    debug_out("Parse malloc fail (wasm_obj)\n");
    return NULL;
  }

  /* Parse Type Seg */
  if(byte_buffer_read_byte(wasm_raw)==Type) debug_out("Type Section Found\n");

  return wasm_obj;
}