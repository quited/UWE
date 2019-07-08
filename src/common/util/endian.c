//
// Created by 31838 on 7/7/2019.
//

#include <common/type.h>
#include <common/container/stack/stack.h>
#include "endian.h"

int host_endian() {
  int p = 1;
  byte *ptr = (byte *) &p;
  return ptr[0] == (byte) 1;
}

byte revert_endian(byte b) {
  stack s = stack_init(sizeof(byte));
  for (byte i = 0, p = (byte) (0b10000000); i < sizeof(byte) * 8; i++, p >>= 1) {
    byte r = (byte) (bool) b & p;
    if (stack_push(s, &r))return 0;
  }
  byte res = 0;
  for (byte i = 0, p = (byte) (0b10000000); i < sizeof(byte) * 8; i++, p >>= 1) {
    byte r = 0;
    if (stack_pop(&r, s))return 0;
    if (r)res |= p;
  }
  return res;
}

byte revert_endian_for_each_func(byte b) {
  return revert_endian(b);
}

array revert_array(array arr) {
  array res = array_revert_items(arr);
  array_for_each_byte(res, revert_endian_for_each_func);
  return res;
}