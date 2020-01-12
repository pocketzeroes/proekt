int dp[300][26][26];

int cal(int a, int b) {
    int ax = a / 6;
    int ay = a % 6;
    int bx = b / 6;
    int by = b % 6;
    return abs(ax - bx) + abs( ay - by);
}

int minimumDistance(char*s) {
    int ssize=strlen(s);
    for(int i=0; s[i]; i++) {
        int t = s[i] - 'A';
        for (int j = 0; j < 26; j++)
            for (int k = 0; k < 26; k++)
                dp[i + 1][j][k] = INT_MAX / 3;
        for (int j = 0; j < 26; j++)
            for (int k = 0; k < 26; k++){
                dp[i + 1][j][t] = fmin(dp[i + 1][j][t], dp[i][j][k] + cal(k, t));
                dp[i + 1][t][k] = fmin(dp[i + 1][t][k], dp[i][j][k] + cal(j, t));
            }
    }
    int ans = INT_MAX / 3;
        for (int j = 0; j < 26; j++)
            for (int k = 0; k < 26; k++) {
                ans = fmin(ans, dp[ssize][j][k]);
            }
    return ans;
}
