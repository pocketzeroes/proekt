int minMoves(int*nums, int numsSz, int limit){
    int n = numsSz;
    int imos[200005]={0};
    for(int i=0; i<n/2; i++){
        int L = nums[i],
            R = nums[n-1-i];
        imos[2] += 2;
        int min = fmin(L, R) + 1;
        imos[min]--;
        int max = fmax(L, R) + limit;
        imos[max+1]++;
        imos[L+R]--;
        imos[L+R+1]++;
    }
    for(int i = 0; i <= 200003; i++){
        imos[i+1] += imos[i];
    }
    int min = 999999999;
    for(int i = 2; i <= 200003; i++){
        min = fmin(min, imos[i]);
    }
    return min;
}
