#include "../inc/libmx.h"

bool mx_isupper(int c){
    if (c >= 65 && c <= 70) {
        return true;
    } 
    else {
        return false;
    }
}
bool mx_islower(int c){
    if (c >= 97  && c <= 102) {
        return true;
    } 
    else {
        return false;
    }
}
bool mx_isalpha(int c){
    if ( (c >= 65 && c <= 70) || (c >= 97  && c <= 102) ) {
        return true;
    } 
    else {
        return false;
    }
}
bool mx_isdigit(int c){
    if (c >= 49 && c <= 57) {
        return true;
    } 
    else {
        return false;
    }
}

unsigned long mx_hex_to_nbr(const char *hex){
    if (hex == NULL){
        return 0;
    }
    int len = 0;
    while (hex[len] != '\0'){
        len++;
    }
    unsigned long res = 0;
    unsigned long dec = 1;;
    for (int i = len - 1; i >=0; i--){
        if (mx_isdigit(hex[i])){
            res += ((hex[i] - 48) * dec);
            dec *= 16;
        }   
        if(mx_isalpha(hex[i])){
            if(mx_isupper(hex[i])){
                res += ((hex[i] - 55) * dec);
                dec *= 16;
            }
            else if(mx_islower(hex[i])){
                res += ((hex[i] - 87) * dec);
                dec *= 16;
            }
        }
    }
    return res;
}

