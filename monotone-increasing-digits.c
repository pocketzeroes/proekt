int monotoneIncreasingDigits(int n){
    int*a = calloc(n/2, sizeof(int));
    int aSz=0;
    for (int t = n; t; t /= 10)
        a[aSz++] = (t % 10);
    int m = aSz;
    int ret = 0, pre = 0;
    for (int i = 0; i < m; ++i) {
        for (int k = 9; k >= pre; --k) {
            int cur = ret;
            for (int j = i; j < m; ++j)
                cur = cur * 10 + k;
            if (cur <= n) {
                ret = ret * 10 + k;
                pre = k;
                break;
            }
        }
    }
    return ret;
}
