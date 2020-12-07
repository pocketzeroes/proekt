int cmp (const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}
int maxOperations(int*nums, int numsSz, int k){
    int n=numsSz,i,j,ans=0;
    qsort(nums, numsSz, sizeof(int), cmp);
    for(i=0,j=n-1;i<j;)
      if(nums[i]+nums[j]<k)
        i++;
    else if(nums[i]+nums[j]>k)
      j--;
    else{
        ans++;
        i++;
        j--;
    }
    return ans;
}
