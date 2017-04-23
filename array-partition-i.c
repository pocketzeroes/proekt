int cmp (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}
int arrayPairSum(int* nums, int numsSize) {
    qsort(nums,numsSize,sizeof(int),cmp);
    int n = numsSize;
    int s = 0;
    for(int i = 0;i < n;i+=2){
        s += nums[i];
    }
    return s;
}
