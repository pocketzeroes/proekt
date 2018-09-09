typedef long long ll;
int numPermsDISequence(char*S){
    int n = strlen(S);
    int a[n+1]; memset(a, 0, sizeof(a));
    int p   = 0;
    int len = 0;
    for(int i=0; i<n; i++){
        if(S[i] == 'D')
            len++;
        else{
            a[p++] = len+1;
            len = 0;
        }
    }
    a[p++] = len+1;
    enum{mod = 1000000007};
    ll C[401][401];
    for(int i=0; i<=400; i++){
        C[i][0] = 1;
        for(int j=1; j<=i; j++){
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
            if (C[i][j] >= mod)
                C[i][j] -= mod;
        }
    }
//  a = Arrays.copyOf(a, p);
    ll dp[p+1]; memset(dp, 0, sizeof(dp));
    dp[0] = 1;
    int all = 0;
    for(int i=1; i<=p; i++){
        all += a[i-1];
        int s = 0;
        for(int j=i-1, sgn=1; j>=0; j--, sgn=-sgn){
            s += a[j];
            dp[i] += dp[j] * C[all][s] * sgn;
            dp[i] %= mod;
        }
        if(dp[i] < 0)
            dp[i] += mod;
    }
    return(int)dp[p];
}
