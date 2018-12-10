bool isAlienSorted(char**words, int wordsSz, char*order){
    int a[256], i, j;
    memset(a, 0, sizeof(a));
    for(i=0; order[i]; i++)
        a[order[i]] = i;
    for(i=0; i<wordsSz; i++)
        for(j=0; words[i][j]; j++)
            words[i][j] = a[words[i][j]]+'a';
    for(i=0; i<wordsSz-1; i++)
        if(strcmp(words[i], words[i+1])>0)
            return 0;
    return 1;
}
