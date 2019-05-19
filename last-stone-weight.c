int cmp(const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}
void swap(int*nums, int i, int j) {
   int t   = nums[i];
   nums[i] = nums[j];
   nums[j] = t;
}
int lastStoneWeight(int*stones, int stonesSz){
    int ret = 0, n = stonesSz;
    qsort(stones, stonesSz, sizeof(int), cmp);
    while (n > 1){
        stones[n - 2] = stones[n - 1] - stones[n - 2];
        n--;
        stonesSz--;
        if (stones[n - 1] == 0){
            stonesSz--;
            n--;
            continue;
        }
        for (int i = n - 2; i >= 0; i--){
            if (stones[i] <= stones[i + 1])
                break;
            swap(stones, i, i+1);
        }
    }
    if (!n)
        return 0;
    return stones[0];
}
