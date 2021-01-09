#include "../inc/pathfinder.h"

void way_to_str(Node **res_paths, char **path, int size_path){
    Node **tmp_res = res_paths; 
    for(int a = 0; a < size_path; a++){//Way to str
        char *tmp_str = mx_strdup(mx_itoa(res_paths[a]->full_dist));
        tmp_str = mx_strjoin(tmp_str, "|");
        while(tmp_res[a] != NULL){
        tmp_str = mx_strjoin(tmp_str, tmp_res[a]->name);
        tmp_str = mx_strjoin(tmp_str, ",");
        tmp_res[a] = tmp_res[a]->parent;
        }
        path[a] = tmp_str;
    }
    for(int a = 0; a < size_path; a++){//Reverse way
        char **tmp_arr1 = mx_strsplit(path[a], '|');
        char **tmp_arr2 = mx_strsplit(tmp_arr1[1], ',');
        char *tmp_str = NULL;
        for(int i = amount_of_el(tmp_arr2)-1; i >= 0; i--){
            tmp_str = mx_strjoin( tmp_str, tmp_arr2[i]);
            tmp_str = mx_strjoin( tmp_str, ",");
        }
        tmp_str = mx_strjoin( tmp_str, "|");
        tmp_str = mx_strjoin( tmp_str, tmp_arr1[0]);
        path[a] = tmp_str;
    }
}

int get_index_in_strarr(char **arr, char *sub){
    for(int i = 0; arr[i]; i++){
        if(mx_strcmp(arr[i], sub) == 0) return i;
    }
    return -1;
}

void print_path(char *path, int **matrix, char **islands) {
    char **tmp = mx_strsplit(path, ',');
    int tmp_size = amount_of_el(tmp);
    int sum = 0;
    //Path
    mx_printstr("========================================\n");
    mx_printstr("Path: ");
    mx_printstr(tmp[0]);
    mx_printstr(" -> ");
    mx_printstr(tmp[tmp_size-1]);
    mx_printchar('\n');
    //Route
    mx_printstr("Route: ");
    for (int i = 0; i < tmp_size; i++){
        mx_printstr(tmp[i]);
        if(i >= 0 && i < tmp_size-1) mx_printstr(" -> ");
    }
    //Distance
    int first = get_index_in_strarr(islands, tmp[0]);
    int second = get_index_in_strarr(islands, tmp[1]);
    if(tmp_size == 2){
        mx_printstr("\nDistance: ");
        mx_printint(matrix[first][second]);
        mx_printstr("\n========================================\n");
    } else {
        mx_printstr("\nDistance: ");
        mx_printint(matrix[first][second]);
        sum+=matrix[first][second];
        for (int i = 1; i <tmp_size-1; i++){
            first = get_index_in_strarr(islands, tmp[i]);
            second = get_index_in_strarr(islands, tmp[i+1]);
            mx_printstr(" + ");
            sum+=matrix[first][second];
            mx_printint(matrix[first][second]);
        }
        mx_printstr(" = ");
        mx_printint(sum);
        mx_printstr("\n========================================\n");
    }
}

void sort_path_all(char **path, char **islands, int **arr, unsigned long size){
    //Sort by distance
    for(unsigned long i = 0; i < size; i++){
        for(unsigned long j = 0; j < size-1; j++){
            char **tmp1 = mx_strsplit(path[j], '|');
            char **tmp2 = mx_strsplit(path[j+1], '|');
            if(mx_atoi(tmp1[1]) > mx_atoi(tmp2[1])){
                char *tmp_path = mx_strdup(path[j]);
                path[j] = mx_strdup(path[j+1]);
                path[j+1] = mx_strdup(tmp_path);
            }
        }
    }
    
    //Write only minimum paths
    char **tmp_num = mx_strsplit(path[0], '|');
    char **only_min = (char **)malloc((size*size)*sizeof(char));
    int size_min = 0;
    for(unsigned long i = 0; i < size; i++){
        char **tmp = mx_strsplit(path[i], '|');
        if(mx_atoi(tmp_num[1]) != mx_atoi(tmp[1]))
            break;
        only_min[size_min] = mx_strdup(path[i]);
        size_min++;
    }
    
    //Sort by names
    sort_path_names(only_min, islands, size_min);

    //Output
    for(int  i = 0; i < size_min; i++){
        char **tmp = mx_strsplit(only_min[i], '|');
        print_path(tmp[0], arr, islands);
    }
}

void sort_path_names(char **path, char **islands, unsigned long size){
    int *path_to_num = (int *)malloc((size)*sizeof(int));
    for(unsigned long i = 0; i < size; i++){
        path_to_num[i] = 10;
    }
    for(unsigned long i = 0; i < size; i++){
        char **tmp_without_num = mx_strsplit(path[i], '|');
        char **tmp = mx_strsplit(tmp_without_num[0], ',');
        for(int j =0; tmp[j]; j++){
            path_to_num[i] += get_index_in_strarr(islands, tmp[j]);
            path_to_num[i] *= 10;
        }
    }
    for(unsigned long i = 0; i < size; i++){
        for(unsigned long j = 0; j < size-1; j++){
            if(amount_of_num(path_to_num[j]) < amount_of_num(path_to_num[j+1])){
                int tmp = path_to_num[j];
                path_to_num[j] = path_to_num[j+1];
                path_to_num[j+1] = tmp;
                char *tmp_path = mx_strdup(path[j]);
                path[j] = mx_strdup(path[j+1]);
                path[j+1] = mx_strdup(tmp_path);
            }
            if(amount_of_num(path_to_num[j]) == amount_of_num(path_to_num[j+1])){
                if(path_to_num[j] > path_to_num[j+1]){
                    int tmp = path_to_num[j];
                    path_to_num[j] = path_to_num[j+1];
                    path_to_num[j+1] = tmp;
                    char *tmp_path = mx_strdup(path[j]);
                    path[j] = mx_strdup(path[j+1]);
                    path[j+1] = mx_strdup(tmp_path);
                }
            }
        }
    }
}

int amount_of_el(char **arr) {
    int res = 0;
    while(arr[res]){
        res++;
    }
    return res;
}

int amount_of_num(int num) {
    int cpy_num = num;
    int res = 0;
    do {
        res++;
        cpy_num /=10;
    } while (cpy_num  != 0);
    return res;
}
