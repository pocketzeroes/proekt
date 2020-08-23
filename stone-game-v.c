#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
int dp[505][505],sum[505];

int f(int l,int r){
    if(dp[l][r]!=-1)
        return dp[l][r];
    if(l == r)
        return 0;
    int ret=0;
    for(int k=l;k<r;++k) {
        int tmp = 0;
        if(sum[r]-sum[k] > sum[k]-sum[l-1]) {
            tmp = sum[k]-sum[l-1]+f(l,k);
        }
        else if(sum[r]-sum[k] < sum[k]-sum[l-1]) {
            tmp = sum[r]-sum[k]+f(k+1,r);
        }
        else {
            tmp = fmax(sum[r]-sum[k]+f(k+1,r), sum[k]-sum[l-1]+f(l,k));
        }
        ret=fmax(ret,tmp);
    }
    return dp[l][r]=ret;
}
int stoneGameV(int*a, int aSz){
    memset(dp,-1,sizeof(dp));
    clr(sum);
    int n=aSz;
    for(int i=1;i<=n;++i)
        sum[i]=sum[i-1]+a[i-1];
    return f(1,n);
}
