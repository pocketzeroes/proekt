int dp[1 << 12];
int amt[1 << 12];

int minimumTimeRequired(int*jobs, int jobsSz, int k){
    int n = jobsSz;
    for(int mask = 0; mask < (1<<n); mask++){
        dp[mask] =(int)1e9;
        amt[mask] = 0;
        for(int i = 0; i < n; i++) if(mask&(1<<i)) amt[mask] += jobs[i];
    }
    dp[0] = 0;
    while(k--){
      for(int mask = (1<<n)-1; mask >= 0; mask--){
        int other = mask;
        while(true){
          dp[mask] = fmin(dp[mask], fmax(dp[mask^other], amt[other]));
          if(other == 0)
            break;
          other = (other-1)&mask;
        }
      }
    }
    return dp[(1<<n)-1];
}
