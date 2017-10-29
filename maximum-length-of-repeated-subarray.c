int max(int a,int b){return a>b?a:b;}

int findLength(int*A, int Alength, int*B, int Blength){
    int n = Alength, m = Blength;
    int dp[n+1][m+1]; memset(dp,0,sizeof(dp));
    int ret = 0;
    for(int i = 0;i < n;i++){
        for(int j = 0;j < m;j++){
            if(A[i] == B[j]){
                dp[i+1][j+1] = dp[i][j] + 1;
            }
            else{
                dp[i+1][j+1] = 0;
            }
            ret = max(ret, dp[i+1][j+1]);
        }
    }
    return ret;
}
