#include "../inc/libmx.h"

int mx_memcmp(const void *s1, const void *s2, size_t n){
    if(n == 0) return 0;

    const char *cs1 = s1;
    const char *cs2 = s2;
    
    for(size_t i = 0; i < n; ++i) if(cs1[i] != cs2[i]) return (cs1[i] - cs2[i]);
    
    return 0;
}
