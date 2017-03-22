int* nextGreaterElement(int* findNums, int findNumsSize, int* nums, int numsSize, int* returnSize) {
    int* returnArray = NULL;
    int* numsHash = NULL;
    *returnSize = findNumsSize;
    if(findNums != NULL && findNumsSize != 0 &&
       nums != NULL && numsSize != 0) {
        returnArray = malloc((*returnSize) * sizeof(int));
        if(returnArray == NULL) {
            err(-1, "nextGreaterElement: line 17: malloc: out of space!");
        }
        int max = 0;
        for(int i = 0; i < numsSize; i++) {
            if(max < nums[i]) {
                max = nums[i];
            }
        }
        numsHash = malloc((max+1) * sizeof(int));
        if(numsHash == NULL) {
            err(-1, "nextGreaterElement: line 31: malloc: out of space!");
        }
        for(int i = 0; i < numsSize-1; i++) {
            numsHash[nums[i]] = -1;
            for(int j = i+1; j < numsSize; j++) {
                if(nums[j] > nums[i]) {
                    numsHash[nums[i]] = nums[j];
                    break;
                }
            }
        }
        numsHash[nums[numsSize-1]] = -1;
        for(int i = 0; i < findNumsSize; i++) {
            returnArray[i] = numsHash[findNums[i]];
        }
    }
    return returnArray;
}
