int cmp (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}
int minMoves(int*nums,int numsSz){
    qsort(nums,numsSz,sizeof(int),cmp);
    int count = 0;
    for (int i = numsSz - 1; i > 0; i--)
        count += nums[i] - nums[0];
    return count;
}
