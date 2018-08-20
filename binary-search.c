int search(int* nums, int numsSize, int target) {
    for (int l = 0, h = numsSize - 1, m = (l + h) / 2; l <= h; m = (l + h) / 2)
        if (nums[m] == target)
            return m;
        else if (nums[m] > target)
            h = m - 1;
        else
            l = m + 1;
    return -1;
}
