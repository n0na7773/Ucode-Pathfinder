#include "../inc/libmx.h"

char *mx_strdup(const char *s1) {
    char *cp = mx_strnew(mx_strlen(s1));
    if (cp == NULL) return NULL;                              
    return (mx_strcpy(cp, s1));                              
}
