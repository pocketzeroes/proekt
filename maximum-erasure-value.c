#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
int freq[10005];
int maximumUniqueSubarray(int*nums, int numsSz){
  clr(freq);
  int n = numsSz;
  int lhs = 0;
  int ret = 0;
  int curr = 0;
  for(int i = 0; i < numsSz; i++){
    while(freq[nums[i]] > 0){
      curr -= nums[lhs];
      freq[nums[lhs++]]--;
    }
    curr += nums[i];
    freq[nums[i]]++;
    ret = fmax(ret, curr);
  }
  return ret;
}
