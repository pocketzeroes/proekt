void chmax(int*a, int b){
    if(*a < b)
      *a = b;
}
void chmin(int*a, int b){
    if(*a > b)
      *a = b;
}
int maxAbsoluteSum(int*nums, int numsSz){
    int n = numsSz, ans = 0, mn = 0, mx = 0;
    for(int i=(0);i<(n);++i){
      mn += nums[i];
      chmax(&ans, abs(mn));
      chmin(&mn, 0);
      mx += nums[i];
      chmax(&ans, abs(mx));
      chmax(&mx, 0);
    }
    return ans;
}
