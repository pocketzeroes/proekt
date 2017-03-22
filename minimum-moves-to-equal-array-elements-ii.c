int cmp (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}
int minMoves2(int* nums, int numsSize) {
      qsort(nums, numsSize,sizeof(int),cmp); 
      int n = numsSize, res = 0;
      for (int i = 0; i < n/2; ++i) res += (nums[n-1-i]-nums[i]);
      return res;
    }