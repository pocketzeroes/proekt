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

int**restoreMatrix(int*r, int rSz, int*c, int cSz, int*rsz, int**csz){
    int n = rSz, m = cSz;
    int i = 0, j = 0;
    int**a = newmat(n, m);
    for(;;){
        int x = fmin(r[i], c[j]);
        a[i][j] += x;
        r[i] -= x;
        c[j] -= x;
        if(r[i] == 0) i++;
        if(c[j] == 0) j++;
        if(i >= n || j >= m) break;
    }
    int*cols=calloc(n, sizeof(int));
    fill(cols, n, m);
   *csz=cols;
   *rsz=n;
    return a;
}
