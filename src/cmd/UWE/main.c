#include <stdio.h>
#include <stdlib.h>

#include "common/container/byte_buffer/byte_buffer.h"
#include "parser/parser.h"
#include "common/type.h"
#include "common/util/debugtool.h"
#include "common/wasmobj/wasmobj.h"

int main(int argc, char *argv[]) {

  if (argc != 2) {
    debug_out("USAGE: UWE <.wasm filename>\n");
    return -1;
  }
  byte_buffer byte_buffer_ins = byte_buffer_init();
  if (!byte_buffer_ins) {
    debug_out("Init parser fail (byte_buffer_ins)\n");
    return -1;
  }
  FILE *file = fopen(argv[1], "rb");
  if (!file) {
    debug_out("Open file fail\n");
    return -1;
  }
  
  {
    array arr = array_init(100, sizeof(byte));
    do {
        int read = fread(array_get_data(arr), sizeof(byte), array_size(arr), file);
      if (!read) break;
      if (!arr) {
        debug_out("Init parser fail (arr)\n");
        return -1;
      }
      if (byte_buffer_write(byte_buffer_ins, arr, read)) {
        debug_out("File read fail (byte_buffer_ins)\n");
        return -1;
      }
    } while (true);
    array_destroy(arr);
  }

    debug_out("read %d \n", byte_buffer_read_available(byte_buffer_ins));

  wasmobj wasm_obj = parse(byte_buffer_ins);
  byte_buffer_destroy(byte_buffer_ins);
  if(!wasm_obj) {
    printf("Parse Error\n");
  } else {
    wasmobj_destroy(wasm_obj);
    printf("Parse Success\n");
  }
  return 0;
}