int numberOfArrays(char*s, int k){
    enum{MOD=(int)1e9+7};
    int n = strlen(s);
    int*f=(int*)malloc(sizeof(int)*(n+1));
    memset(f,0,sizeof(int)*(n+1));
    f[0]=1;
    for(int i=0;i<n;++i) if(s[i]!='0'){
        long long u=0;
        for(int j=i;j<n;++j){
            u=u*10+s[j]-48;
            if(u>k)
                break;
            f[j+1] += f[i];
            f[j+1] %= MOD;
        }
    }
    int ans=f[n];
    free(f);
    return ans;
}
