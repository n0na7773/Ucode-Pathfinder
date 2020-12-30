#include "../inc/libmx.h"

char *mx_replace_substr(const char *str, const char *sub, const char *replace){
    if (str == NULL || sub == NULL || replace == NULL) return NULL;
    else if (!*sub) return (char*)str;

    char *res = NULL;

    int broken_leg = 0; //wtf 
    
    for (int i = 0;*str != '\0';i++){
        if(mx_strncmp(str, sub, mx_strlen(sub)) == 0){
            res = mx_strjoin(res, replace);
            str += mx_strlen(sub);
        }
        else{
            char a = str[broken_leg];
            res = mx_strjoin(res, &a);
            str++;
        }
    }
    return res;
}
