enum{ N = 50010};


int f[N][3];

int maxSumDivThree(int*nums, int numsSz){
    int n = numsSz;
    f[0][1] = f[0][2] = -123456789;
    for (int i = 1; i <= n; ++i) {
        int val = nums[i - 1] % 3;
        for (int j = 0; j < 3; ++j)
            f[i][j] = f[i - 1][j];
        for (int j = 0; j < 3; ++j) {
            int k = (j + val) % 3;
            f[i][k] = fmax(f[i][k], f[i - 1][j] + nums[i - 1]);
        }
    }
    return f[n][0];
}
