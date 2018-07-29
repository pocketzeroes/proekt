int upper_bound(int*a, int n, int x) {
    int l = 0;
    int h = n;
    while (l < h) {
        int mid = (l + h) / 2;
        if (x >= a[mid])
            l = mid + 1;
        else
            h = mid;
    }
    return l;
}
typedef struct {
}Solution;
Solution*ptr;
int*dp;
int dpSz;
int sum = 0;

Solution*solutionCreate(int*w, int wSz){
    dpSz=wSz;
    dp=calloc(dpSz, sizeof(int));
    for(int i=0;i<wSz;i++){int e = w[i];
        sum += e;
        dp[i] = sum;
    }
    return ptr;
}
int solutionPickIndex(Solution*obj) {
    int r = rand() % sum;
    int it = upper_bound(dp, dpSz, r);
    return it;
}
void solutionFree(Solution*obj){
    free(dp);dp=NULL;
    dpSz=0;
    sum=0;
}
