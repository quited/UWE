//
// Created by 31838 on 7/2/2019.
//

#include "vector.h"

#include <string.h>
#include <errno.h>

static const int START_SPACE = 8;
static const double RESIZE_RATIO = 1.5;

struct internal_vector {
    size_t bytes_per_item;
    int item_count;
    int item_capacity;
    void *data;
};

vector vector_init(const size_t data_size) {
    struct internal_vector *init;
    if (data_size == 0) {
        return NULL;
    }
    init = malloc(sizeof(struct internal_vector));
    if (!init) {
        return NULL;
    }
    init->bytes_per_item = data_size;
    init->item_count = 0;
    init->item_capacity = START_SPACE;
    init->data = malloc(init->item_capacity * init->bytes_per_item);
    if (!init->data) {
        free(init);
        return NULL;
    }
    return init;
}

int vector_size(vector me) {
    return me->item_count;
}

int vector_capacity(vector me) {
    return me->item_capacity;
}

int vector_is_empty(vector me) {
    return vector_size(me) == 0;
}

static int vector_set_space(vector me, const int size) {
    void *const temp = realloc(me->data, size * me->bytes_per_item);
    if (!temp) {
        return -ENOMEM;
    }
    me->data = temp;
    me->item_capacity = size;
    return 0;
}

int vector_reserve(vector me, int size) {
    if (me->item_capacity >= size) {
        return 0;
    }
    return vector_set_space(me, size);
}

int vector_trim(vector me) {
    return vector_set_space(me, me->item_count);
}

void vector_copy_to_array(void *const arr, vector me) {
    memcpy(arr, me->data, me->item_count * me->bytes_per_item);
}

void *vector_get_data(vector me) {
    return me->data;
}

int vector_add_first(vector me, void *const data) {
    return vector_add_at(me, 0, data);
}

int vector_add_at(vector me, const int index, void *const data) {
    if (index < 0 || index > me->item_count) {
        return -EINVAL;
    }
    if (me->item_count + 1 >= me->item_capacity) {
        const int new_space = (int) (me->item_capacity * RESIZE_RATIO);
        void *const temp = realloc(me->data, new_space * me->bytes_per_item);
        if (!temp) {
            return -ENOMEM;
        }
        me->data = temp;
        me->item_capacity = new_space;
    }
    if (index != me->item_count) {
        memmove((char *) me->data + (index + 1) * me->bytes_per_item,
                (char *) me->data + index * me->bytes_per_item,
                (me->item_count - index) * me->bytes_per_item);
    }
    memcpy((char *) me->data + index * me->bytes_per_item, data,
           me->bytes_per_item);
    me->item_count++;
    return 0;
}

int vector_add_last(vector me, void *const data) {
    return vector_add_at(me, me->item_count, data);
}

static int vector_is_illegal_input(vector me, const int index) {
    return index < 0 || index >= me->item_count;
}

int vector_remove_first(vector me) {
    return vector_remove_at(me, 0);
}

int vector_remove_at(vector me, const int index) {
    if (vector_is_illegal_input(me, index)) {
        return -EINVAL;
    }
    me->item_count--;
    memmove((char *) me->data + index * me->bytes_per_item,
            (char *) me->data + (index + 1) * me->bytes_per_item,
            (me->item_count - index) * me->bytes_per_item);
    return 0;
}

int vector_remove_last(vector me) {
    if (me->item_count == 0) {
        return -EINVAL;
    }
    me->item_count--;
    return 0;
}

int vector_set_first(vector me, void *const data) {
    return vector_set_at(me, 0, data);
}

int vector_set_at(vector me, const int index, void *const data) {
    if (vector_is_illegal_input(me, index)) {
        return -EINVAL;
    }
    memcpy((char *) me->data + index * me->bytes_per_item, data,
           me->bytes_per_item);
    return 0;
}

int vector_set_last(vector me, void *const data) {
    return vector_set_at(me, me->item_count - 1, data);
}

int vector_get_first(void *const data, vector me) {
    return vector_get_at(data, me, 0);
}

int vector_get_at(void *const data, vector me, const int index) {
    if (vector_is_illegal_input(me, index)) {
        return -EINVAL;
    }
    memcpy(data, (char *) me->data + index * me->bytes_per_item,
           me->bytes_per_item);
    return 0;
}

int vector_get_last(void *const data, vector me) {
    return vector_get_at(data, me, me->item_count - 1);
}

int vector_clear(vector me) {
    me->item_count = 0;
    return vector_set_space(me, START_SPACE);
}

vector vector_destroy(vector me) {
    free(me->data);
    me->data = NULL;
    free(me);
    return NULL;
}
