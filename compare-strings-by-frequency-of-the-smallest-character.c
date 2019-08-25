int f(char*s){
    int f[26];memset(f,0,sizeof(f));
    for(int i=0;s[i];i++){char c = s[i];
        f[c-'a']++;
    }
    for(int i=0; i<26; i++)
        if(f[i] > 0)
            return f[i];
    return 0;
}
int*numSmallerByFrequency(char**queries, int queriesSz, char**words, int wordsSz, int*rsz){
    int n = queriesSz;
    int m = wordsSz;
    int ws[m];
    for(int i=0; i<m; i++)
        ws[i] = f(words[i]);
    int*ret = calloc(n, sizeof(int));
    for(int i=0; i<n; i++){
        int u = f(queries[i]);
        for(int j=0; j<m; j++)
            if(u < ws[j])
                ret[i]++;
    }
   *rsz=n;
    return ret;
}
