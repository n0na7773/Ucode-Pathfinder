#include "../inc/libmx.h"

int mx_count_words(const char *str, char c) {
    int count = 0;
    if(!str) return -1;
    for (int i = 0; str[i] != '\0'; i++) {
        if(str[i] == c && str[i+1] != ' ') {
            count++;
        }
    }   
    return count + 1;
}
