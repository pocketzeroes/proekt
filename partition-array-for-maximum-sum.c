int max(int a,int b){return a>b?a:b;}
int dp[502];
int maxSumAfterPartitioning(int*A, int Asz, int K){
    memset(dp, 0, sizeof(dp));
    for (int i = 0; i < Asz; i++) {
        int maxi = 0;
        for (int j = i; j < i + K&&j<Asz; j++) {
            maxi = max(maxi, A[j]);
            dp[j+1] = max(dp[j+1], dp[i] + (j - i + 1)*maxi);
        }
    }
    return dp[Asz];
}
