//
// Created by 31838 on 7/2/2019.
//

#include "deque.h"

#include <string.h>
#include <errno.h>

static const int BLOCK_SIZE = 8;
static const double RESIZE_RATIO = 1.5;

struct internal_deque {
    size_t data_size;
    int start_index;
    int end_index;
    int block_count;
    struct node *block;
};

struct node {
    void *data;
};

deque deque_init(const size_t data_size) {
    struct internal_deque *init;
    struct node *block;
    if (data_size == 0) {
        return NULL;
    }
    init = malloc(sizeof(struct internal_deque));
    if (!init) {
        return NULL;
    }
    init->data_size = data_size;
    init->start_index = BLOCK_SIZE / 2;
    init->end_index = init->start_index + 1;
    init->block_count = 1;
    init->block = malloc(sizeof(struct node));
    if (!init->block) {
        free(init);
        return NULL;
    }
    block = init->block;
    block->data = malloc(BLOCK_SIZE * init->data_size);
    if (!block->data) {
        free(init->block);
        free(init);
        return NULL;
    }
    return init;
}

int deque_size(deque me) {
    return me->end_index - me->start_index - 1;
}

int deque_is_empty(deque me) {
    return deque_size(me) == 0;
}

int deque_trim(deque me) {
    int i;
    const int start_block =
            me->start_index == -1 ? 0 : me->start_index / BLOCK_SIZE;
    const int end_block =
            me->end_index == 0 ? 0 : (me->end_index - 1) / BLOCK_SIZE;
    const int new_block_count = end_block - start_block + 1;
    void *const new_block = malloc(new_block_count * sizeof(struct node));
    if (!new_block) {
        return -ENOMEM;
    }
    for (i = 0; i < start_block; i++) {
        const struct node block_item = me->block[i];
        free(block_item.data);
    }
    for (i = end_block + 1; i < me->block_count; i++) {
        const struct node block_item = me->block[i];
        free(block_item.data);
    }
    memcpy(new_block,
           &me->block[start_block],
           new_block_count * sizeof(struct node));
    free(me->block);
    me->block = new_block;
    me->block_count = new_block_count;
    me->start_index -= start_block * BLOCK_SIZE;
    me->end_index -= start_block * BLOCK_SIZE;
    return 0;
}

void deque_copy_to_array(void *const arr, deque me) {
    int i;
    for (i = 0; i < deque_size(me); i++) {
        deque_get_at((char *) arr + i * me->data_size, me, i);
    }
}

int deque_push_front(deque me, void *const data) {
    struct node block_item;
    int block_index;
    int inner_index;
    if (me->start_index == -1) {
        block_index = -1;
        inner_index = BLOCK_SIZE - 1;
    } else {
        block_index = me->start_index / BLOCK_SIZE;
        inner_index = me->start_index % BLOCK_SIZE;
    }
    if (inner_index == BLOCK_SIZE - 1) {
        struct node *block_item_reference;
        if (block_index == -1) {
            int i;
            const int old_block_count = me->block_count;
            const int new_block_count =
                    (int) (RESIZE_RATIO * me->block_count) + 1;
            const int added_blocks = new_block_count - old_block_count;
            void *temp = realloc(me->block,
                                 new_block_count * sizeof(struct node));
            if (!temp) {
                return -ENOMEM;
            }
            me->block = temp;
            me->block_count = new_block_count;
            memmove(&me->block[added_blocks],
                    me->block,
                    old_block_count * sizeof(struct node));
            block_index = added_blocks - 1;
            me->start_index += added_blocks * BLOCK_SIZE;
            me->end_index += added_blocks * BLOCK_SIZE;
            for (i = 0; i < added_blocks; i++) {
                struct node *const block_item_copy = &me->block[i];
                block_item_copy->data = NULL;
            }
        }
        block_item_reference = &me->block[block_index];
        if (!block_item_reference->data) {
            block_item_reference->data = malloc(BLOCK_SIZE * me->data_size);
            if (!block_item_reference->data) {
                return -ENOMEM;
            }
        }
    }
    block_item = me->block[block_index];
    memcpy((char *) block_item.data + inner_index * me->data_size, data,
           me->data_size);
    me->start_index--;
    return 0;
}

int deque_push_back(deque me, void *const data) {
    struct node block_item;
    const int block_index = me->end_index / BLOCK_SIZE;
    const int inner_index = me->end_index % BLOCK_SIZE;
    if (inner_index == 0) {
        struct node *block_item_reference;
        if (block_index == me->block_count) {
            int i;
            const int new_block_count =
                    (int) (RESIZE_RATIO * me->block_count) + 1;
            void *temp = realloc(me->block,
                                 new_block_count * sizeof(struct node));
            if (!temp) {
                return -ENOMEM;
            }
            me->block = temp;
            me->block_count = new_block_count;
            for (i = block_index; i < me->block_count; i++) {
                struct node *const block_item_copy = &me->block[i];
                block_item_copy->data = NULL;
            }
        }
        block_item_reference = &me->block[block_index];
        if (!block_item_reference->data) {
            block_item_reference->data = malloc(BLOCK_SIZE * me->data_size);
            if (!block_item_reference->data) {
                return -ENOMEM;
            }
        }
    }
    block_item = me->block[block_index];
    memcpy((char *) block_item.data + inner_index * me->data_size, data,
           me->data_size);
    me->end_index++;
    return 0;
}

int deque_pop_front(void *const data, deque me) {
    int block_index;
    int inner_index;
    struct node block_item;
    if (deque_is_empty(me)) {
        return -EINVAL;
    }
    me->start_index++;
    block_index = me->start_index / BLOCK_SIZE;
    inner_index = me->start_index % BLOCK_SIZE;
    block_item = me->block[block_index];
    if (!data)return 0;
    memcpy(data, (char *) block_item.data + inner_index * me->data_size,
           me->data_size);
    return 0;
}

int deque_pop_back(void *const data, deque me) {
    int block_index;
    int inner_index;
    struct node block_item;
    if (deque_is_empty(me)) {
        return -EINVAL;
    }
    me->end_index--;
    block_index = me->end_index / BLOCK_SIZE;
    inner_index = me->end_index % BLOCK_SIZE;
    block_item = me->block[block_index];
    if (!data)return 0;
    memcpy(data, (char *) block_item.data + inner_index * me->data_size,
           me->data_size);
    return 0;
}

int deque_set_first(deque me, void *const data) {
    return deque_set_at(me, 0, data);
}

int deque_set_at(deque me, int index, void *const data) {
    int block_index;
    int inner_index;
    struct node block_item;
    if (index < 0 || index >= deque_size(me)) {
        return -EINVAL;
    }
    index += me->start_index + 1;
    block_index = index / BLOCK_SIZE;
    inner_index = index % BLOCK_SIZE;
    block_item = me->block[block_index];
    memcpy((char *) block_item.data + inner_index * me->data_size, data,
           me->data_size);
    return 0;
}

int deque_set_last(deque me, void *const data) {
    return deque_set_at(me, deque_size(me) - 1, data);
}

int deque_get_first(void *const data, deque me) {
    return deque_get_at(data, me, 0);
}

int deque_get_at(void *const data, deque me, int index) {
    int block_index;
    int inner_index;
    struct node block_item;
    if (index < 0 || index >= deque_size(me)) {
        return -EINVAL;
    }
    index += me->start_index + 1;
    block_index = index / BLOCK_SIZE;
    inner_index = index % BLOCK_SIZE;
    block_item = me->block[block_index];
    memcpy(data, (char *) block_item.data + inner_index * me->data_size,
           me->data_size);
    return 0;
}

int deque_get_last(void *const data, deque me) {
    return deque_get_at(data, me, deque_size(me) - 1);
}

int deque_clear(deque me) {
    void *temp_block_data;
    int i;
    struct node *block;
    struct node *const temp_block = malloc(sizeof(struct node));
    if (!temp_block) {
        return -ENOMEM;
    }
    temp_block_data = malloc(BLOCK_SIZE * me->data_size);
    if (!temp_block_data) {
        free(temp_block);
        return -ENOMEM;
    }
    for (i = 0; i < me->block_count; i++) {
        const struct node block_item = me->block[i];
        free(block_item.data);
    }
    free(me->block);
    me->start_index = BLOCK_SIZE / 2;
    me->end_index = me->start_index + 1;
    me->block_count = 1;
    me->block = temp_block;
    block = me->block;
    block->data = temp_block_data;
    return 0;
}

deque deque_destroy(deque me) {
    int i;
    for (i = 0; i < me->block_count; i++) {
        const struct node block_item = me->block[i];
        free(block_item.data);
    }
    free(me->block);
    free(me);
    return NULL;
}
