int maxLengthBetweenEqualCharacters(char*s){
    int res = -1;
    int i, j;
    int ssize=strlen(s);
    for(i = 0; s[i]; ++i){
        j = ssize - 1;
        while(s[j] != s[i])
            --j;
        res = fmax(res, j - i - 1);
    }
    return res;
}
