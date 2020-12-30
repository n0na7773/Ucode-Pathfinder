#include "../inc/libmx.h"

char **mx_strsplit(char const *s, char c){
    if(!s) return 0;
	int count_words = mx_count_words(s, c);
	char **res = (char**)malloc((count_words + 1) * sizeof(char *));
	int j = 0;
	for (int i = 0; i < count_words; ++i) {
		int word_length = 0;
		while (s[j] != c && s[j]) {
			j++;
			word_length++;
		}
		if(word_length == 0 && j < mx_strlen(s)){
			j++;
			i--;
		} else {
			char *tmp_word = mx_strndup(&s[j - word_length], word_length);
			res[i] = tmp_word;
		}
	} 
	res[count_words] = NULL;
	return res;
}
