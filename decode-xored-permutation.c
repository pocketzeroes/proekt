int*decode(int*a, int aSz, int*rsz){
  int n = aSz + 1;
  int sum = 0;
  for (int i = 1; i <= n; ++i) sum ^= i;
  for (int i = n - 2; i >= 0; i -= 2) sum ^= a[i];
  int*ret=calloc(n,sizeof(int));
  ret[0] = sum;
  for(int i = 0; i < n - 1; ++i) ret[i + 1] = ret[i] ^ a[i];
 *rsz=n;
  return ret;
}
