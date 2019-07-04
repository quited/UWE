//
// Created by 31838 on 7/2/2019.
//

#ifndef DATA_STACK_H
#define DATA_STACK_H

#include <stdlib.h>

typedef struct internal_stack *stack;

stack stack_init(size_t data_size);

int stack_size(stack me);

int stack_is_empty(stack me);

int stack_trim(stack me);

void stack_copy_to_array(void *arr, stack me);

int stack_push(stack me, void *data);

int stack_pop(void *data, stack me);

int stack_top(void *data, stack me);

int stack_clear(stack me);

stack stack_destroy(stack me);

#endif //DATA_STACK_H
