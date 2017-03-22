
int* searchRange(int* nums, int numsSize, int target, int* returnSize) {
    int lower_bound() {
        int left = 0;
        int right = numsSize;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] >= target) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        return left;
    }
    int upper_bound() {
        int left = 0;
        int right = numsSize;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] > target) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        return left;
    }
    int begin = lower_bound(nums, target);
    int end   = upper_bound(nums, target);
   *returnSize=2;
    int*arr=malloc(2*sizeof(int));
    arr[0]=-1;
    arr[1]=-1;
    if (begin < numsSize && nums[begin] == target) {
        arr[0]=begin;
        arr[1]= end - 1;
    }
    return arr;
}
