#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)

bool winnerSquareGame(int n){
    int dp[n+1]; clr(dp);
    for(int i=1; i<=n; ++i){
        for(int j=1; j*j<=i; ++j)
            dp[i]|=!dp[i-j*j];
    }
    return dp[n];
}
