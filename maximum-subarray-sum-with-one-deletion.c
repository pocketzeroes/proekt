enum{ MAXN = 100100};
int psl[MAXN];
int psh[MAXN];

int maximumSum(int*arr, int arrSz){
    int N = arrSz;
    for (int i = 0; i < N; i++){
        psl[i+1] = fmax (0, psl[i] + arr[i]);
        psh[i+1] = fmax (0, psh[i] + arr[N-1-i]);
    }
    int ans = -1e9;
    for (int i = 0; i < N; i++){
        ans = fmax (ans, psl[i] + psh[N-1-i]);
        ans = fmax (ans, psl[i] + psh[N-1-i] + arr[i]);
    }
    int nans = -1e9;
    for (int i = 0; i < N; i++)
        nans = fmax (nans, arr[i]);
    if (nans < 0) 
        return nans;
    return ans;
}
