int minOperations(int n) {
    int avg = n;
    int ret = 0;
    for(int i = 1; i <= 2*n+1; i += 2)
        ret += fmax(0, avg - i);
    return ret;
}
