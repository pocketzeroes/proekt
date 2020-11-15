int cnt[100000 + 10];
int a[102], n;
int dp[52][1<<10];
int sum[1<<10];

bool canDistribute(int*nums, int numsSz, int*quantity, int quantitySz){
    memset(cnt,0,sizeof(cnt));
    n=0;
    for(int z=0;z<numsSz;z++){int x=nums[z];
      cnt[x]++;
    }
    for(int i=1;i<=100000;i++)
        if(cnt[i])
          a[++n]=cnt[i];
    int m=quantitySz;
    memset(dp,0,sizeof(dp));
    dp[0][0]=1;
    for(int i=0;i<1<<m;i++){
        sum[i]=0;
        for(int j=0;j<m;j++)
          if(i>>j&1)
            sum[i]+=quantity[j]; 
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<1<<m;j++){
            if(dp[i][j]){
                for(int k=0;k<1<<m;k++){
                    if((j&k)==0 && sum[k]<=a[i+1]){
                        dp[i+1][j|k] = 1;
                    }
                }
            }
        }
    }
    bool ok=dp[n][(1<<m)-1];
    return ok;
}
