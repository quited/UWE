//
// Created by 31838 on 7/5/2019.
//

#ifndef UWE_BYTE_BUFFER_H
#define UWE_BYTE_BUFFER_H

#include <container/array/array.h>
#include <type.h>

typedef struct internal_byte_buffer *byte_buffer;

byte_buffer byte_buffer_init();

array byte_buffer_read(byte_buffer me, int n_bytes);

int byte_buffer_write(byte_buffer me, array arr, int n_bytes);

byte byte_buffer_read_byte(byte_buffer me);

int byte_buffer_write_byte(byte_buffer me, byte b);

byte_buffer byte_buffer_destroy(byte_buffer me);

int byte_buffer_size(byte_buffer me);

int byte_buffer_read_available(byte_buffer me);

#endif //UWE_BYTE_BUFFER_H
