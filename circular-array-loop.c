bool circularArrayLoop(int* nums, int numsSize){
    int next(int i){
        return ((i + nums[i]) + numsSize) % numsSize;
    }
    for (int i = 0; i < numsSize; ++i){
        if (nums[i] == 0)
            continue;
        int slow = i, fast = i;
        while (nums[next( slow)] * nums[i] > 0 &&
               nums[next( fast)] * nums[i] > 0 &&
               nums[next( next( fast))] * nums[i] > 0) {
            slow = next(  slow);
            fast = next(  next( fast));
            if (slow == fast) {
                if (slow == next( slow)) 
                    break;
                return true;
            }
        }
        slow = i;
        int val = nums[i];
        while (nums[slow] * val > 0) {
            int tmp = next( slow);
            nums[slow] = 0;
            slow = tmp;
        }
    }
    return false;
}
