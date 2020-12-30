#include "../inc/pathfinder.h"

void parse(const char *filename) {
    char *file = mx_file_to_str(filename);

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
    lines--;

    char **islands = (char **)malloc((num*9)*2);
    for (int i = 0; i < lines; i++){
        char *from = mx_strndup(all[i], mx_get_char_index(all[i], '-'));
        for (int j = 0; j < num; j++) {
            if (islands[j] == NULL) {
                islands[j] = mx_strdup(from);
                break;
            }
            if (mx_strcmp(islands[j],mx_strdup(from)) == 0) {
                break;
            }
        }        
        char *to = mx_strndup(all[i] + mx_get_char_index(all[i], '-') + 1, mx_get_char_index(all[i], ',') - mx_strlen(from) - 1);
        for (int j = 0; j < num; j++) {
            if (islands[j] == NULL) {
                islands[j] = mx_strdup(to);
                break;
            }
            if (mx_strcmp(islands[j],mx_strdup(to)) == 0) {
                break;
            }
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

    for (int i = 0; i < num; i++) {
        for(int j = 0; j < num; j++){
            mx_printint(matrix[i][j]);
            mx_printchar('\t'); 
        }

        mx_printstr("\n");   
    }
    /*for (int i = 0; i < num; i++){
        mx_printstr(islands[i]);
        mx_printstr("\n=======\n");
    }*/
    
    //DON`T FORGET TO DO ALL ERROR HANDLINGS
    //DON`T FORGET TO DO ALL ERROR HANDLINGS
    //DON`T FORGET TO DO ALL ERROR HANDLINGS
    //DON`T FORGET TO DO ALL ERROR HANDLINGS
    //DON`T FORGET TO DO ALL ERROR HANDLINGS
    //DON`T FORGET TO DO ALL ERROR HANDLINGS


}
