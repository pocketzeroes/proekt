void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
int*f;
int dfs(int*a, int x, int n){
    if(x == n)
        return 0;
    if(f[x] != INT_MIN)
        return f[x];
    int sum = 0;
    for(int i = x; i <= x + 2 && i < n; ++i){
        sum += a[i];
        f[x] = fmax(f[x], sum - dfs(a, i + 1, n));
    }
    return f[x];
}
char*stoneGameIII(int*a, int aSz){
    int n = aSz;
    f = calloc(n, sizeof(int)); fill(f, n, INT_MIN);
    int ans = dfs(a, 0, n);
    free(f);
    if(ans == 0)
        return "Tie";
    else
        return(ans > 0 ? "Alice" : "Bob");
}
