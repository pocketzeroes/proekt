
int Digit_L(int n, int res[10]){
  int sz = 0;
  while(n){
    res[sz++] = n % 10;
    n /= 10;
  }
  return sz;
}
int invDigit_L(int sz, int d[10]){
  int res = 0;
  int i;
  for(i=(sz)-1;i>=(0);i--)
    res = 10 * res + d[i];
  return res;
}
void chmin(int*a, int b){
  if(*a>b)
    *a=b;
}
void chmax(int*a, int b){
  if(*a<b)
     *a=b;
}

int maxDiff(int num){
  int x;
  int mn = 1073709056;
  int mx = -1;
  int v;
  int sz;
  int d[10];
  int pre[10];
  sz =Digit_L(num, d);
  for(x=(0);x<(10);x++){
    int y;
    for(y=(0);y<(10);y++){
      int i;
      for(i=(0);i<(sz);i++){
        pre[i] = d[i];
      }
      for(i=(0);i<(sz);i++){
        if(d[i]==x){
          d[i] = y;
        }
      }
      if(d[sz-1]){
        v = invDigit_L(sz, d);
        chmax(&mx, v);
        chmin(&mn, v);
      }
      for(i=(0);i<(sz);i++){
        d[i] = pre[i];
      }
    }
  }
  return mx - mn;
}
