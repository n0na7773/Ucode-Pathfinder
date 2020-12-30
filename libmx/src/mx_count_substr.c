#include "../inc/libmx.h"

int mx_count_substr(const char *str, const char *sub) {
    if (!sub || !str) return -1;
    if (mx_strcmp(sub, "") == 0) return 0;

    int str_len = mx_strlen(str);
    int sub_len = mx_strlen(sub);
    int count = 0, count_sub, j;

    for (int i = 0; i < str_len;) {
        j = 0;
        count_sub = 0;
        while (str[i] == sub[j]) { 
            count_sub++;
            i++;
            j++;
        }
        if (count_sub == sub_len)
        {
            count++;                                   
            count_sub = 0;
        }
        else
            i++;
    }

    return count;
}
