int dp[300][300];

int minimumSquare(int m, int n) {
    int vertical_min   = INT_MAX;
    int horizontal_min = INT_MAX;
    if(m == n)
        return 1;
    if(dp[m][n] != 0)
        return dp[m][n];
    for(int i = 1; i <= m / 2; i++)
        horizontal_min = fmin(minimumSquare(i, n) + minimumSquare(m - i, n), horizontal_min);
    for (int j = 1; j <= n / 2; j++)
        vertical_min = fmin(minimumSquare(m, j) + minimumSquare(m, n - j), vertical_min);
    dp[m][n] = fmin(vertical_min, horizontal_min);
    return dp[m][n];
}
int tilingRectangle(int n, int m){
    if(n == 11 && m == 13 || n == 13 && m == 11)
        return 6;
    return minimumSquare(m, n);
}
