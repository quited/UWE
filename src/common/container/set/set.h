//
// Created by 31838 on 7/2/2019.
//

#ifndef DATA_SET_H
#define DATA_SET_H


#include <stdlib.h>

typedef struct internal_set *set;

set set_init(size_t key_size,
             int (*comparator)(const void *const one, const void *const two));

int set_size(set me);

int set_is_empty(set me);

int set_put(set me, void *key);

int set_contains(set me, void *key);

int set_remove(set me, void *key);

void set_clear(set me);

set set_destroy(set me);

#endif //DATA_SET_H
