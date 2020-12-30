#include "../inc/libmx.h"

int mx_sqrt(int x) {
    if (x > 0) {
        if (x == 1) 
            return x; 
        int result = 1; 
        for (int i = 1; i * i != x; i++) {
            result = i;
            if (i * i > x || i * i < 0) return 0; 
        } 
        return result + 1; 
    }
    else return 0;
}
