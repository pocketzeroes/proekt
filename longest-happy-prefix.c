char*longestPrefix(char*s){
    int n = strlen(s);
    int*v = calloc(n, sizeof(int));
    int len=0;
    for(int i=1; i<n; ++i) {
        if(s[i]==s[len]) {
            len++;
            v[i]=len;
        }
        else {
            if(len)
                len=v[len-1], --i;
            else
                v[i]=0;
        }
    }
    s[v[n-1]]='\0';
    free(v);
    return strdup(s);
}
