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

bool checkline(const char *from, const char *to, const char *dist) {
    if (!from || !to || !dist) return false;

    if(!checkword(from)) return false;
    if(!checkword(to)) return false;
    if(!checknum(dist)) return false;

    if (mx_strcmp(from, to) == 0) return false;

    return true;
}

void checklast(char *str) {
    int num_n = 0;
    for(int i = 0; i < mx_strlen(str)-1; i++) {
        if(str[i] == '\n') num_n++;
        if(str[i] == '\n' && !mx_isalpha(str[i+1])) {
            mx_printerr("error: line ");
            mx_printerr(mx_itoa(num_n+1)); 
            mx_printerr(" is not valid\n");
            exit(0);
        }
    }
}
