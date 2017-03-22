bool find132pattern(int* nums,int numslength) {
    if(numslength<3) return false;
    int start = 0;
    while(start<numslength-1){
        while(start<numslength-1 && nums[start]>=nums[start+1]) start++;
        int m = start+1;
        while(m<numslength-1 && nums[m]<=nums[m+1]) m++;
        int j = m+1;
        while(j<numslength){
            if(nums[j]>nums[start] && nums[j]<nums[m]) return true;
            j++;
        }
        start = m+1;
    }
    return false;
}
