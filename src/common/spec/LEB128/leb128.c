//
// Created by 31838 on 7/5/2019.
//

#include "leb128.h"

array leb128FromUint64(u64 n) {
    byte_buffer buf = byte_buffer_init();

    for (;;) {
        byte b = (byte) (n & 0x7F);
        n >>= 7;
        if (n == 0)
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

u64 leb128ToUint64(array arr) {
    u64 res = 0;
    for (int i = 0, shift = 0;; i++, shift += 7) {
        byte b = ((byte *) array_get_data(arr))[i];
        res |= ((u64) 0x7F & b) << shift;
        if (!(b & 0x80))break;
    }
    return res;
}