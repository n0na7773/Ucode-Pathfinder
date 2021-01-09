#include "../inc/libmx.h"

char *mx_file_to_str(const char *file){
    if(!file) return NULL;
	
	int file1 = open(file, O_RDONLY);
	int file2 = open(file, O_RDONLY);

	int filelen = 0;
	char buff;

	if(file1 < 0){
		close(file1);
		return NULL;
	}

   	while(read(file2, &buff, 1)) {
        filelen++;
	}

	char *str = mx_strnew(filelen);
	
	read(file1, str, filelen);
	close(file1);
	return str;
}
