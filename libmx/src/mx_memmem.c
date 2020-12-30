#include "../inc/libmx.h"

void *mx_memmem(const void *big, size_t big_len, const void *little, size_t little_len){
    if (!big) return NULL; 
    if (big_len <= 0) return NULL;
    if (!little) return NULL; 
    if (little_len <= 0) return NULL;

    unsigned char *cbig = (unsigned char *)big;
    unsigned char *clittle = (unsigned char *)little;

    while (*cbig) {
        if (mx_memcmp(cbig, clittle, little_len - 1) == 0) {
            return cbig;
        }
        cbig++;
    }
    return NULL;
}
