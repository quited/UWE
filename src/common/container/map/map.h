//
// Created by 31838 on 7/7/2019.
//

#ifndef UWE_MAP_H
#define UWE_MAP_H

#include <stdlib.h>

typedef struct internal_map *map;

map map_init(size_t key_size,
             size_t value_size,
             int (*comparator)(const void *const one, const void *const two));

int map_size(map me);

int map_is_empty(map me);

int map_put(map me, void *key, void *value);

int map_get(void *value, map me, void *key);

int map_contains(map me, void *key);

int map_remove(map me, void *key);

void map_clear(map me);

map map_destroy(map me);

#endif //UWE_MAP_H
