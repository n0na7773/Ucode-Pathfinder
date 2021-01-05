#include "../inc/pathfinder.h"

void parse(const char *filename) {
    char *file = mx_file_to_str(filename); //I changed file_to_str function. There was filelen-1 to avoid abnormal symbols
    /*mx_printstr(file);
    mx_printchar('\n');
    mx_printint(mx_strlen(file));
    mx_printchar('\n');*/
    if(!file){
        mx_printerr("error: file ");
        mx_printerr(filename);
        mx_printerr(" is empty\n");
        exit(0);
    }

    //Amount of islands
    if(file[0] == '\n'){
        mx_printerr("error: line 1 is not valid\n");
        exit(0);
    }
    char *r1 = mx_strndup(file, mx_get_char_index(file, '\n'));
    int num = 0;
    if (checknum(r1) && mx_atoi(r1) <= __INT_MAX__) {
        num = mx_atoi(r1);
    } 
    else {
        mx_printerr("error: line 1 is not valid\n");
        exit(0);
    }
    
    //Splitted into lines with route and distance
    char **all = mx_strsplit(&file[mx_get_char_index(file, '\n')+1], '\n');

    int lines = 0;
    while (all[lines] != NULL) lines++;
    
    int invalid_island = 0;
    unsigned long route = 0;  
    char **islands = (char **)malloc((num*9)*2);
    for (int i = 0; i < num; i++) islands[i] = "NULL";
    for (int i = 0; i < lines; i++){
        invalid_island = 0;
        char *from = mx_strndup(all[i], mx_get_char_index(all[i], '-'));
        for (int j = 0; j < num; j++) {
            if (mx_strcmp(islands[j], "NULL") == 0) {               
                islands[j] = mx_strdup(from);
                break;
            }
            if (mx_strcmp(islands[j], mx_strdup(from)) == 0) { 
                break;
            }
            else if (mx_strcmp(islands[j], mx_strdup(from)) != 0) {
                invalid_island++;
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
            else if (mx_strcmp(islands[j], mx_strdup(to)) != 0) {
                invalid_island++;
            }
        }
        if (invalid_island == num*2) {
            mx_printerr("error: invalid number of islands\n");
            exit(0);
        } 
        char *dist = mx_strdup(all[i] + mx_get_char_index(all[i], ',') + 1);

        if(correct_line(from, to, dist) == false) {
            mx_printerr("error: line ");
            mx_printerr(mx_itoa(i+2)); 
            mx_printerr(" is not valid\n");
            exit(0);
        }
        route += mx_atoi(dist);        
    }
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
        char *dist = mx_strndup(all[i] + mx_get_char_index(all[i], ',') + 1, mx_get_char_index(all[i], '\n'));
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

    //Check for too long distance
    if(route > __INT_MAX__){
        mx_printerr("error: sum of bridges lengths is too big\n");
        exit(0);
    }

    for (int i = 0; i < num; i++) {
        for(int j = 0; j < num; j++){
            mx_printint(matrix[i][j]);
            mx_printchar('\t'); 
        }
        mx_printstr("\n");   
    }
    for (int i = 0; i < num; i++){
        mx_printstr(islands[i]);
        mx_printstr("\n=======\n");
    }
    
    //DON`T FORGET TO DO ALL ERROR HANDLINGS
    //DON`T FORGET TO DO ALL ERROR HANDLINGS
    //DON`T FORGET TO DO ALL ERROR HANDLINGS
    //DON`T FORGET TO DO ALL ERROR HANDLINGS
    //DON`T FORGET TO DO ALL ERROR HANDLINGS
    //DON`T FORGET TO DO ALL ERROR HANDLINGS
    /*
    usage: ./pathfinder [filename]           +
    error: file [filename] does not exist    - have no idea
    error: file [filename] is empty          +
    error: line 1 is not valid               +
    error: line [line_number] is not valid   +
    error: invalid number of islands         +
    error: duplicate bridges                 +
    error: sum of bridges lengths is too big +
    */

}
