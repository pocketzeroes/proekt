bool find(char *s2, int start, int size, char ** wordDict, int wordDictSize) {
    char str[size+1];
    char *ret;
    strncpy(str, s2+start, size);
    str[size] = '\0';
    for (int i =0; i < wordDictSize; i++){
        if (strlen(str) == strlen(wordDict[i])){
            ret = strstr(wordDict[i], str);
            if (ret == NULL) {
                continue;
            } 
            else {
                if (strlen(ret)-strlen(wordDict[i]) == 0){
                    return true;
                }
            }
        }
    }
    return false;
}

bool wordBreak(char* s, char** wordDict, int wordDictSize) {
    if(wordDict == NULL) {
        return false;
    }
    if (s == NULL) {
        return true;
    }
    int len1 = strlen(s);
    int len2 = len1 +1;
    char s2[len2];
    s2[0] = '#';
    strncpy(s2+1, s, len1);
    bool possible[len2];
    possible[0] = true;
    for (int i = 1; i < len2; i++){
        for (int k = 0; k< i; k++){
            possible[i] = possible[k] && (find(s2, k+1, i-k, wordDict, wordDictSize));
            if(possible[i]) 
                break;
        }
    }
    return possible[len2-1];
}
