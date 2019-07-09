#include "parser.h"

#include "common/container/array/array.h"
#include "common/container/buffer/buffer.h"
#include "common/container/byte_buffer/byte_buffer.h"
#include "common/util/debugtool.h"
#include "common/wasmobj/typeobj/funcobj/funcobj.h"
#include "common/LEB128/leb128.h"
#include "common/wasmspec/magic.h"
#include "common/wasmspec/section_id.h"
#include "common/type.h"
#include "common/wasmspec/typecode.h"
#include "common/wasmobj/typeobj/typeobj.h"
#include "common/container/vector/vector.h"
#include "common/wasmobj/wasmobj.h"

wasmobj parse(byte_buffer wasm_raw) {

  /* Check Magic Seg */
  array magic_arr = byte_buffer_read(wasm_raw, 4);
  if (array_size(magic_arr) == 4) {

    for (int i = 0; i < 4; i++) {
      byte m;
      if (array_get(&m, magic_arr, i))
        return NULL;
      if (m != magic[i]) {
        array_destroy(magic_arr);
        debug_out("Magic Seg check fail\n");
        return NULL;
      }
    }
  } else {
    array_destroy(magic_arr);
    debug_out("Magic Seg read fail\n");
    return NULL;
  }
  array_destroy(magic_arr);

  /* Parse Version Seg */
  array version_arr = byte_buffer_read(wasm_raw, 4);
  byte_buffer version_buf = byte_buffer_init();
  byte_buffer_write(version_buf, version_arr, 4);
  wasmobj wasm_obj = wasmobj_init(version_buf);
  if (!wasm_obj) {
    debug_out("Parse malloc fail (wasm_obj)\n");
    return NULL;
  }

  while (byte_buffer_read_available(wasm_raw)) {
    byte seg_type = byte_buffer_read_byte(wasm_raw);
    switch (seg_type) {
      
      /* Parse Type Seg */
      case Type: {
        u32 len = (u32)Leb128ToUint64(wasm_raw);
        debug_out("Type Section Found, length: %d bytes.\n",len);
        array type_arr = byte_buffer_read(wasm_raw,len);
        byte_buffer type_buf = byte_buffer_init();
        byte_buffer_write(type_buf,type_arr,len);
        typeobj type_obj = typeobj_init(type_buf);
        if(!type_obj) {
          debug_out("Parse Error (Type Parse Error)\n");
        } else {
          int func_count = typeobj_get_size(type_obj);
          debug_out("Found %d function types.\n",func_count);
          for(int i=0;i<func_count;i++) {
            funcobj f = typeobj_get_at(type_obj,i);

            vector params = funcobj_get_param(f);
            if(!params) {
              debug_out("Get Params Fail.\n");
            } else {
              debug_out("Params: ");
              int params_count = vector_size(params);
              for(int j=0;j<params_count;j++) {
                TypeCode type;
                vector_get_at((void*)&type,params,j);
                debug_out("%x ",type);
              }
              debug_out("\n");
            }

            vector rets = funcobj_get_ret(f); //Core dumped here because Null Pointer f->ret
            if(!rets) {
              debug_out("Get Returns Fail.\n");
            } else {
              debug_out("Returns: ");
              int rets_count = vector_size(rets);
              for(int j=0;j<rets_count;j++) {
                TypeCode type;
                vector_get_at((void*)&type,rets,j);
                debug_out("%x ",type);
              }
              debug_out("\n");
            }
          }
        }
        array_destroy(type_arr);
      }
      break;
      
      /* Parse Import Seg */
      case Import: {
        u32 len = (u32)Leb128ToUint64(wasm_raw);
        debug_out("Import Section Found, length: %d bytes.\n",len);
        array import_arr = byte_buffer_read(wasm_raw,len);
        array_destroy(import_arr);
      }
      break;

      /* Parse Import Seg */
      case Function: {
        u32 len = (u32)Leb128ToUint64(wasm_raw);
        debug_out("Function Section Found, length: %d bytes.\n",len);
        array function_arr = byte_buffer_read(wasm_raw,len);
        array_destroy(function_arr);
      }
      break;

      /* Parse Table Seg */
      case Table: {
        u32 len = (u32)Leb128ToUint64(wasm_raw);
        debug_out("Table Section Found, length: %d bytes.\n",len);
        array table_arr = byte_buffer_read(wasm_raw,len);
        array_destroy(table_arr);
      }
      break;

      /* Parse Memory Seg */
      case Memory: {
        u32 len = (u32)Leb128ToUint64(wasm_raw);
        debug_out("Memory Section Found, length: %d bytes.\n",len);
        array memory_arr = byte_buffer_read(wasm_raw,len);
        array_destroy(memory_arr);
      }
      break;
      
      /* Parse Global Seg */
      case Global: {
        u32 len = (u32)Leb128ToUint64(wasm_raw);
        debug_out("Global Section Found, length: %d bytes.\n",len);
        array global_arr = byte_buffer_read(wasm_raw,len);
        array_destroy(global_arr);
      }
      break;

      /* Parse Export Seg */
      case Export: {
        u32 len = (u32)Leb128ToUint64(wasm_raw);
        debug_out("Export Section Found, length: %d bytes.\n",len);
        array export_arr = byte_buffer_read(wasm_raw,len);
        array_destroy(export_arr);
      }
      break;

      /* Parse Start Seg */
      case Start: {
        u32 len = (u32)Leb128ToUint64(wasm_raw);
        debug_out("Start Section Found, length: %d bytes.\n",len);
        array start_arr = byte_buffer_read(wasm_raw,len);
        array_destroy(start_arr);
      }
      break;

      /* Parse Element Seg */
      case Element: {
        u32 len = (u32)Leb128ToUint64(wasm_raw);
        debug_out("Element Section Found, length: %d bytes.\n",len);
        array element_arr = byte_buffer_read(wasm_raw,len);
        array_destroy(element_arr);
      }
      break;

      /* Parse Code Seg */
      case Code: {
        u32 len = (u32)Leb128ToUint64(wasm_raw);
        debug_out("Code Section Found, length: %d bytes.\n",len);
        array code_arr = byte_buffer_read(wasm_raw,len);
        array_destroy(code_arr);
      }
      break;

      /* Parse Data Seg */
      case Data: {
        u32 len = (u32)Leb128ToUint64(wasm_raw);
        debug_out("Data Section Found, length: %d bytes.\n",len);
        array data_arr = byte_buffer_read(wasm_raw,len);
        array_destroy(data_arr);
      }
      break;

      /* Unknow Seg */
      default: {
        debug_out("Parse error (Not type), seg_type: %x.\n",seg_type);
        wasmobj_destroy(wasm_obj);
        return NULL;
      }
      break;
    }
  }

  return wasm_obj;
}