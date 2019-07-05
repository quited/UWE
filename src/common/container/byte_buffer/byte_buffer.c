//
// Created by 31838 on 7/5/2019.
//

#include <container/buffer/buffer.h>
#include <type.h>

#include "byte_buffer.h"

struct internal_byte_buffer {
    buffer buf;
};

byte_buffer byte_buffer_init() {
    struct internal_byte_buffer *init = malloc(sizeof(struct internal_byte_buffer));
    if (!init)return NULL;
    init->buf = buffer_init(sizeof(byte));
    if (!init->buf) {
        free(init);
        return NULL;
    }
    return (byte_buffer) init;
}

array byte_buffer_read(byte_buffer me, int n_bytes) {
    array res;
    if (buffer_read(&res, me->buf, n_bytes))return NULL;
    return res;
}

int byte_buffer_write(byte_buffer me, array arr, int n_bytes) {
    return buffer_write(me->buf, arr, n_bytes);
}

byte byte_buffer_read_byte(byte_buffer me) {
    byte *data;
    if (buffer_read_one((void **) &data, me->buf))return 0;
    return *data;
}

int byte_buffer_write_byte(byte_buffer me, byte b) {
    return buffer_write_one(me->buf, &b);
}

byte_buffer byte_buffer_destroy(byte_buffer me) {
    buffer_destroy(me->buf);
    free(me);
    return NULL;
}

int byte_buffer_size(byte_buffer me) {
    return buffer_size(me->buf);
}

int byte_buffer_read_available(byte_buffer me) {
    return buffer_read_available(me->buf);
}
