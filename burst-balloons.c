inline int min(int a,int b){return a<b?a:b;}
inline int max(int a,int b){return a>b?a:b;}

int maxCoins(int* nums, int numsSize){
    int*coins=malloc((numsSize+2)*sizeof(int));
    int coinsSz=0;
    coins[coinsSz++]=1;
    for(int i=0;i<numsSize;i++){
        int n=nums[i];
        if (n > 0) 
            coins[coinsSz++]=n;
    }
    coins[coinsSz++]=1;
    int max_coins[coinsSz][coinsSz];
    memset(max_coins,0,sizeof(max_coins));
    for (int k = 2; k < coinsSz; ++k) 
        for (int left = 0; left < coinsSz - k; ++left) 
            for (int i = left + 1, right = left + k; i < right; ++i) 
                max_coins[left][right] = max(max_coins[left][right], coins[left] * coins[i] * coins[right] + max_coins[left][i] + max_coins[i][right]);
    return max_coins[0][coinsSz - 1];
}
