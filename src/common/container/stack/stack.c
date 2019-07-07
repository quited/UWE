//
// Created by 31838 on 7/2/2019.
//

#include <common/util/debugtool.h>
#include "stack.h"

#include "../deque/deque.h"

struct internal_stack {
  deque deque_data;
};

stack stack_init(const size_t data_size) {
  struct internal_stack *init;
  if (data_size == 0) {
    return NULL;
  }
  init = malloc(sizeof(struct internal_stack));
  if (!init) {
    return NULL;
  }
  init->deque_data = deque_init(data_size);
  if (!init->deque_data) {
    free(init);
    return NULL;
  }
  return init;
}

int stack_size(stack me) {
  avoid_null_pointer(me);
  return deque_size(me->deque_data);
}

int stack_is_empty(stack me) {
  avoid_null_pointer(me);
  return deque_is_empty(me->deque_data);
}

int stack_trim(stack me) {
  avoid_null_pointer(me);
  return deque_trim(me->deque_data);
}

void stack_copy_to_array(void *const arr, stack me) {
  avoid_null_pointer(me);
  deque_copy_to_array(arr, me->deque_data);
}

int stack_push(stack me, void *const data) {
  avoid_null_pointer(me);
  return deque_push_back(me->deque_data, data);
}

int stack_pop(void *const data, stack me) {
  avoid_null_pointer(me);
  return deque_pop_back(data, me->deque_data) == 0;
}

int stack_top(void *const data, stack me) {
  avoid_null_pointer(me);
  return deque_get_last(data, me->deque_data) == 0;
}

int stack_clear(stack me) {
  avoid_null_pointer(me);
  return deque_clear(me->deque_data);
}

stack stack_destroy(stack me) {
  avoid_null_pointer(me);
  deque_destroy(me->deque_data);
  free(me);
  return NULL;
}

