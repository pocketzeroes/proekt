char*smallestGoodBase(char*n){
    char*end;
    char*ptr;
    unsigned long long num =strtoull(n,&end,10);
    unsigned long long res;
    for(int l = log(num) / log(2); l >= 2; --l) {
        unsigned long long b = pow(num, 1.0 / l), sum = 0, curr = 1;
        for (int i = 0; i <= l; ++i, curr *= b) {
            sum += curr;
        }
        if (sum == num) {
            res=b;
            goto end;
        }
    }
    res=num - 1;
end:
    asprintf(&ptr,"%lld",res);
    return ptr;
}
       