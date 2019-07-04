//
// Created by 31838 on 7/2/2019.
//

#ifndef DATA_VECTOR_H
#define DATA_VECTOR_H

#include <stdlib.h>

typedef struct internal_vector *vector;

vector vector_init(size_t data_size);

int vector_size(vector me);

int vector_capacity(vector me);

int vector_is_empty(vector me);

int vector_reserve(vector me, int size);

int vector_trim(vector me);

void vector_copy_to_array(void *arr, vector me);

void *vector_get_data(vector me);

int vector_add_first(vector me, void *data);

int vector_add_at(vector me, int index, void *data);

int vector_add_last(vector me, void *data);

int vector_remove_first(vector me);

int vector_remove_at(vector me, int index);

int vector_remove_last(vector me);

int vector_set_first(vector me, void *data);

int vector_set_at(vector me, int index, void *data);

int vector_set_last(vector me, void *data);

int vector_get_first(void *data, vector me);

int vector_get_at(void *data, vector me, int index);

int vector_get_last(void *data, vector me);

int vector_clear(vector me);

vector vector_destroy(vector me);

#endif //DATA_VECTOR_H
