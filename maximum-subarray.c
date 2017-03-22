#define MAX(a,b) (((a)>(b))?(a):(b))

int maxSubArray(int* nums, int numsSize){
    int max_current = nums[0];
    int max_global  = nums[0];
    for( int i=1;i< numsSize;i++ ){
        max_current = MAX(max_current + nums[i], nums[i]);
        max_global  = MAX(max_current, max_global);
    }
    return max_global;
}

