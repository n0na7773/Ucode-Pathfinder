#include "../inc/pathfinder.h"

void convert(Node **res_paths, char **path, int size_path){
    Node **temp_res = res_paths; 
    for(int a = 0; a < size_path; a++){//Way to str
        char *temp_str = mx_strdup(mx_itoa(res_paths[a]->full_dist));
        temp_str = mx_strjoin(temp_str, "|");
        while(temp_res[a] != NULL){
            temp_str = mx_strjoin(temp_str, temp_res[a]->name);
            temp_str = mx_strjoin(temp_str, ",");
            temp_res[a] = temp_res[a]->parent;
        }
        path[a] = temp_str;
        
    }
    for(int a = 0; a < size_path; a++){//Reverse way
        char **temp_arr1 = mx_strsplit(path[a], '|');
        char **temp_arr2 = mx_strsplit(temp_arr1[1], ',');
        char *temp_str = NULL;
        for(int i = string_amount(temp_arr2)-1; i >= 0; i--){
            temp_str = mx_strjoin(temp_str, temp_arr2[i]);
            temp_str = mx_strjoin(temp_str, ",");
        }
        temp_str = mx_strjoin(temp_str, "|");
        temp_str = mx_strjoin(temp_str, temp_arr1[0]);
        path[a] = temp_str;
    }
}

void sorting(char **path, char **islands, int **arr, unsigned long size){
    //Sort by distance
    for(unsigned long i = 0; i < size; i++){
        for(unsigned long j = 0; j < size-1; j++){
            char **temp1 = mx_strsplit(path[j], '|');
            char **temp2 = mx_strsplit(path[j+1], '|');
            if(mx_atoi(temp1[1]) > mx_atoi(temp2[1])){
                char *temp_path = mx_strdup(path[j]);
                path[j] = mx_strdup(path[j+1]);
                path[j+1] = mx_strdup(temp_path);
            }
        }
    }
    
    //Write only minimum paths
    char **temp_num = mx_strsplit(path[0], '|');
    char **only_min = (char **)malloc((size*size)*sizeof(char));
    int size_min = 0;
    for(unsigned long i = 0; i < size; i++){
        char **temp = mx_strsplit(path[i], '|');
        if(mx_atoi(temp_num[1]) != mx_atoi(temp[1]))
            break;
        only_min[size_min] = mx_strdup(path[i]);
        size_min++;
        
    }
    
    //Sort by names
    for(int i = 0; i < size_min; i++){
        for(int j = 0; j < size_min-1; j++){
            char **tmp_without_num1 = mx_strsplit(only_min[j], '|');
            char **tmp_without_num2 = mx_strsplit(only_min[j+1], '|');
            char **tmp1 = mx_strsplit(tmp_without_num1[0], ',');
            char **tmp2 = mx_strsplit(tmp_without_num2[0], ',');
            int z = 1;
            while(true){
                if(!tmp1[z] || !tmp2[z]) break;
                if(get_index_in_strarr(islands, tmp1[z]) > get_index_in_strarr(islands, tmp2[z]) && mx_strcmp(tmp1[z-1], tmp2[z-1]) == 0){
                    char *tmp_path = mx_strdup(only_min[j]);
                    only_min[j] = mx_strdup(only_min[j+1]);
                    only_min[j+1] = mx_strdup(tmp_path);
                    break;
                }
                z++;
            }           
        }
    }

    //Output
    for(int  i = 0; i < size_min; i++){
        char **temp = mx_strsplit(only_min[i], '|');
        print_path(temp[0], arr, islands);
    }
}

void print_path(char *path, int **matrix, char **islands) {
    char **temp = mx_strsplit(path, ',');
    int sum = 0;
    int temp_size = string_amount(temp);
    

    //Path
    mx_printstr("========================================\n");
    mx_printstr("Path: ");
    mx_printstr(temp[0]);
    mx_printstr(" -> ");
    mx_printstr(temp[temp_size-1]);
    mx_printchar('\n');

    //Route
    mx_printstr("Route: ");
    for (int i = 0; i < temp_size; i++){
        mx_printstr(temp[i]);
        if(i >= 0 && i < temp_size-1) mx_printstr(" -> ");
    }

    //Distance
    int first = get_index_in_strarr(islands, temp[0]);
    int second = get_index_in_strarr(islands, temp[1]);
    if(temp_size == 2){
        mx_printstr("\nDistance: ");
        mx_printint(matrix[first][second]);
        mx_printstr("\n========================================\n");
    } else {
        mx_printstr("\nDistance: ");
        mx_printint(matrix[first][second]);
        sum += matrix[first][second];
        for (int i = 1; i <temp_size-1; i++){
            first = get_index_in_strarr(islands, temp[i]);
            second = get_index_in_strarr(islands, temp[i+1]);
            mx_printstr(" + ");
            sum += matrix[first][second];
            mx_printint(matrix[first][second]);
        }
        mx_printstr(" = ");
        mx_printint(sum);
        mx_printstr("\n========================================\n");
    }
}

int get_index_in_strarr(char **arr, char *sub){
    for(int i = 0; arr[i]; i++){
        if(mx_strcmp(arr[i], sub) == 0) return i;
    }
    return -1;
}

int string_amount(char **arr) {
    int res = 0;
    while(arr[res]){
        res++;
    }
    return res;
}
