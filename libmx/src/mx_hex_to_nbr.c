#include "../inc/libmx.h"

bool mx_isuppernbr(int c){
    if (c >= 65 && c <= 70) {
        return true;
    } 
    else {
        return false;
    }
}
bool mx_islowernbr(int c){
    if (c >= 97  && c <= 102) {
        return true;
    } 
    else {
        return false;
    }
}
bool mx_isalphanbr(int c){
    if ( (c >= 65 && c <= 70) || (c >= 97  && c <= 102) ) {
        return true;
    } 
    else {
        return false;
    }
}
bool mx_isdigitnbr(int c){
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
        if (mx_isdigitnbr(hex[i])){
            res += ((hex[i] - 48) * dec);
            dec *= 16;
        }   
        if(mx_isalphanbr(hex[i])){
            if(mx_isuppernbr(hex[i])){
                res += ((hex[i] - 55) * dec);
                dec *= 16;
            }
            else if(mx_islowernbr(hex[i])){
                res += ((hex[i] - 87) * dec);
                dec *= 16;
            }
        }
    }
    return res;
}

