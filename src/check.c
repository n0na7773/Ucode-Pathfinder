#include "../inc/pathfinder.h"

bool checknum(const char *num){
    if (mx_strcmp(num, "") == 0 || num == NULL || mx_atoi(num) < 0) return false;
    for (int i = 0; i < mx_strlen(mx_strtrim(num)); i++) {
        if (!mx_isdigit(num[i])) return false;
    }
    return true;
}

bool checkword(const char *word) {
    for (int i = 0; i < mx_strlen(word); i++) {    
        if (!mx_isalpha(word[i])) return false;
    }
    return true;
}

bool correct_line(const char *from, const char *to, const char *dist) {
    if (!from || !to || !dist) return false;
    if(!checkword(from)) return false;
    if(!checkword(to)) return false;
    if(!checknum(dist)) return false;

    if (mx_strcmp(from, to) == 0) return false;

    return true;
}
