enum{ SIZE =(int) 1e6+10};
int nxt[SIZE][26];

int numMatchingSubseq(char*SS, char**words, int wordsSz){
    int n = strlen(SS);
    for (int i = 0; i < (26); ++i)
        nxt[n][i] = n;
    for(int i=n-1; i>=0; i--){
        for (int j = 0; j < (26); ++j)
            nxt[i][j]=nxt[i+1][j];
        nxt[i][SS[i]-'a']=i;
    }
    int an=0;
    for(int z=0; z<wordsSz; z++){char*s=words[z];
        int s_size=strlen(s);
        int err=0,now=0;
        for(int i = 0; i < s_size; ++i){
            if(nxt[now][s[i]-'a']==n){
                err=1;
                break;
            }
            now = nxt[now][s[i]-'a']+1;
        }
        if(!err)
            an++;
    }
    return an;
}
