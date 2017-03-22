int findMin(int* nums,int numsSz) {
    int left = 0, right = numsSz - 1;
    while (left < right && nums[left] >= nums[right]) {
        int mid = left + (right - left) / 2;
        if (nums[mid] < nums[left]) {
            right = mid;
        }
        else {
            left = mid + 1;
        }
    }
    return nums[left];
}
