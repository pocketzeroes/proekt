char* getPermutation(int n, int k) {
    int i,j,f=1;
    char s[n+1];
    memset(s,'0',n);
    for(i=1;i<=n;i++){
        f*=i;
        s[i-1]+=i;
    }
    for(i=0,k--;i<n;i++){
        f/=n-i;
        j=i+k/f; 
        char c=s[j];
        for(;j>i;j--)
            s[j]=s[j-1];
        k%=f;
        s[i]=c;
    }
    s[i]='\0';
    return strdup(s);
}

