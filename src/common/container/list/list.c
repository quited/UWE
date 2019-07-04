//
// Created by 31838 on 7/2/2019.
//

#include "list.h"

#include <string.h>
#include <errno.h>

struct internal_list {
    size_t bytes_per_item;
    int item_count;
    struct node *head;
    struct node *tail;
};

struct node {
    struct node *prev;
    void *data;
    struct node *next;
};

list list_init(const size_t data_size) {
    struct internal_list *init;
    if (data_size == 0) {
        return NULL;
    }
    init = malloc(sizeof(struct internal_list));
    if (!init) {
        return NULL;
    }
    init->bytes_per_item = data_size;
    init->item_count = 0;
    init->head = NULL;
    init->tail = NULL;
    return init;
}

int list_size(list me) {
    return me->item_count;
}

int list_is_empty(list me) {
    return list_size(me) == 0;
}

void list_copy_to_array(void *const arr, list me) {
    struct node *traverse = me->head;
    int offset = 0;
    while (traverse) {
        memcpy((char *) arr + offset, traverse->data, me->bytes_per_item);
        offset += me->bytes_per_item;
        traverse = traverse->next;
    }
}

static struct node *list_get_node_from_head(list me, const int index) {
    struct node *traverse = me->head;
    int i;
    for (i = 0; i < index; i++) {
        traverse = traverse->next;
    }
    return traverse;
}

static struct node *list_get_node_from_tail(list me, const int index) {
    struct node *traverse = me->tail;
    int i;
    for (i = me->item_count - 1; i > index; i--) {
        traverse = traverse->prev;
    }
    return traverse;
}

static struct node *list_get_node_at(list me, const int index) {
    if (index < me->item_count / 2) {
        return list_get_node_from_head(me, index);
    }
    return list_get_node_from_tail(me, index);
}

int list_add_first(list me, void *const data) {
    return list_add_at(me, 0, data);
}

int list_add_at(list me, const int index, void *const data) {
    struct node *add;
    if (index < 0 || index > me->item_count) {
        return -EINVAL;
    }
    add = malloc(sizeof(struct node));
    if (!add) {
        return -ENOMEM;
    }
    add->data = malloc(me->bytes_per_item);
    if (!add->data) {
        free(add);
        return -ENOMEM;
    }
    memcpy(add->data, data, me->bytes_per_item);
    if (!me->head) {
        add->prev = NULL;
        add->next = NULL;
        me->head = add;
        me->tail = add;
    } else if (index == 0) {
        struct node *const traverse = me->head;
        traverse->prev = add;
        add->prev = NULL;
        add->next = traverse;
        me->head = add;
    } else if (index == me->item_count) {
        struct node *const traverse = me->tail;
        traverse->next = add;
        add->prev = traverse;
        add->next = NULL;
        me->tail = add;
    } else {
        struct node *const traverse = list_get_node_at(me, index);
        add->prev = traverse->prev;
        add->next = traverse;
        traverse->prev->next = add;
        traverse->prev = add;
    }
    me->item_count++;
    return 0;
}

int list_add_last(list me, void *const data) {
    return list_add_at(me, me->item_count, data);
}

static int list_is_illegal_input(list me, const int index) {
    return index < 0 || index >= me->item_count;
}

int list_remove_first(list me) {
    return list_remove_at(me, 0);
}

int list_remove_at(list me, const int index) {
    struct node *traverse;
    if (list_is_illegal_input(me, index)) {
        return -EINVAL;
    }
    traverse = list_get_node_at(me, index);
    if (index == 0) {
        traverse->next->prev = NULL;
        me->head = traverse->next;
    } else if (index == me->item_count - 1) {
        traverse->prev->next = NULL;
        me->tail = traverse->prev;
    } else {
        traverse->prev->next = traverse->next;
        traverse->next->prev = traverse->prev;
    }
    free(traverse->data);
    free(traverse);
    me->item_count--;
    return 0;
}

int list_remove_last(list me) {
    return list_remove_at(me, me->item_count - 1);
}

int list_set_first(list me, void *const data) {
    return list_set_at(me, 0, data);
}

int list_set_at(list me, const int index, void *const data) {
    struct node *traverse;
    if (list_is_illegal_input(me, index)) {
        return -EINVAL;
    }
    traverse = list_get_node_at(me, index);
    memcpy(traverse->data, data, me->bytes_per_item);
    return 0;
}

int list_set_last(list me, void *const data) {
    return list_set_at(me, me->item_count - 1, data);
}

int list_get_first(void *const data, list me) {
    return list_get_at(data, me, 0);
}

int list_get_at(void *const data, list me, const int index) {
    struct node *traverse;
    if (list_is_illegal_input(me, index)) {
        return -EINVAL;
    }
    traverse = list_get_node_at(me, index);
    memcpy(data, traverse->data, me->bytes_per_item);
    return 0;
}

int list_get_last(void *const data, list me) {
    return list_get_at(data, me, me->item_count - 1);
}

void list_clear(list me) {
    struct node *traverse = me->head;
    while (traverse) {
        struct node *const temp = traverse;
        traverse = traverse->next;
        free(temp->data);
        free(temp);
    }
    me->head = NULL;
    me->item_count = 0;
    me->tail = NULL;
}

list list_destroy(list me) {
    list_clear(me);
    free(me);
    return NULL;
}
