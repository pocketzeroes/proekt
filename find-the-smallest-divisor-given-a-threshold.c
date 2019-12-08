typedef long long ll;
enum{ INF = (int)1E9};
int smallestDivisor(int*nums, int numsSz, int threshold){
  int l = 1,
      r = INF;
  while(l <= r){
    int d = (l + r) / 2;
    ll sum = 0;
    for(int i=0; i<numsSz; i++)
      sum += (nums[i] + d - 1) / d;
    if(sum > threshold)
      l = d + 1;
    else
      r = d - 1;
  }
  return l;
}
