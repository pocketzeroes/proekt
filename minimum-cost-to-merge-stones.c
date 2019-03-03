int min(int a,int b){return a<b?a:b;}

int mergeStones(int*a, int aSz, int K){
    int n = aSz;
    if(n % (K-1) != 1 % (K-1))
        return -1;
    int cum[n+1]; memset(cum,0,sizeof(cum));
    for(int i = 0; i < n; i++)
        cum[i+1] = cum[i] + a[i];
    int dp[n][n]; memset(dp, 0, sizeof(dp));
    for(int len = K; len <= n; len++){
        for(int i = 0;i+len-1 < n;i++){
            int j = i+len-1;
            int cost = INT_MAX;
            int ulen = (len-1)/(K-1)*(K-1)+1;
            if(ulen % (K-1) == 1 %(K-1))
                ulen -= K-1;
            int s = len % (K-1) == 1 % (K-1) ? len-(K-1) : len;
            for(int k = i+1;k <= j;k++){
                if((k-i-1)/(K-1) + (j-k+1-1)/(K-1) == (s-1)/(K-1)){
                    int c = 0;
                    if(i <= k-1)
                        c += dp[i][k-1];
                    if(k <= j)
                        c += dp[k][j];
                    cost = min(cost, c);
                }
            }
            if(len % (K-1) == 1 % (K-1))
                cost += cum[j+1] - cum[i];
            dp[i][j] = cost;
        }
    }
    return dp[0][n-1];
}
