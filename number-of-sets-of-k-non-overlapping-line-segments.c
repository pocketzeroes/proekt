#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
int numberOfSets(int n, int k){
    enum{mod = 1000000007};
    int f[n][k+1]; clr(f);
    int g[n][k+1]; clr(g);
    f[0][0] = 1;
    g[0][0] = 1;
    for(int i=1; i<n; i++){
        for(int j=0; j<=k; j++){
            f[i][j] = f[i - 1][j];
            if(j > 0)
                f[i][j] = (f[i][j] + g[i - 1][j - 1]) % mod;
            
            g[i][j] = (g[i - 1][j] + f[i][j]) % mod;
        }
    }
    return f[n - 1][k];
}
