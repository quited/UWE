//
// Created by 31838 on 7/5/2019.
//

#include "leb128.h"

array Leb128FromUint64(u64 n) {
  byte_buffer buf = byte_buffer_init();

  for (;;) {
    byte b = (byte) (n & 0x7F);
    n >>= 7;
    if (!n)
      break;
    else {
      b = b | 0x80;
      if (byte_buffer_write_byte(buf, b))
        return NULL;
    }
  }

  array res = byte_buffer_read(buf, byte_buffer_read_available(buf));
  byte_buffer_destroy(buf);
  return res;
}

array Leb128FromInt64(i64 n) {
  byte_buffer buf = byte_buffer_init();
  for (;;) {
    byte c = n & 0x7F;
    byte s = n & 0x40;
    n >>= 7;
    if ((n != -1 || s == 0) && (n != 0 || s != 0))
      c |= 0x80;
    byte_buffer_write_byte(buf, c);
    if (!(c & 0x80))
      break;
  }
  array res = byte_buffer_read(buf, byte_buffer_read_available(buf));
  byte_buffer_destroy(buf);
  return res;
}


u64 Leb128ToUint64(byte_buffer buf) {
  u64 res = 0;
  for (int i = 0, shift = 0;; i++, shift += 7) {
    if (!byte_buffer_read_available(buf))
      return 0;
    byte b = byte_buffer_read_byte(buf);
    res |= ((u64) 0x7F & b) << shift;
    if (!(b & 0x80))
      break;
  }
  return res;
}

i64 Leb128ToInt64(byte_buffer buf) {
  i64 res = 0;
  for (byte i = 0; i < 10; i++) {
    if (!byte_buffer_read_available(buf))
      return 0;
    byte b = byte_buffer_read_byte(buf);
    res |= (i64) (b & 0x7F) << (7 * i);
    if (!(b & 0x80)) {
      if (b & 0x40) {
        res |= ~0 << (7 * (i + 1));
        return res;
      }
    }
  }
  return 0;
}