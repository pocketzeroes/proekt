typedef long long LL;

LL s[30010];
LL max(LL a,LL b){return a>b?a:b;}
double findMaxAverage(int*a, int aSz, int k) {
    s[0] = 0;
    int n = aSz;
    LL mx = INT_MIN;
    for (int i = 1; i <= n; ++i) {
        s[i] = s[i-1] + a[i-1];
        if (i >= k) {
            mx = max(mx, s[i] - s[i - k]);
        }
    }
    return 1.0 * mx /  k;
}
