typedef long long ll;

int numSubarrayProductLessThanK(int*nums, int numsSz, int k){
  int i,j,n;
  int ans,now;
  ll p;
  n = numsSz;
  p=1;now=0;
  ans=0;
  for (i=0;i<n;i++)
  {
    while ((p<k)&&(now<n))
    {
      p*=nums[now];
      now++;
    }
    if (now-i-1>=0)
      ans+=now-i-1;
    if (p<k) 
      ans++;
    if (now>i)
    {
      p/=nums[i];
    }
    else
    {
      now++;
    }
  }
  return ans;
}
