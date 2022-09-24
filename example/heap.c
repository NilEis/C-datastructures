#include "datastructures.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    ds_heap_t *heap = ds_heap_create(2, MAX_HEAP);
    if (heap == NULL)
    {
        printf("Could not allocate memory\n");
        exit(-1);
    }
    for (int i = 0; i < 10; i++)
    {
        if (ds_heap_insert(heap, rand() % 500, NULL) == NULL)
        {
            printf("Could not allocate memory\n");
            exit(-1);
        }
        ds_heap_print_arr(heap);
    }
    for (int i = 0; i < 11; i++)
    {
        if (ds_heap_remove_max(heap) == NULL)
        {
            printf("Could not allocate memory\n");
            exit(-1);
        }
        ds_heap_print_arr(heap);
    }
    ds_heap_free(heap);
    return 0;
}
