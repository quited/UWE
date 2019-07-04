//
// Created by 31838 on 7/2/2019.
//

#ifndef DATA_DEQUE_H
#define DATA_DEQUE_H

#include <stdlib.h>

typedef struct internal_deque *deque;

deque deque_init(size_t data_size);

int deque_size(deque me);

int deque_is_empty(deque me);

int deque_trim(deque me);

void deque_copy_to_array(void *arr, deque me);

int deque_push_front(deque me, void *data);

int deque_push_back(deque me, void *data);

int deque_pop_front(void *data, deque me);

int deque_pop_back(void *data, deque me);

int deque_set_first(deque me, void *data);

int deque_set_at(deque me, int index, void *data);

int deque_set_last(deque me, void *data);

int deque_get_first(void *data, deque me);

int deque_get_at(void *data, deque me, int index);

int deque_get_last(void *data, deque me);

int deque_clear(deque me);

deque deque_destroy(deque me);

#endif //DATA_DEQUE_H
