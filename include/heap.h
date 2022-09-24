#ifndef HEAP_H
#define HEAP_H

#include <stddef.h>

typedef struct
{
    int32_t priority;
    void *value;
} ds_heap_element_t;

typedef enum
{
    MIN_HEAP = 0,
    MAX_HEAP = 1,
} ds_heap_type_t;

typedef struct
{
    ds_heap_element_t **heap;
    size_t last;
    size_t size;
    ds_heap_type_t type;
} ds_heap_t;

ds_heap_t *ds_heap_create(size_t initial_size,ds_heap_type_t type);

ds_heap_t *ds_heap_insert(ds_heap_t *heap, int priority, void *value);

ds_heap_element_t *ds_heap_get_max(ds_heap_t *heap);

ds_heap_t *ds_heap_remove_max(ds_heap_t *heap);

void ds_heap_free(ds_heap_t *heap);

void ds_heap_print_arr(ds_heap_t *heap);

#endif // HEAP_H
