int max(int a,int b){return a>b?a:b;}

int longestArithSeqLength(int*A, int Asz){
    int n = Asz;
    int ret = 0;
    int dpt[10001]={0};
    int dp[n]; memset(dp, 0, sizeof(dp));
    for(int d = -10000; d <= 10000; d++){
        for(int i=n-1; i>=0; i--){
            int ne = A[i] + d;
            if(0 <= ne && ne <= 10000)
                dp[i] = dpt[ne] + 1;
            else
                dp[i] = 1;
            dpt[A[i]] = max(dpt[A[i]], dp[i]);
            ret = max(ret, dp[i]);
        }
        for(int i = n-1;i >= 0;i--)
            dpt[A[i]] = 0;
    }
    return ret;
}
