int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

int maxChunksToSorted(int*a, int aSz){
  int n = aSz;
  int d [n+1]; memset(d , 0, sizeof(d ));
  int mx[n+1]; memset(mx, 0, sizeof(mx));
  for(int i = 0; i < n; ++i){
    mx[i + 1] = max(mx[i], a[i]);
  }
  for(int i = 0; i < n; ++i) {
    int mn = a[i];
    for(int j = i; j >= 0; --j) {
      if(mn >= mx[j]) {
        d[i + 1] = max(d[i + 1], 1 + d[j]);
      }
      if(j > 0) {
        mn = min(mn, a[j - 1]);
      }
    }
  }
  return d[n];
}
