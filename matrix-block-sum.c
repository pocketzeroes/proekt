#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
int**newmat(int x, int y){
  int**rv = calloc(x, sizeof(int*));
  for(int i=0; i<x; i++)
    rv[i] = calloc(y, sizeof(int));
  return rv;
}
void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}

int**matrixBlockSum(int**a, int aSz, int*a0sz, int K, int*rsz, int**csz){
    int n = aSz;
    int m = a0sz[0];
    int s[n+1][m+1]; clr(s);
    for (int i = 1; i <= n; ++ i)
        for (int j = 1; j <= m; ++ j)
            s[i][j] = s[i-1][j]+s[i][j-1]-s[i-1][j-1]+a[i-1][j-1];
    int get(int x1, int x2, int y1, int y2){
        return s[x2][y2]-s[x2][y1-1]-s[x1-1][y2]+s[x1-1][y1-1];
    }
    int**ret = newmat(n, m);
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j){
            int x1 = fmax(1, i-K), x2 = fmin(n, i+K);
            int y1 = fmax(1, j-K), y2 = fmin(m, j+K);
            ret[i-1][j-1] = get(x1, x2, y1, y2);
        }
    int*cols=calloc(n, sizeof(int)); fill(cols, n, m);
   *csz=cols;
   *rsz=n;
    return ret;
}
