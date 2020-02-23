#define dfill(arr, sz1, sz2, val)do{     \
  for(int i=0; i<sz1; i++)               \
    for(int j=0; j<sz2; j++)             \
      arr[i][j] = val;                   \
}while(0)
enum{ mod = (int)1e9 + 7};

int countOrders(int n){
    int dp[n+1][n+1]; dfill(dp, n+1, n+1, -1);
int calc(int x, int y){
    if (x < 0 || y < 0) 
        return 0;
    if (x == 0 && y == 0) 
        return 1;
#define res dp[x][y]
    if (res != -1) 
        return res;
    res = x * 1ll * calc(x - 1, y) % mod;
    res += y * 1ll * calc(x + 1, y - 1) % mod;
    if (res >= mod) 
        res -= mod;
    return res;
}
    return calc(0, n);
}
