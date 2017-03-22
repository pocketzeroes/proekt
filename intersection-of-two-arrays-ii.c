int partition(int* a, int l, int r) {
    int x = a[l];
    while(l < r) {
        while(l < r && x < a[r]) --r;
        if(l < r) {
            a[l] = a[r];
            ++l;
        }
        while(l < r && x > a[l]) ++l;
        if(l < r) {
            a[r] = a[l];
            --r;
        }
    }
    a[l] = x;
    return l;
}

void quick_sort(int* a, int l, int r) {
    if(l < r) {
        int m = partition(a, l, r);
        quick_sort(a, l, m-1);
        quick_sort(a, m+1, r);
    }
}

int* intersect(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize) {
    quick_sort(nums1, 0, nums1Size-1);
    quick_sort(nums2, 0, nums2Size-1);
    int maxsize = nums1Size > nums2Size ? nums1Size : nums2Size;
    int i = 0, j = 0;
    *returnSize = 0;
    int* result = (int*)malloc(maxsize*sizeof(int));
    while(i < nums1Size && j < nums2Size) {
        if(nums1[i] < nums2[j]) ++i;
        else if(nums1[i] > nums2[j]) ++j;
        else {
            result[(*returnSize)++] = nums1[i];
            ++i;
            ++j;
        }
    }
    return result;
}

