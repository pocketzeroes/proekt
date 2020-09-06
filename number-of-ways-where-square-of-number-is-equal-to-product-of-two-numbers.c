typedef long long ll;
int cmp(const void * a, const void * b){ return ( *(int*)a - *(int*)b ); }
ll upper_bound(ll*a, ll n, ll x){
    ll l = 0;
    ll h = n;
    while(l < h){
        ll mid = (l + h) / 2;
        if(x >= a[mid])
            l = mid + 1;
        else
            h = mid;
    }
    return l;
}
ll lower_bound(ll*a, ll n, ll x){
  ll l = 0;
  ll h = n;
  while (l < h) {
    ll mid = (l + h) / 2;
    if (x <= a[mid]) 
      h = mid;
    else
      l = mid + 1;
  }
  return l;
}

#define FOR(i, begin, end) for(int i=(begin),i##_end_=(end);i<i##_end_;i++)
#define REP(i, n) FOR(i,0,n)


int solve(int*nums1, int nums1Sz, int*nums2, int nums2Sz){
    ll*tgt = calloc(nums1Sz, sizeof(ll));
    for(int z=0; z<nums1Sz; z++){int x=nums1[z];
        tgt[z] = 1LL*x*x;
    }
    int ret = 0;
    REP(i, nums2Sz)REP(j, i)
    {
        ll x = 1LL * nums2[i] * nums2[j];
        ret += upper_bound(tgt, nums1Sz, x) - lower_bound(tgt, nums1Sz, x);
    }
    return ret;
}
int numTriplets(int*nums1, int nums1Sz, int*nums2, int nums2Sz){
    qsort(nums1, nums1Sz, sizeof(int), cmp);
    qsort(nums2, nums2Sz, sizeof(int), cmp);
    return solve(nums1, nums1Sz, nums2, nums2Sz)+
           solve(nums2, nums2Sz, nums1, nums1Sz);
}
