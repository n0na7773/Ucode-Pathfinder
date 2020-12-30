#include "../inc/libmx.h"

char *mx_strstr(const char *s1, const char *s2) {
    while (*s1) {
		const char *start = s1;
		const char *sub = s2;
		while (*s1 && *sub && *s1 == *sub) {
		    s1++;
		    sub++;
		}
		if (!*sub) return (char*)start;	  
		s1 = start + 1; 
	}
	return NULL;
}
