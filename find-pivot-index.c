int pivotIndex(int*a, int aSz){
    int n = aSz;
    int s[n + 3]; memset(s,0,sizeof(s));
    int d[n + 3]; memset(d,0,sizeof(d));
    for (int i = 1; i <= n; ++i) s[i] = s[i - 1] + a[i - 1];
    for (int i = n; i >= 1; --i) d[i] = d[i + 1] + a[i - 1];
    for (int i = 1; i <= n; ++i) if (s[i] == d[i]) return i - 1;
    return -1;
}
