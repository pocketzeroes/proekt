void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
int*createTargetArray(int*nums, int numsSz, int*index, int indexSz, int*rsz){
    int n = numsSz, i, j, k, x;
    int*ans = calloc(n, sizeof(int)); fill(ans, n, -1);
    for(i=0; i<n; i++){
        x = index[i];
        for(j=i-1; j>=x; j--)
            ans[j + 1] = ans[j];
        ans[x] = nums[i];
        j = 0;
    }
   *rsz=n;
    return ans;
}
