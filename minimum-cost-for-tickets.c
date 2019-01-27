int min(int a,int b){return a<b?a:b;}

void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}

int mincostTickets(int*days, int daysSz, int*costs, int costsSz){
    int n = daysSz;
    int dp[n+1];
    fill(dp, n+1, INT_MAX / 2);
    dp[0] = 0;
    for(int i = 1;i <= n;i++){
        dp[i] = dp[i-1] + costs[0];
        for(int j = i-1;j >= 0;j--){
            if(days[i-1] - days[j] + 1 <= 7)
                dp[i] = min(dp[i], dp[j] + costs[1]);
            if(days[i-1] - days[j] + 1 <= 30)
                dp[i] = min(dp[i], dp[j] + costs[2]);
        }
    }
    return dp[n];
}
