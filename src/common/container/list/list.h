//
// Created by 31838 on 7/2/2019.
//

#ifndef DATA_LIST_H
#define DATA_LIST_H

#include <stdlib.h>

typedef struct internal_list *list;

list list_init(size_t data_size);

int list_size(list me);

int list_is_empty(list me);

void list_copy_to_array(void *arr, list me);

int list_add_first(list me, void *data);

int list_add_at(list me, int index, void *data);

int list_add_last(list me, void *data);

int list_remove_first(list me);

int list_remove_at(list me, int index);

int list_remove_last(list me);

int list_set_first(list me, void *data);

int list_set_at(list me, int index, void *data);

int list_set_last(list me, void *data);

int list_get_first(void *data, list me);

int list_get_at(void *data, list me, int index);

int list_get_last(void *data, list me);

void list_clear(list me);

list list_destroy(list me);

#endif //DATA_LIST_H
