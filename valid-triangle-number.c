int cmp (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}
int triangleNumber(int*a, int aSz){
  int i,j,k,n,left,right,mid,ans,sum;
  ans=0;
  qsort(a, aSz, sizeof(int), cmp);
  n = aSz;
  for (i=0;i<n;i++){
    for (j=i+1;j<n;j++){
      sum=a[i]+a[j];
      left=j;right=n;
      while (right-left>1){
        mid=(left+right)/2;
        if (a[mid]>=sum) 
          right=mid;
        else 
          left=mid;
      }
      ans+=left-j;
    }
  }
  return ans;
}
