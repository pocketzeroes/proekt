int f[38];

int tribonacci(int n){
    memset(f, 0, sizeof(f));
    f[0] = 0;
    f[1] = 1;
    f[2] = 1;
    for (int i = 3; i < 38; ++i) {
        f[i] = f[i - 1] + f[i - 2] + f[i - 3];
    }
    return f[n];
}
