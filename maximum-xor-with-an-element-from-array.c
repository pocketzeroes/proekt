int cmp (const void * a, const void * b){
  return ( *(int*)a - *(int*)b );
}
int lower_bound(int*a, int n, int x){
  int l = 0;
  int h = n;
  while (l < h){
    int mid = (l + h) / 2;
    if (x <= a[mid]) 
      h = mid;
    else
      l = mid + 1;
  }
  return l;
}
int upper_bound(int*a, int n, int x){
  int l = 0;
  int h = n;
  while (l < h) {
    int mid = (l + h) / 2;
    if (x >= a[mid])
      l = mid + 1;
    else
      h = mid;
  }
  return l;
}

int N;
int A[100000];

int solve(int a, int b, int x, int bt){
  int res = -1;
  int k;
  int z;
  if(a >= b)
    return res;
  while(bt >= 0 && (A[a] & 1<<bt) == (A[b-1] & 1<<bt))
    bt--;
  if(bt == -1)
    return x ^ A[a];
  z = (A[a] & ( ((1<<30)-1) ^ ((1<<bt) - 1) )) + (1<<bt);
  k = lower_bound(A, b, z);
  if(x & 1<<bt)
    res = solve(a, k, x, bt - 1);
  else
    res = solve(k, b, x, bt - 1);
  return res;
}
int*maximizeXor(int*nums, int numsSz, int**queries, int queriesSz, int*queries0sz, int*rsz){
  int i, k;
  int*res = calloc(queriesSz, sizeof(int));
  N = numsSz;
  for(i=0; i<N; i++){
    A[i] = nums[i];
  }
  qsort(A, N, sizeof(int), cmp);
  for(i=0; i<queriesSz; i++){
    k = upper_bound(A, N, queries[i][1]);
    res[i]=solve(0, k, queries[i][0], 30);
  }
 *rsz=queriesSz;
  return res;
}
