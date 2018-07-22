int max_element(int*arr, int sz){
  int maxe=arr[0];
  for(int i=1;i<sz;i++)
    if(arr[i]>maxe)
      maxe=arr[i];
  return maxe;
}
typedef long long ll;
int minEatingSpeed(int*a, int aSz, int H){
    int n    = aSz;
    int low  = 1, 
        high = max_element(a, aSz);
    while(low != high){
        int mid = (low + high) / 2;
        ll sum = 0;
        for(int i = 0; i < n; ++i)
            sum += (a[i] + mid - 1) / mid;
        if (sum > H)
            low = mid + 1;
        else
            high = mid;
    }
    return high;
}
