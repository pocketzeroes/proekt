enum{ MOD =(int) 1e9 + 7};
typedef long long ll;

ll accumulate(int*arr, int sz){
  ll sum=0;
  for(int i=0; i<sz; i++)
    sum += arr[i];
  return sum;
}
int kConcatenationMaxSum(int*arr, int arrSz, int k){
    int n = arrSz;
    ll best = 0;
    ll full_sum = accumulate(arr, arrSz);
    ll sum = 0;
    for(int i = 0; i < n; i++){
        sum += arr[i];
        if (sum < 0)
            sum = 0;
        else if (sum > best)
            best = sum;
    }
    ll max_prefix = 0,
       max_suffix = 0;
    sum = 0;
    for(int i = 0; i < n; i++){
        sum += arr[i];
        max_prefix = fmaxl(max_prefix, sum);
    }
    sum = 0;
    for (int i = n - 1; i >= 0; i--) {
        sum += arr[i];
        max_suffix = fmaxl(max_suffix, sum);
    }
    if (k > 1) {
        best = fmaxl(best, max_suffix + max_prefix);
        best = fmaxl(best, max_suffix + max_prefix + (k - 2) * full_sum);
    }
    return best % MOD;
}
