int cmp (const void*a, const void*b){ return(*(int*)a-*(int*)b);}
typedef long long ll;
enum{ MOD =(int)1e9+7};
ll pow2[100011];

int numSubseq(int*nums, int numsSz, int target){
  if(pow2[0] == 0){
    pow2[0] = 1;
    for (int i=1; i<100011; i++) {
      pow2[i] = pow2[i-1] * 2;
      if (pow2[i] >= MOD) 
        pow2[i] -= MOD;
    }
  }
  qsort(nums, numsSz, sizeof(int), cmp);
  int r = numsSz - 1u;
  ll ans = 0;
  for(int i=0, i_len=(numsSz); i<i_len; ++i) {
     while (r >= 0 && nums[i] + nums[r] > target) 
       r--;
     if (r < i) 
       break;
     ans += pow2[r-i];
     if (ans >= MOD) 
       ans -= MOD;
  }
  return ans;
}
