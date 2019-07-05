//
// Created by 31838 on 7/5/2019.
//

#include "leb128.h"

array leb128FromUint64(u64 n) {
    bool more = true;

    byte_buffer buf = byte_buffer_init();

    while (more) {
        byte b = (byte) (n & 0x7F);
        n >>= 7;
        if (n == 0)more = false;
        else {
            b = b | 0x80;
            if (byte_buffer_write_byte(buf, b))
                return NULL;
        }
    }

    return byte_buffer_read(buf, byte_buffer_size(buf));
}