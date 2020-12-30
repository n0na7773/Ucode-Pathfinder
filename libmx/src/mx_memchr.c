#include "../inc/libmx.h"

void *mx_memchr(const void *s, int c, size_t n){
    if(n == 0) return 0;
    
    const char *cs = s;
    
    for(size_t i = 0; i < n; i++){
        if(cs[i] == c) return (char*)&cs[i];
    }
    return NULL;
}
