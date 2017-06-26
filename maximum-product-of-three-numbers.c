inline int min(int a,int b){return a<b?a:b;}
inline int max(int a,int b){return a>b?a:b;}

int cmp (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}

int maximumProduct(int*nums, int numsSz){
    qsort(nums, numsSz, sizeof(int), cmp);
    int n = numsSz;
    int s = nums[n-1] * nums[n-2] * nums[n-3];
    s = max(s, nums[n-1] * nums[n-2] * nums[0]);
    s = max(s, nums[n-1] * nums[1] * nums[0]);
    s = max(s, nums[2] * nums[1] * nums[0]);
    return s;
}

