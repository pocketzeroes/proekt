double new21Game(int N, int K, int W) {
    double*dp = calloc(N+3, sizeof(double));
    dp[0] =  1;
    dp[1] = -1;
    double val = 0;
    for(int i = 0;i < K;i++){
        val += dp[i];
        if(i+1 <= N)
            dp[i+1] += val / W;
        if(i+W+1 <= N)
            dp[i+W+1] -= val / W;
    }
    double ret = 0;
    for(int i = K;i <= N;i++){
        val += dp[i];
        ret += val;
    }
    free(dp);
    return ret;
}
