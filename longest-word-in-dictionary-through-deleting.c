bool checkIfMatch(char* s, char* word);

char* findLongestWord(char* s, char** d, int dSize) {

    int max_len = 0;
    char* max_word = NULL;
    int d_len;
    int i;

    for(i=0;i<dSize;i++){

        if( checkIfMatch(s,d[i]) ){
            d_len = strlen(d[i]);
            if(d_len > max_len || (d_len == max_len && strcmp(d[i], max_word) < 0) ){
                max_len = d_len;
                max_word = d[i];
            }
        }
    }
    return (max_word == NULL) ? "" : max_word;
}

bool checkIfMatch(char* s, char* word) {
    while(*s != '\0'){
        if(*s == *word){
            word++;
        }
        s++;
    }
    return (*word == '\0');
}
