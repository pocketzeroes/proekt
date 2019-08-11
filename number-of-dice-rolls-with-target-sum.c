typedef long long ll;
ll dp[31][1010];
ll mo=1000000007;

int numRollsToTarget(int d, int f, int target) {
    memset(dp,0,sizeof(dp));
    dp[0][0]=1;
    int i,j,x;
    for(i=0;i<(d);i++) {
        for(j=0;j<(901);j++)
            for(x=1;x<=f;x++){
                dp[i+1][j+x]+=dp[i][j];
                dp[i+1][j+x]%=mo;
            }
    }
    return dp[d][target];
}
