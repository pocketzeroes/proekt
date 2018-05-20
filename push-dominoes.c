char*pushDominoes(char*dominoes){
    char*s = dominoes;
    int n = strlen(s);
    char pre = 0;
    int prepos = -1;
    for(int i = 0;i < n;i++){
        if(s[i] == 'L'){
            if(pre == 'R'){
                int K = (prepos+i+1)/2-prepos;
                for(int j = 0;j < K;j++){
                    s[prepos+j] = 'R';
                    s[i-j] = 'L';
                }
            }
            else{
                for(int j = prepos+1;j <= i;j++){
                    s[j] = 'L';
                }
            }
            prepos = i;
            pre = 'L';
        }
        else if(s[i] == 'R'){
            if(pre == 'R'){
                for(int j = prepos;j < i;j++){
                    s[j] = 'R';
                }
            }
            pre = 'R';
            prepos = i;
        }
    }
    if(pre == 'R'){
        for(int i = prepos;i < n;i++)
            s[i] = 'R';
    }
    return strdup(s);
}
