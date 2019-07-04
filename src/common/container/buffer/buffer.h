//
// Created by 31838 on 7/3/2019.
//

#ifndef AGEDWASM_BUFFER_H
#define AGEDWASM_BUFFER_H

#include <stddef.h>
#include "../array/array.h"

typedef struct internal_buffer *buffer;

buffer buffer_init(size_t data_size);

int buffer_size(buffer me);

int buffer_read(array *data, buffer me, int n_element);

int buffer_write(buffer me, array data, int n_element);

int buffer_read_available(buffer me);

buffer buffer_destroy(buffer me);

buffer buffer_from_array(array arr);

#endif //AGEDWASM_BUFFER_H
