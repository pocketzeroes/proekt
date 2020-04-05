int accumulate(int*arr, int sz){
  int sum=0;
  for(int i=0; i<sz; i++)
    sum += arr[i];
  return sum;
}
int cmpr(const void*b, const void*a){
   return ( *(int*)a - *(int*)b );
}
int*minSubsequence(int*nums, int numsSz, int*rsz){
    int sum = accumulate(nums, numsSz);
    qsort(nums, numsSz, sizeof(int), cmpr);//rev
    int t = 0;
    int*ans = calloc(numsSz, sizeof(int));
    int i;
    for(i=0;i<numsSz;){int num = nums[i];
        ans[i++] = num;
        t += num;
        if(t * 2 > sum)
            break;
    }
   *rsz=i;
    return ans;
}
