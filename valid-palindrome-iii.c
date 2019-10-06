#define dfill(arr, sz1, sz2, val)do{     \
  for(int i=0; i<sz1; i++)               \
    for(int j=0; j<sz2; j++)             \
      arr[i][j] = val;                   \
}while(0)

int**newmat(int x, int y){
  int**rv = calloc(x, sizeof(int*));
  for(int i=0;i<x;i++)
    rv[i] = calloc(y, sizeof(int));
  return rv;
}

int calc(int l, int r, int**dp, char*s){
    if (l >= r)
        return 0;
#define res dp[l][r]
    if (res != -1)
        return res;
    res = r - l + 1;
    if(s[l] == s[r])
        res = fmin(res, calc(l + 1, r - 1, dp, s));
    res = fmin(res, 1 + calc(l + 1, r, dp, s));
    res = fmin(res, 1 + calc(l, r - 1, dp, s));
    return res;
    #undef res
}
bool isValidPalindrome(char*s, int k){
    int n = strlen(s);
    int**dp=newmat(n, n); dfill(dp, n,n, -1);
    return calc(0, n - 1, dp, s) <= k;
}
