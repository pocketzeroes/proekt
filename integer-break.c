int integerBreak(int n) {
    if (n < 4) 
        return n - 1;
    int res = 0;
    if (n % 3 == 0)      res = pow(3, n / 3);
    else if (n % 3 == 2) res = pow(3, n / 3) * 2;
    else                 res = pow(3, n / 3 - 1) * 4;
    return res;
}
