signed char can_Cross(int*stones, int sz, int ind, int jumpsize,char**memo){
    if (memo[ind][jumpsize] >= 0)
        return memo[ind][jumpsize];
    for (int i = ind + 1; i < sz; i++){
        int gap = stones[i] - stones[ind];
        if (gap >= jumpsize - 1 && gap <= jumpsize + 1){
            if (can_Cross(stones,sz, i, gap, memo)==1){
                memo[ind][gap] = 1;
                return 1;
            }
        }
    }
    memo[ind][jumpsize] = (ind == sz - 1) ? 1 : 0;
    return memo[ind][jumpsize];
}
bool canCross(int*stones, int stonesSz){
    unsigned char*memo[stonesSz];
    for (int i=0;i<stonesSz;i++){
        memo[i]=malloc(stonesSz);
        memset(memo[i],-1,stonesSz);
    }
    return can_Cross(stones,stonesSz, 0, 0, memo) == 1;
}
