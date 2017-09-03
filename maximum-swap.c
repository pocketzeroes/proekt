char tmp[10];
void swap(char*nums, int i, int j){
  char t  = nums[i];
  nums[i] = nums[j];
  nums[j] = t;
}
int maximumSwap(int num){
  int i, j, n;
  int ret, ans;
  ans = num;
  sprintf(tmp, "%d", num);
  n = strlen(tmp);
  for(i=0; i<n; i++)
    for(j=i+1; j<n; j++){
      swap(tmp, i, j);
      ret = atoi(tmp);
      if(ret > ans)
        ans = ret;
      swap(tmp, i, j);
    }
  return ans;
}
