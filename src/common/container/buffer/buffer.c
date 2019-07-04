//
// Created by 31838 on 7/3/2019.
//

#include "buffer.h"

#include <errno.h>
#include <string.h>

#define initial_buffer_size 20

struct internal_buffer {
    size_t bytes_per_item;
    int read_pos, write_pos;
    array backend;
};

buffer buffer_init(size_t data_size) {
    struct internal_buffer *init;
    if (data_size == 0)return NULL;
    init = (struct internal_buffer *) malloc(sizeof(struct internal_buffer));
    if (!init)return NULL;
    init->backend = array_init(initial_buffer_size, data_size);
    init->read_pos = init->write_pos = 0;
    init->bytes_per_item = data_size;
    return (buffer) init;
}

int buffer_size(buffer me) {
    return array_size(me->backend);
}

int buffer_grow(buffer me, int grow) {
    if (grow <= 0)return 0;
    array empty_b = array_init(grow, me->bytes_per_item);
    array b = array_append(me->backend, empty_b);
    if (empty_b && b) {
        array_destroy(empty_b);
        array_destroy(me->backend);
        me->backend = b;
        return 0;
    } else return -ENOMEM;
}

int buffer_shrink(buffer me) {
    array s = array_slice(me->backend, me->read_pos, array_size(me->backend));
    if (!s)return -ENOMEM;
    array_destroy(me->backend);
    me->backend = s;
    me->write_pos -= me->read_pos;
    me->read_pos = 0;
    return 0;
}

int buffer_read(array *data, buffer me, int n_element) {
    n_element = n_element > buffer_read_available(me) ? buffer_read_available(me) : n_element;
    if (n_element == 0) {
        *data = NULL;
        return 0;
    }
    array res = array_slice(me->backend, me->read_pos, me->read_pos + n_element);
    if (!res) {
        *data = NULL;
        return -ENOMEM;
    }
    *data = res;
    me->read_pos += n_element;
    if (me->read_pos > buffer_size(me) * 0.5)
        return buffer_shrink(me);
    return 0;
}

int buffer_write(buffer me, array data, int n_element) {
    if (n_element + me->write_pos > array_size(me->backend))
        if (buffer_grow(me, n_element + me->write_pos + 1))
            return -ENOMEM;
    if (!memcpy(array_get_data(me->backend) + me->write_pos * me->bytes_per_item, array_get_data(data),
                n_element * me->bytes_per_item))
        return -ENOMEM;
    me->write_pos += n_element;
    return 0;
}

int buffer_read_available(buffer me) {
    return me->write_pos - me->read_pos;
}

buffer buffer_destroy(buffer me) {
    array_destroy(me->backend);
    free(me);
    return NULL;
}

buffer buffer_from_array(array arr) {
    struct internal_buffer *init;
    init = (struct internal_buffer *) malloc(sizeof(struct internal_buffer));
    if (!init)return NULL;
    init->backend = array_copy(arr);
    init->bytes_per_item = array_bytes_per_item(arr);
    init->write_pos = init->read_pos = 0;
    return init;
}

