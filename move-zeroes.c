void moveZeroes(int*nums,int numsSz){
    int j = 0;
    for (int i = 0; i < numsSz; i++) {
        if (nums[i] != 0) 
            nums[j++] = nums[i];
    }
    for (;j < numsSz; j++) 
        nums[j] = 0;
}
