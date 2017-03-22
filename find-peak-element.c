int findPeakElement(int* nums,int numsSz) {
    int left = 0, right = numsSz - 1;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if ((mid == 0 || nums[mid - 1] < nums[mid]) &&
           (mid + 1 == numsSz || nums[mid] > nums[mid + 1])) {
            return mid;
        } else if (!(mid == 0 || nums[mid - 1] < nums[mid])) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return left;
}
