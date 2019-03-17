int max_element(int*arr, int sz){
  int maxe=arr[0];
  for(int i=1;i<sz;i++)
    if(arr[i]>maxe)
      maxe=arr[i];
  return maxe;
}
int shipWithinDays(int*weights, int weightsSz, int D){
  int n = weightsSz;
  int lo = max_element(weights, weightsSz);
  int hi = 100000000;
  while (lo < hi) {
    int m = (lo + hi) >> 1;
    int cur = 0;
    int need = 0;
    for (int i = 0; i < n; ++i) {
      if (cur + weights[i] > m) {
        cur = 0;
        ++need;
      }
      cur += weights[i];
      assert(cur <= m);
    }
    ++need;
    if (need > D)
      lo = m + 1;
    else
      hi = m;
  }
  return lo;
}
