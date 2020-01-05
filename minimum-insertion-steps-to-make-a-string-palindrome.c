#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)

int minInsertions(char*s){
    int n = strlen(s);
    int dp[n][n]; clr(dp);
    for(int i=0; i+1<n; ++i)
        dp[i][i+1] = s[i]!=s[i+1];
    for(int sz=3; sz<=n; ++sz){
        for(int i=0; i+sz<=n; ++i){
            int j = i + sz - 1;
            if(s[i] == s[j])
                dp[i][j] = dp[i + 1][j - 1];
            else
                dp[i][j] = 1 + fmin(dp[i + 1][j], dp[i][j - 1]);
        }
    }
    return dp[0][n-1];
}
