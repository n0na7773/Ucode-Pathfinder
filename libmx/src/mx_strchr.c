#include "../inc/libmx.h"

char* mx_strchr(const char*s, int c) {
    while(*s != c && *s != '\0') {
        s++;
    }
    if (*s == c) return (char *)s;
    else return NULL;
}
