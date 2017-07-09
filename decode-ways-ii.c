int dp[100010];
int MOD = 1000000007;
void ck(int*x, int y) {
   *x += y;
    if (*x >= MOD) {
        *x -= MOD;
    }
}
int numDecodings(char*s){
    int n = strlen(s);
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 1; j <= 9; j++) {
            if (s[i] == '*' || s[i] == j + '0') {
                ck(&dp[i + 1], dp[i]);
            }
        }
        if (i + 1 == n) {
            continue;
        }
        for (int j = 1; j <= 2; j++) {
            for (int k = 0; k <= 9; k++) {
                if (j * 10 + k > 26) {
                    continue;
                }
                if (s[i] == '*' || s[i] == j + '0') {
                    if ((s[i + 1] == '*' && k != 0) || s[i + 1] == k + '0') {
                        ck(&dp[i + 2], dp[i]);
                    }
                }
            }
        }
    }
    return dp[n];
}



