#include <stdlib.h>
int cmpfunc (const void * a, const void * b){ return ( *(int*)a - *(int*)b ); }
int threeSumClosest(int* nums, int numsSize, int target) {
    int ans      = INT_MAX;
    int min_diff = INT_MAX;
    qsort(nums, numsSize, sizeof(int),&cmpfunc);
    for (int i = 0; i < numsSize - 2; ++i) {
        if (i == 0 || nums[i] != nums[i - 1]) {
            int j = i + 1;
            int k = numsSize - 1;
            while (j < k) {
                int sum = nums[i] + nums[j] + nums[k];
                if (sum > target) {  
                    --k;
                } else if (sum < target) {  
                    ++j;
                } else {
                    return target;
                }
                if (abs(sum - target) < min_diff) {
                    min_diff = abs(sum - target);
                    ans = sum;
                }
            }
        }
    }
    return ans;
}
