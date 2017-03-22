inline int min(int a,int b){return a<b?a:b;}
inline int max(int a,int b){return a>b?a:b;}

int cmp(const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}
int findPairs(int* nums, int numsSize, int k) {
    int ans = 0;
    qsort(nums,numsSize,sizeof(int),cmp);
    for (int i = 0, j = 0; i < numsSize; i++) {
        for (j = max(j, i + 1); j < numsSize && (long) nums[j] - nums[i] < k; j++) ;
        if (j < numsSize && (long) nums[j] - nums[i] == k) ans++;
        while (i + 1 < numsSize && nums[i] == nums[i + 1]) i++;
    }
    return ans;
}
