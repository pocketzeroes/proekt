inline int min(int a,int b){return a<b?a:b;}
inline int max(int a,int b){return a>b?a:b;}

int findMaxLength(int*a,int numsSz) {
  int res = 0, n = numsSz; 
  int idx[2*n+1];
  memset(idx,-1,sizeof(idx));
  for (int i = 0, d = 0; i < n; res = max(res, i++ -idx[d+n]))
    if ((a[i]? ++d : --d) && idx[d+n]<0) idx[d+n] = i;
  return res;
}
