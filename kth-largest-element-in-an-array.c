void swap(int*nums, int i, int j) {
   int t   = nums[i];
   nums[i] = nums[j];
   nums[j] = t;
}
int gNsz;
int paritionSort (int* nums, int startIndex, int endIndex){
    if (startIndex < 0 || startIndex > endIndex || startIndex > gNsz-1 || endIndex > gNsz-1){
        return -1;
    }
    int pivotIndex = rand() % (endIndex-startIndex+1) + startIndex;
    int currIndex = startIndex;
    swap(nums,startIndex, pivotIndex);
    pivotIndex = startIndex;
    for (int i=startIndex+1; i<=endIndex; i++){
        if (nums[i] > nums[pivotIndex]){
            swap(nums, ++currIndex, i);
        }
    }
    swap(nums, currIndex, pivotIndex);
    return currIndex;
}
int findKthLargest(int* nums,int numsSz, int k) {
    gNsz=numsSz;
    if (k > numsSz || k < 1){
        return -1;
    }
    int resultIndex=0, left=0, right=numsSz-1;
    while (left < right){
        resultIndex = paritionSort(nums, left, right);
        if (resultIndex == k-1){
            return nums[resultIndex];
        }
        else if (resultIndex > k-1){
            right = resultIndex-1;
        }
        else { 
            left = resultIndex+1;
        }
    }
    return nums[left];
}
