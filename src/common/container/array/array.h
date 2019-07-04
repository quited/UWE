//
// Created by 31838 on 7/2/2019.
//

#ifndef DATA_ARRAY_H
#define DATA_ARRAY_H

#include <stdlib.h>

typedef struct internal_array *array;

array array_init(int element_count, size_t data_size);

int array_size(array me);

void array_copy_to_array(void *arr, array me);

void *array_get_data(array me);

int array_set(array me, int index, void *data);

int array_get(void *data, array me, int index);

array array_destroy(array me);

array array_slice(array me, int start, int end);

array array_append(array me, array b);

array array_prepend(array me, array b);

array array_copy(array me);

array array_from_array(void *arr, int element_count, size_t data_size);

size_t array_bytes_per_item(array me);

#endif //DATA_ARRAY_H
