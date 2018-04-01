double soupServings(int N){
    if(N == 0)
        return 0.5;
    if(N >= 10000)
        return 1.;
    int n = (N+24)/25;
    double dp[n+1]; memset(dp, 0, sizeof(dp));
    dp[n] = 1;
    double P = 0;
    for(int i = 0;i <= n/2+1;i++){
        for(int j = 0;j <= n;j++){
            for(int k = 1;k <= 4;k++){
                int b = 2*n-4*(i+1)-(j-k);
                if(j-k <= 0){
                    if(b <= 0){
                        P += dp[j]/4/2;
                    }
                    else{
                        P += dp[j]/4;
                    }
                }
                else if(b <= 0){
                    ;
                }
                else{
                    dp[j-k] += dp[j]/4;
                }
            }
            dp[j] = 0;
        }
    }
    return P;
}
