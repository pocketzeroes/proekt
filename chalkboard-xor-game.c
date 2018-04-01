bool xorGame(int*nums, int numsSz){
    int x = 0;
    for(int i=0;i<numsSz;i++){int v = nums[i];
      x ^= v;
    }
    return x == 0 || numsSz % 2 == 0;
}
