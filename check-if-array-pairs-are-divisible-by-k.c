
int moddw_L(int a, int b){
  a %= b;
  if(a < 0)
    a += b;
  return a;
}

int cnt[100000];

bool canArrange(int*arr, int arrSz, int k){
  int i;
  for(i=0; i<k; i++)
    cnt[i] = 0;
  for(i=0; i<arrSz; i++)
    cnt[(moddw_L(arr[i], k))]++;
  if(cnt[0] % 2)
    return false;
  for(i=1; i<k; i++)
    if(cnt[i] != cnt[k-i])
      return false;
  return true;
}
