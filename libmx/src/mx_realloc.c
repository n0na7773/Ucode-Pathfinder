#include "../inc/libmx.h"

void *mx_realloc(void *ptr, size_t size){
    size_t prev_size = malloc_size(ptr);

    if (!size) {
        free(ptr);
        return NULL;
    }
    else if (!ptr) 
        return malloc(size);
    else if (size <= prev_size) 
        return ptr;
    
    void *new_ptr = malloc(size);

    mx_memcpy(new_ptr, ptr, prev_size);
    free(ptr);

    return new_ptr;
}
