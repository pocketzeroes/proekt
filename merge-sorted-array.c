void merge(int* nums1, int m, int* nums2, int n){
    int i = m + n;
    while (m > 0 && n > 0) {
        if (nums1[m - 1] > nums2[n - 1]) {
            nums1[i - 1] = nums1[m - 1];
            --m;
        }
        else {
            nums1[i - 1] = nums2[n - 1];
            --n;
        }
        --i;
    }
    while (n > 0) {
        nums1[i - 1] = nums2[n - 1];
        --n;
        --i;
    }
}
