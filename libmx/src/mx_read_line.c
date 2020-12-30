#include "../inc/libmx.h"

int mx_read_line(char **lineptr, size_t buf_size, char delim, const int fd){
    (*lineptr)++;
    size_t super = buf_size;
    char space = delim;
    if (space == ' ') super++;
    int result = fd;
    return result*result;
}
