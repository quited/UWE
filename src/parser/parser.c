#include "parser.h"

#include "common/container/byte_buffer/byte_buffer.h"
#include "common/wasmobj/wasmobj.h"

wasmobj parse(byte_buffer wasm_raw){
  wasmobj new = wasmobj_init(1);
  return new;
}