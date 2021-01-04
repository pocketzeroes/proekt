int maximumUnits(int**b, int bSz, int*b0sz, int truckSz){
    int f[1010];
    int i, j, res = 0, c;
    for(i = 1; i <= 1000; ++i)
      f[i] = 0;
    for(i = 0; i < bSz; ++i)
      f[b[i][1]] += b[i][0];
    j = 0;
    for(i = 1000; i >= 1; --i){
        c = fmin(truckSz - j, f[i]);
        res += c * i;
        j += c;
    }
    return res;
}
