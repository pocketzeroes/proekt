#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
int cmp(const void * a, const void * b){ return ( *(int*)a - *(int*)b );}
int minAbsDifference(int*nums, int numsSz, int goal){
    int n = numsSz;
    int half = n / 2;
    int ls = half, rs = n - half;
    int lsum[1<<ls]; clr(lsum);
    for(int i = 1; i < (1 << ls); i++){
        for(int j = 0; j < ls; j++){
            if((i & (1 << j)) == 0)
              continue;
            lsum[i] = lsum[i-(1<<j)] + nums[j];
            break;
        }
    }
    int rsum[1<<rs]; clr(rsum);
    for(int i = 1; i < (1 << rs); i++){
        for(int j = 0; j < rs; j++){
            if((i & (1 << j)) == 0)
              continue;
            rsum[i] = rsum[i-(1<<j)] + nums[ls+j];
            break;
        }
    }
    qsort(lsum, 1<<ls, sizeof(int), cmp);
    qsort(rsum, 1<<rs, sizeof(int), cmp);
    int ret = INT_MAX;
    for(int z=0; z<(1<<ls); z++){int x=lsum[z];
        ret = fmin(ret, abs(goal - x));
    }
    for(int z=0; z<(1<<rs); z++){int x = rsum[z];
        ret = fmin(ret, abs(goal - x));
    }
    int rsumSz=1<<rs;
    int lsumSz=1<<ls;
    int i = 0, j = rsumSz - 1;
    while(i < lsumSz && j >= 0){
        int s = lsum[i] + rsum[j];
        ret = fmin(ret, abs(goal - s));
        if(s > goal)
            j--;
        else
            i++;
    }
    return ret;
}
