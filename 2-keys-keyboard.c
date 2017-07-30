int min(int a,int b){return a<b?a:b;}

int minSteps(int n) {
    int res[1010];
    for (int i = 0; i < 1010; ++i) res[i] = INT_MAX;
    res[1] = 0;
    for (int i = 1; i <= 1000; ++i) {
        for (int j = i * 2, k = 2; j <= 1000; j += i, ++k) {
            res[j] = min(res[j], res[i] + k);
        }
    }
    return res[n];
}
