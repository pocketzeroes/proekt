#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)

int stoneGameVII(int*stones, int stonesSz){
    int n = stonesSz;
    int pref[n]; clr(pref);
    for(int i=0; i<n; i++)
        pref[i] = stones[i] + (i > 0 ? pref[i-1] : 0);
    int get(int l, int r){
        return pref[r] - (l > 0 ? pref[l-1] : 0);
    }
    int dp[n][n]; clr(dp);
    for(int i=n-1; i>=0; i--)
        for(int j=i; j<n; j++){
            if(i == j)
                dp[i][j] = 0;
            else if((j - i + 1) % 2 == n % 2)
                dp[i][j] = fmax(get(i, j - 1) + dp[i][j-1], get(i + 1, j) + dp[i+1][j]);
            else
                dp[i][j] = fmin(-get(i, j - 1) + dp[i][j-1], -get(i + 1, j) + dp[i+1][j]);
        }
    return dp[0][n-1];
}
