typedef long long ll;
int findLengthOfLCIS(int*nums, int numsSz){
  int i,j,k,n;
  ll now,ans,cnt;
  n = numsSz;
  now=(1LL<<60);
  cnt=0;
  ans=0;
  for (i=0;i<n;i++){
    if (nums[i]<=now){
      if (cnt>ans) 
        ans=cnt;
      now=nums[i];
      cnt=1;
    }
    else{
      cnt++;
      now=nums[i];
    }
  }
  if(cnt>ans) 
    ans=cnt;
  return ans;
}
