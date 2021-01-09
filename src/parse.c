#include "../inc/pathfinder.h"

void parse(const char *filename) {
    char *file = mx_file_to_str(filename); 
    
    if(!file){
        mx_printerr("error: file ");
        mx_printerr(filename);
        mx_printerr(" does not exist\n");
        exit(0);
    }
    if(mx_strlen(file) == 0){
        mx_printerr("error: file ");
        mx_printerr(filename);
        mx_printerr(" is empty\n");
        exit(0);
    }
    if(file[0] == '\n'){
        mx_printerr("error: line 1 is not valid\n");
        exit(0);
    }

    //Amount of islands
    char *r1 = mx_strndup(file, mx_get_char_index(file, '\n'));
    int num = 0;
    if (checknum(r1) && mx_atoi(r1) <= __INT_MAX__) {
        num = mx_atoi(r1);
    } 
    else {
        mx_printerr("error: line 1 is not valid\n");
        exit(0);
    }    
    if (num < 1) {
        mx_printerr("error: invalid number of islands\n");
        exit(0);
    }

    //Splitted into lines with route and distance
    char **all = mx_strsplit(&file[mx_get_char_index(file, '\n')+1], '\n');

    int lines = 0;
    while (all[lines] != NULL) lines++;
    
    unsigned long route = 0;  
    char **islands = (char **)malloc((num*9)*2);
    for (int i = 0; i < num; i++) islands[i] = "NULL";
    for (int i = 0; i < lines; i++){
        char *from = mx_strndup(all[i], mx_get_char_index(all[i], '-'));
        for (int j = 0; j < num; j++) {
            if (mx_strcmp(islands[j], "NULL") == 0) {               
                islands[j] = mx_strdup(from);
                break;
            }
            if (mx_strcmp(islands[j], mx_strdup(from)) == 0) { 
                break;
            }
            if (j == num - 1) {
                mx_printerr("error: invalid number of islands\n");
                exit(0);
            }
        }               
        char *to = mx_strndup(all[i] + mx_get_char_index(all[i], '-') + 1, mx_get_char_index(all[i], ',') - mx_strlen(from) - 1);
        for (int j = 0; j < num; j++) {
            if (mx_strcmp(islands[j], "NULL") == 0) {
                islands[j] = mx_strdup(to);
                break;
            }
            if (mx_strcmp(islands[j], mx_strdup(to)) == 0) {
                break;
            }
            if (j == num - 1) {
                mx_printerr("error: invalid number of islands\n");
                exit(0);
            }
            
        }
        char *dist = mx_strdup(all[i] + mx_get_char_index(all[i], ',') + 1);
        
        if(checkline(from, to, dist) == false) {
            mx_printerr("error: line ");
            mx_printerr(mx_itoa(i+2)); 
            mx_printerr(" is not valid\n");
            exit(0);
        }
        route += mx_atoi(dist);        
    }
    checklast(file);

    for (int i = 0; i < num; i++) {
        if (mx_strcmp(islands[i], "NULL") == 0) {
            mx_printerr("error: invalid number of islands\n");
            exit(0);
        }
    }
    
    //Now I have sorted array of all islands
    //Second parse for fulfilling the adjancy matrix
    int **matrix = (int **)malloc((num*num)*sizeof(int));

    for (int i = 0; i < num; i++) {
        matrix[i] = (int *)malloc((num) * sizeof(int));
    }
    for (int i = 0; i < num; i++) {
        for(int j = 0; j < num; j++){
            matrix[i][j] = -1;
        }   
    }

    for (int i = 0; i < lines; i++){
        char *from = mx_strndup(all[i], mx_get_char_index(all[i], '-'));   
        char *to = mx_strndup(all[i] + mx_get_char_index(all[i], '-') + 1, mx_get_char_index(all[i], ',') - mx_strlen(from) - 1);
        char *dist = mx_strdup(all[i] + mx_get_char_index(all[i], ',') + 1);
        int x = -1, y = -1;
        for (int i = 0; islands[i]; i++){
            if(mx_strcmp(islands[i], from) == 0) x = i;
            if(mx_strcmp(islands[i], to) == 0) y = i;
        }
        if(matrix[x][y] == -1 && matrix[y][x] == -1){
            matrix[x][y] = mx_atoi(dist);
            matrix[y][x] = mx_atoi(dist);
        } 
        else {
            mx_printerr("error: duplicate bridges\n");
            exit(0);
        }
    }

    if(route > __INT_MAX__){
        mx_printerr("error: sum of bridges lengths is too big\n");
        exit(0);
    }

    //A*
    int size_path = 0;
    for(int i = 0; i < num; i++) {
        for(int j = i; j < num; j++) {
            if(i != j) {                
                Node **a = pathfinder(matrix, islands, i, j, num);
                for(int k = 0; a[k] != NULL; k++) {
                    size_path++;
                } 
            }
        }   
    }

    Node **res_paths = (Node **) malloc((size_path + 1) * sizeof(Node *));
    for(int j = 0; j < size_path; j++) res_paths[j] = NULL;
    
    size_path = 0;
    for(int i = 0; i < num; i++) {
        for(int j = i; j < num; j++) {
            if(i != j) {
                Node **a = pathfinder(matrix, islands, i, j, num);
                for(int j = 0; a[j] != NULL; j++) {
                    res_paths[size_path] = (Node*)malloc(sizeof(Node));
                    res_paths[size_path] = a[j];
                    size_path++;
                }
            }
        }   
    }   

    char **path = (char **)malloc((size_path*size_path)*sizeof(char));
    way_to_str(res_paths, path, size_path);

    int size_one_way = 0;
    char **res = (char **)malloc((__INT_MAX__/100)*sizeof(char));
    for(int j = 0; j < num; j++){
        for(int z = j; z < num; z++){
            for(int a = 0; a < size_path; a++){
                char **tmp_without_num = mx_strsplit(path[a], '|');
                char **tmp = mx_strsplit(tmp_without_num[0], ',');
                if(mx_strcmp(tmp[0], islands[j]) == 0 && mx_strcmp(tmp[amount_of_el(tmp)-1], islands[z]) == 0){
                    res[size_one_way] = mx_strdup(path[a]);
                    size_one_way++;
                }
            }
            if(size_one_way != 0){
                sort_path_all(res, islands, matrix, (unsigned long)size_one_way);
            }
            size_one_way = 0;
        }
    }

    /*for (int i = 0; i < num; i++) {
        for(int j = 0; j < num; j++){
            mx_printint(matrix[i][j]);
            mx_printchar('\t'); 
        }
        mx_printstr("\n");   
    }
    for (int i = 0; i < num; i++){
        mx_printstr(islands[i]);
        mx_printstr("\n=======\n");
    }*/
    
    //DON`T FORGET TO DO ALL ERROR HANDLINGS

    /*
    usage: ./pathfinder [filename]           +
    error: file [filename] does not exist    +
    error: file [filename] is empty          +
    error: line 1 is not valid               +
    error: line [line_number] is not valid   +
    error: invalid number of islands         +
    error: duplicate bridges                 +
    error: sum of bridges lengths is too big +
    */

}
