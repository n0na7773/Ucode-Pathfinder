#pragma once
#ifndef LIBMX_H
#define LIBMX_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <fcntl.h>
//#include <wchar.h>
//#include <locale.h>
#include <malloc/malloc.h>

typedef struct s_list { 
    void *data;
    struct s_list *next; 
}              t_list;

//Utils Pack
void mx_printchar(char c); // 100
void mx_print_unicode(wchar_t c); // done
void mx_printstr(const char *s);  // 100
void mx_print_strarr(char **arr, const char *delim); // done
void mx_printint(int n);  // 100
double mx_pow(double n, unsigned int pow); // 100
int mx_sqrt(int x);  // 100
char *mx_nbr_to_hex(unsigned long nbr); // 80 REMAKE still 80
unsigned long mx_hex_to_nbr(const char *hex);  // 100
char *mx_itoa(int number); // done TEST
void mx_foreach(int *arr, int size, void (*f)(int)); // 100
int mx_binary_search(char **arr, int size, const char *s, int *count); // 100
int mx_bubble_sort(char **arr, int size); // 100
int mx_quicksort(char **arr, int left, int right); // done TEST

//String Pack
int mx_strlen(const char *s); // 100
void mx_swap_char(char *s1, char *s2); // 100
void mx_str_reverse(char *s); // 100 i have 80 because of test without input
void mx_strdel(char **str); // 100
void mx_del_strarr(char ***arr); // 100
int mx_get_char_index(const char *str, char c); // done
char *mx_strdup(const char *s1); // 100
char *mx_strndup(const char *s1, size_t n); // done 81
char *mx_strcpy(char *dst, const char *src); // 100
char *mx_strncpy(char *dst, const char *src, int len); // FAIL done
int mx_strcmp(const char *s1, const char *s2); // 100
char *mx_strcat(char *restrict s1, const char *restrict s2); // 100
char *mx_strstr(const char *haystack, const char *needle); // 100
int mx_get_substr_index(const char *str, const char *sub); // done
int mx_count_substr(const char *str, const char *sub); // 75 REMAKE
int mx_count_words(const char *str, char c); // 75 REMAKE
char *mx_strnew(const int size); // 100
char *mx_strtrim(const char *str); // FAIL done 70 succ
char *mx_del_extra_spaces(const char *str); // FAIL done IDK 
char **mx_strsplit(const char *s, char c); // FAIL done 50 success
char *mx_strjoin(const char *s1, const char *s2); // 50 REMAKE done now i have 75
char *mx_file_to_str(const char *file); // UNKNOWN FAIL  done
char *mx_replace_substr(const char *str, const char *sub, const char *replace); // done FAIL
int mx_read_line(char **lineptr, size_t buf_size, char delim, const int fd); // done FAIL

//Memory Pack
void *mx_memset(void *b, int c, size_t len); // done
void *mx_memcpy(void *restrict dst, const void *restrict src, size_t n); // done
void *mx_memccpy(void *restrict dst, const void *restrict src, int c, size_t n); // done
int mx_memcmp(const void *s1, const void *s2, size_t n); // done
void *mx_memchr(const void *s, int c, size_t n); // done
void *mx_memrchr(const void *s, int c, size_t n); // done
void *mx_memmem(const void *big, size_t big_len, const void *little, size_t little_len); // done FAIL
void *mx_memmove(void *dst, const void *src, size_t len); // done
void *mx_realloc(void *ptr, size_t size); // done

//List Pack
t_list *mx_create_node(void *data);  // 100
void mx_push_front(t_list **list, void *data);  // 100
void mx_push_back(t_list **list, void *data);  // 100
void mx_pop_front(t_list **head);  // 100
void mx_pop_back(t_list **head);  // FAIL
int mx_list_size(t_list *list);  // 100
t_list *mx_sort_list(t_list *lst, bool (*cmp)(void *, void *));  // 100

//Other
bool mx_isdigit(int c);
bool mx_isalpha(int c);
bool mx_islower(int c);
bool mx_isupper(int c);
bool mx_isspace(char c);
char *mx_strchr(const char *s, int c); // 100
int mx_strncmp(const char *s1, const char *s2, int n); // 45 FAIL done
int mx_atoi(const char *str); // 76
void mx_printerr(const char *str);

#endif
