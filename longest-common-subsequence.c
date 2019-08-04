int longestCommonSubsequence(char*text1, char*text2){
    int n1 = strlen(text1),
        n2 = strlen(text2);
    int dp[n2+1]; memset(dp, 0, sizeof(dp));
    for (int i = 1; i <= n1; ++i){
        int prev = 0;
        for (int j = 1; j <= n2; ++j) {
            int tmp = dp[j];
            if (text1[i - 1] == text2[j - 1])
                dp[j] = 1 + prev;
            else
                dp[j] = fmax(tmp, dp[j - 1]);
            prev = tmp;
        }
    }
    return dp[n2];
}
