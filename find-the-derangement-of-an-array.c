int findDerangement(int n) {
    const long long MOD = 1e9+7;
    long long a=0,b=1,c;
    for(int i=2;i<=n;i++) {
        c=i*(b+a) % MOD;
        a=b;
        b=c;
    }
    return (int)a;
}
