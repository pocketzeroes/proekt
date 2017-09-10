typedef long long ll;
ll d[3000][2];
int findNumberOfLIS(int*nums, int numsSz){
  int i,j,k,n,ma;
  ll ans;
  n = numsSz;
  ma=0;
  for(i=0; i < numsSz; i++){
    d[i][0]=1;
    d[i][1]=1;
    for (j=0;j<i;j++)
      if (nums[j]<nums[i]){
        if (d[j][0]+1>d[i][0]){
          d[i][0]=d[j][0]+1;
          d[i][1]=d[j][1];
        }
        else if (d[j][0]+1==d[i][0]){
          d[i][1]+=d[j][1];
        }
      }
    if (d[i][0]>ma) 
      ma=d[i][0];
  }
  ans=0;
  for (i=0;i<n;i++)
    if (d[i][0]==ma) 
      ans+=d[i][1];
  return ans;
}
