#include "datastructures.h"
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

static int __max_heap(int32_t a, int32_t b)
{
    return a > b;
}
static int __min_heap(int32_t a, int32_t b)
{
    return a < b;
}

static int (*__heap_cmp[2])(int32_t a, int32_t b) = {&__min_heap, &__max_heap};

ds_heap_t *ds_heap_create(size_t initial_size, ds_heap_type_t type)
{
    ds_heap_t *ret = (ds_heap_t *)calloc(1, sizeof(ds_heap_t));
    if (ret == NULL)
    {
        return NULL;
    }
    ret->heap = (ds_heap_element_t **)calloc(initial_size, sizeof(ds_heap_element_t *));
    if (ret->heap == NULL)
    {
        return NULL;
    }
    ret->last = 0;
    ret->size = initial_size;
    ret->type = type;
    return ret;
}

ds_heap_t *ds_heap_insert(ds_heap_t *heap, int priority, void *value)
{
    ds_heap_element_t *elem = malloc(sizeof(ds_heap_element_t));
    if (elem == NULL)
    {
        return NULL;
    }
    elem->priority = priority;
    elem->value = value;
    if (heap->last == heap->size)
    {
        heap->heap = (ds_heap_element_t **)realloc((void *)heap->heap, (1 + heap->size + (heap->size / 2)) * sizeof(ds_heap_element_t *));
        if (heap->heap == NULL)
        {
            return NULL;
        }
        for (size_t i = heap->size; i < 1 + heap->size + (heap->size / 2); i++)
        {
            heap->heap[i] = NULL;
        }
        heap->size = 1 + heap->size + (heap->size / 2);
    }
    heap->heap[heap->last] = elem;
    if (heap->last == 0)
    {
        heap->last++;
        return heap;
    }
    size_t parent = heap->last;
    do
    {
        parent = (parent - 1) / 2;
        if (__heap_cmp[heap->type](heap->heap[heap->last]->priority, heap->heap[parent]->priority))
        {
            ds_heap_element_t *tmp = heap->heap[heap->last];
            heap->heap[heap->last] = heap->heap[parent];
            heap->heap[parent] = tmp;
        }
    } while (parent != 0);
    heap->last++;
    return heap;
}

ds_heap_element_t *ds_heap_get_first(ds_heap_t *heap)
{
    return heap->heap[0];
}

ds_heap_t *ds_heap_remove_max(ds_heap_t *heap)
{
    if (heap->last == 0)
    {
        return heap;
    }
    else if (heap->last == 1)
    {
        free(heap->heap[0]);
        heap->heap[0] = NULL;
        heap->last--;
        return heap;
    }
    free(heap->heap[0]);
    heap->heap[0] = heap->heap[heap->last - 1];
    heap->heap[heap->last - 1] = NULL;
    heap->last--;
    for (int i = 0; i < 2; i++)
    {
        size_t parent = 0;
        size_t current = 2 * parent + 1;
        int change = 1;
        while (current < heap->last && change)
        {
            change = 0;
            if (__heap_cmp[heap->type](heap->heap[current]->priority, heap->heap[parent]->priority))
            {
                ds_heap_element_t *tmp = heap->heap[current];
                heap->heap[current] = heap->heap[parent];
                heap->heap[parent] = tmp;
                parent = current;
                current = 2 * parent + 1;
                change = 1;
                continue;
            }
            current = 2 * parent + 2;
            if (current >= heap->last)
            {
                break;
            }
            if (__heap_cmp[heap->type](heap->heap[current]->priority, heap->heap[parent]->priority))
            {
                ds_heap_element_t *tmp = heap->heap[current];
                heap->heap[current] = heap->heap[parent];
                heap->heap[parent] = tmp;
                parent = current;
                current = 2 * parent + 1;
                change = 1;
            }
        }
    }
    if (heap->last+1 <= heap->size / 5)
    {
        heap->heap = (ds_heap_element_t **)realloc(heap->heap, (heap->size / 5) * sizeof(ds_heap_element_t *));
        heap->size /= 5;
    }
}

void ds_heap_free(ds_heap_t *heap)
{
    for (size_t i = 0; i < heap->last; i++)
    {
        free(heap->heap[i]);
    }
    free(heap->heap);
    free(heap);
}

void ds_heap_print_arr(ds_heap_t *heap)
{
    if (heap->last == 0)
    {
        printf("Heap is empty\n");
        return;
    }
    else if (heap->last == 1)
    {
        printf("size: %zu/%zu; [%" PRIi32 "]\n", heap->last, heap->size, heap->heap[0]->priority);
        return;
    }
    printf("size: %zu/%zu; [%" PRIi32 "] -", heap->last, heap->size, heap->heap[0]->priority);
    for (size_t i = 1; i < heap->last - 1; i++)
    {
        printf(" [%" PRIi32 "] -", heap->heap[i]->priority);
    }
    printf(" [%" PRIi32 "]\n", heap->heap[heap->last - 1]->priority);
}