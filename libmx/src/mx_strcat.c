#include "../inc/libmx.h"

char *mx_strcat(char *s1, const char *s2){
    char* strret = s1;
    int len1 = mx_strlen(s1); 
    int len2 = mx_strlen(s2); 
  if((s1 != NULL) && (s2 != NULL)) {
    while(len1--) {
      s1++;
    }
    while(len2--) {
      *s1++ = *s2++;
    }
    *s1 = '\0';
  }
  return strret;
}
