  int missingNumber(int*nums,int numsSize) {
    int num = 0;
    for (int i = 0; i < numsSize; ++i) {
      num ^= nums[i] ^ (i + 1);
    }
    return num;
  }
