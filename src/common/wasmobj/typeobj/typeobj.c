#include "typeobj.h"

#include "common/container/array/array.h"
#include "common/container/byte_buffer/byte_buffer.h"
#include "common/wasmobj/typeobj/funcobj/funcobj.h"
#include "common/LEB128/leb128.h"
#include "common/util/pointer.h"
#include "common/wasmspec/typecode.h"
#include "common/container/vector/vector.h"
#include <stdlib.h>

struct internal_typeobj {
  vector type_list;
};

typeobj typeobj_init(byte_buffer seg_raw) {
  typeobj init = malloc(sizeof(typeobj));
  if(!init) return NULL;
  init->type_list = vector_init(sizeof(funcobj));
  if(!init->type_list) {
    free(init);
    return NULL;
  }

  u32 len = (u32) Leb128ToUint64(seg_raw);
  u32 func_count = (u32)Leb128ToUint64(seg_raw);
  for(int i=0; i<func_count; i++) {
    if(byte_buffer_read_byte(seg_raw) != 0x60) {
      typeobj_destroy(init);
      return NULL;
    }
    funcobj func_obj = funcobj_init();
    avoid_null_pointer(func_obj);

    u32 param_count = (u32)Leb128ToUint64(seg_raw);
    for(int i=0; i<param_count; i++) {
      byte param_t = byte_buffer_read_byte(seg_raw);
      switch (param_t) {
        case I32:
          funcobj_add_param(func_obj, I32);    
          break;
        case I64:
          funcobj_add_param(func_obj, I64);
          break;
        case F32:
          funcobj_add_param(func_obj, F32);
          break;
        case F64:
          funcobj_add_param(func_obj, F64);
          break;
        default: {
            funcobj_destroy(func_obj);
            typeobj_destroy(init);
            return NULL;
          }
          break;
      }
    }

    u32 ret_count = (u32)Leb128ToUint64(seg_raw);
    if(ret_count!=0)
      for(int i=0;i<ret_count;i++) {
        byte ret_t = byte_buffer_read_byte(seg_raw);
        switch (ret_t) {
          case I32:
            funcobj_add_ret(func_obj,I32);
            break;
          case I64:
            funcobj_add_ret(func_obj,I64);
            break;
          case F32:
            funcobj_add_ret(func_obj,F32);
            break;
          case F64:
            funcobj_add_ret(func_obj,F64);
            break;
          default: {
            funcobj_destroy(func_obj);
            typeobj_destroy(init);
            return NULL;
          }
          break;
        }
      }
    
    vector_add_last(init->type_list,func_obj);
  }

  return init;
}

typeobj typeobj_destroy(typeobj me) {
  avoid_null_pointer(me);
  if(me->type_list) {
    funcobj it;
    for(int i=0;i<vector_size(me->type_list);i++) {
      vector_get_at(it,me->type_list,i);
      funcobj_destroy(it);
    }
    vector_destroy(me->type_list);
  }
  me->type_list = NULL;
  free(me);
  return NULL;
}

funcobj typeobj_get_at(typeobj me, int index) {
  avoid_null_pointer(me);
  funcobj get;
  vector_get_at(get, me->type_list, index);
  return get;
}

int typeobj_get_size(typeobj me) {
  avoid_null_pointer(me);
  return vector_size(me->type_list);
}
