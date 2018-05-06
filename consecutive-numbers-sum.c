bool ok(int d, int n){
    int u = n/d;
    int a = u-d+1;
    if(a % 2 != 0)
        return false;
    return a > 0;
}
int consecutiveNumbersSum(int n){
    n *= 2;
    int ct = 0;
    for(int d=1; (long long)d*d<=n; d++){
        if(n % d == 0){
            if(ok(d, n))
                ct++;
            if(d*d < n && ok(n/d, n))
                ct++;
        }
    }
    return ct;
}
