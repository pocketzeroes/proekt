int n;
bool adj[1000][1000];
int dp[1000];

int cdp(int u){
    if(!dp[u]){
        for(int i=0; i<n; ++i)
            if(adj[u][i])
            dp[u] = fmax(dp[u], cdp(i));
        ++dp[u];
    }
    return dp[u];
}
int maxJumps(int*arr, int arrSz, int d){
    n=arrSz;
    for(int i=0; i<n; ++i) {
        memset(adj[i], 0, n);
        int mx=0;
        for(int j=i-1; ~j; --j) {
            mx = fmax(mx, arr[j]);
            if(j<i-d)
                adj[i][j]=0;
            else {
                adj[i][j] = arr[i]>mx;
            }
        }
        mx=0;
        for(int j=i+1; j<n; ++j) {
            mx = fmax(mx, arr[j]);
            if(j>i+d)
                adj[i][j]=0;
            else {
                adj[i][j]=arr[i]>mx;
            }
        }
    }
    memset(dp, 0, 4*n);
    int ans=0;
    for(int i=0; i<n; ++i)
        ans = fmax(cdp(i), ans);
    return ans;
}
