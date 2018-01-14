bool is_prime(int x) {
    if (x==1)
        return false;
    for (int i=2; i<=sqrt(x); ++i)
        if (x%i==0)
            return false;
    return true;
}
int countPrimeSetBits(int L, int R){
    int ans = 0;
    for (int x=L; x<=R; ++x) {
        int count = 0;
        int t = x;
        while (t) {
            count += t&1;
            t >>= 1;
        }
        if (is_prime(count)) ++ans;
    }
    return ans;
}
