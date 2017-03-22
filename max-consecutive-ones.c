#define MAX(a,b) (((a)>(b))?(a):(b))
int findMaxConsecutiveOnes(int* nums, int numsSize) {
    int result = 0, local_max = 0;
    for (int i=0;i<numsSize;i++) {
        int n=nums[i];
        local_max = n ? local_max + 1 : 0;
        result = MAX(result, local_max);
    }
    return result;
}
