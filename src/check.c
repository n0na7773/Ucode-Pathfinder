#include "../inc/pathfinder.h"

bool checknum(const char *num){
    if (mx_strcmp(num, "") == 0 || num == NULL || mx_atoi(num) < 0) return false;
    for (int i = 0; i < mx_strlen(num); i++)
        if (!mx_isdigit(num[i])) return false;
    return true;
}
