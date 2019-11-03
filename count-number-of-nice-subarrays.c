
int upper_bound(int*a, int n, int x) {
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
int lower_bound(int*a, int n, int x) {
  int l = 0;
  int h = n;
  while (l < h) {
    int mid = (l + h) / 2;
    if (x <= a[mid]) 
      h = mid;
    else
      l = mid + 1;
  }
  return l;
}
//////////////////////////////

int pre[50005];

int numberOfSubarrays(int*a, int aSz, int k){
    memset(pre,0,sizeof pre);
    int n=aSz;
    for(int i=1;i<=n;++i) {
        if(a[i-1] & 1)
            pre[i]=pre[i-1]+1;
        else
            pre[i]=pre[i-1];
    }
    int ans=0;
    for(int i=1;i<=n;++i){
        ans += upper_bound(pre+1, n, pre[i-1]+k) -
               lower_bound(pre+1, n, pre[i-1]+k);
    }
    return ans;
}
