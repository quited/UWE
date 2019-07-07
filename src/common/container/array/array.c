//
// Created by 31838 on 7/2/2019.
//

#include "array.h"

#include <string.h>
#include <errno.h>
#include <common/util/pointer.h>

struct internal_array {
  size_t bytes_per_item;
  int item_count;
  void *data;
};

array array_init(const int element_count, const size_t data_size) {
  struct internal_array *init;
  if (element_count < 0 || data_size == 0) {
    return NULL;
  }
  init = malloc(sizeof(struct internal_array));
  if (!init) {
    return NULL;
  }
  init->bytes_per_item = data_size;
  init->item_count = element_count;
  if (init->item_count == 0) {
    init->data = NULL;
    return init;
  }
  init->data = calloc((size_t) element_count, data_size);
  if (!init->data) {
    free(init);
    return NULL;
  }
  return init;
}

int array_size(array me) {
  avoid_null_pointer(me);
  return me->item_count;
}

void array_copy_to_array(void *const arr, array me) {
  avoid_null_pointer(arr);
  if (me->item_count == 0) {
    return;
  }
  memcpy(arr, me->data, me->item_count * me->bytes_per_item);
}

void *array_get_data(array me) {
  avoid_null_pointer(me);
  return me->data;
}

static int array_is_illegal_input(array me, const int index) {
  avoid_null_pointer(me);
  return index < 0 || index >= me->item_count;
}

int array_set(array me, const int index, void *const data) {
  avoid_null_pointer(me);
  if (array_is_illegal_input(me, index)) {
    return -EINVAL;
  }
  memcpy((char *) me->data + index * me->bytes_per_item, data,
         me->bytes_per_item);
  return 0;
}

int array_get(void *const data, array me, const int index) {
  avoid_null_pointer(me);
  avoid_null_pointer(data);
  if (array_is_illegal_input(me, index)) {
    return -EINVAL;
  }
  memcpy(data, (char *) me->data + index * me->bytes_per_item,
         me->bytes_per_item);
  return 0;
}

array array_destroy(array me) {
  avoid_null_pointer(me);
  if (me->data)free(me->data);
  free(me);
  return NULL;
}

array array_slice(array me, int start, int end) {
  avoid_null_pointer(me);
  if (start < 0 || start >= me->item_count || start > end)return NULL;
  if (end < 0 || end > me->item_count)return NULL;
  array init = array_init(end - start, me->bytes_per_item);
  if (init == NULL)return NULL;
  if (end - start == 0)return init;
  if (!memcpy(init->data, me->data + start * me->bytes_per_item, me->bytes_per_item * (end - start)))return NULL;
  return init;
}

array array_append(array me, array b) {
  avoid_null_pointer(me);
  if ((!me) && b)return array_copy(b);
  else if (me && (!b))return array_copy(me);
  else if (!me)return NULL;

  if (me->bytes_per_item != b->bytes_per_item || me->bytes_per_item == 0)return NULL;
  array init = array_init(me->item_count + b->item_count, me->bytes_per_item);
  if (init == NULL)return NULL;
  if (me->item_count)
    if (!memcpy(init->data, me->data, me->item_count * me->bytes_per_item)) {
      array_destroy(init);
      return NULL;
    }
  if (b->item_count)
    if (!memcpy(init->data + me->bytes_per_item * me->item_count, b->data, b->bytes_per_item * b->item_count)) {
      array_destroy(init);
      return NULL;
    }
  return init;
}

array array_prepend(array me, array b) {
  avoid_null_pointer(me);
  return array_append(b, me);
}

array array_copy(array me) {
  avoid_null_pointer(me);
  array init = array_init(me->item_count, me->bytes_per_item);
  if (!init)return NULL;
  if (!memcpy(init->data, me->data, me->bytes_per_item * me->item_count)) {
    array_destroy(init);
    return NULL;
  }
  return init;
}

array array_from_array(void *arr, int element_count, size_t data_size) {
  if (!arr)return NULL;
  array init = array_init(element_count, data_size);
  if (!init)return NULL;

  if (!memcpy(array_get_data(init), arr, data_size * element_count)) {
    array_destroy(init);
    return NULL;
  }
  return init;
}

size_t array_bytes_per_item(array me) {
  avoid_null_pointer(me);
  return me->bytes_per_item;
}

void array_for_each_byte(array me, byte (*func)(byte b)) {
  avoid_null_pointer(me);
  avoid_null_pointer(func);

  byte *ptr = (byte *) me->data;
  for (u64 i = 0; i < me->item_count * me->bytes_per_item / sizeof(byte); i++)
    ptr[i] = func(ptr[i]);
}

array array_revert_items(array me) {
  array res = array_init(me->item_count, me->bytes_per_item);
  if (!res)return NULL;

  for (int i = 0, j = me->item_count - 1; i < me->item_count && j >= 0; i++, j--) {
    void *data = malloc(me->bytes_per_item);
    if (!data)return NULL;
    if (array_get(data, me, i))return NULL;
    if (array_set(res, j, data))return NULL;
  }
  return res;
}
