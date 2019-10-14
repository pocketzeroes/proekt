#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
int dieSimulator(int n, int*rollMax, int rollMaxSz){
    int dp[5005][6][20]; clr(dp);
    dp[0][0][0]=1;
    int mod =(int)1e9+7;
    for(int i=1; i<=n; i++){
        for(int k=0; k<6; k++){
            for(int j=2; j<=rollMax[k]; j++)
                dp[i][k][j]=dp[i-1][k][j-1];
            int sum=0;
            for(int j=0; j<6; j++){
                if(j==k&&i!=1)
                    continue;
                for(int l=0;l<20;l++){
                    sum += dp[i-1][j][l];
                    sum %= mod;
                }
            }
            dp[i][k][1] = sum;
        }
    }
    int ans = 0;
    for(int i=0; i<6; i++){
        for(int j=0; j<20; j++){
            ans += dp[n][i][j];  
            ans %= mod;
        }
    }
    return ans;
}
