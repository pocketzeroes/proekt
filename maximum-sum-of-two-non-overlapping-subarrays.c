int max(int a,int b){return a>b?a:b;}

int maxSumTwoNoOverlap(int*a, int aSz, int L, int M){
  int n = aSz;
  int cum[n+1]; memset(cum, 0, sizeof(cum));
  for(int i = 0; i < n; i++)
    cum[i+1] = cum[i] + a[i];
  int ret = INT_MIN / 2;
  {
    int mx = INT_MIN / 2;
    for(int i = 0; i <= n; i++){
      if(i >= L+M){
        mx = max(mx, cum[i-M] - cum[i-M-L]);
        ret = max(ret, mx + cum[i] - cum[i-M]);
      }
    }
  }
  {
    int mx = INT_MIN / 2;
    for(int i = 0; i <= n; i++){
      if(i >= L+M){
        mx = max(mx, cum[i-L] - cum[i-L-M]);
        ret = max(ret, mx + cum[i] - cum[i-L]);
      }
    }
  }
  return ret;
}
