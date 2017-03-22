inline int min(int a,int b){return a<b?a:b;}
inline int max(int a,int b){return a>b?a:b;}

int nthUglyNumber(int n) {
    int uglies[n];
    uglies[0] = 1;
    int f2   = 2, f3   = 3, f5   = 5;
    int idx2 = 0, idx3 = 0, idx5 = 0;
    for (int i = 1; i < n; ++i) {
        int min_val = min(min(f2, f3), f5);
        uglies[i] = min_val;
        if (min_val == f2) {
            f2 = 2 * uglies[++idx2];
        }
        if (min_val == f3) {
            f3 = 3 * uglies[++idx3];
        }
        if (min_val == f5) {
            f5 = 5 * uglies[++idx5];
        }
    }
    return uglies[n - 1];
}
