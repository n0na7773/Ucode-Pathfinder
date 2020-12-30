#include "../inc/libmx.h"

void *mx_memrchr(const void *s, int c, size_t n){
    if(n == 0) return 0;

    const char *cs = s;
    
    for(size_t i = n; i > 0; i--){
        if(cs[i] == c) return (char*)&cs[i];
    }
    return NULL;
}
