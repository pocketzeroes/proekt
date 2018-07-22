#define max(a,b) (((a)>(b))?(a):(b))
int lower_bound(int*a, int n, int x) {
    int l = 0;
    int h = n;
    while (l < h) {
        int mid = (l + h) / 2;
        if (x <= a[mid]) 
            h = mid;
        else
            l = mid + 1;
    }
    return l;
}
enum{ MAXN = 1005};
int dp[MAXN][MAXN];

int lenLongestFibSubseq(int*A, int Asz){
    int n = Asz, ans = 0;
    memset(dp,0,sizeof(dp));
    for (int i = n-1; i>=0; i--) {
      for(int j=(i+1);j<(n);j++) {
        dp[i][j] = 2;
        int v = A[i] + A[j];
        int k = lower_bound(A, Asz, v);
        if(k < n && A[k] == v)
          dp[i][j] = max(dp[i][j], dp[j][k] + 1);
        ans = max(ans, dp[i][j]);
      }
    }
    return ans <= 2 ? 0 : ans;
}
