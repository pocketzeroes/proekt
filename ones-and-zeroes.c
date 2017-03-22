inline int min(int a,int b){return a<b?a:b;}
inline int max(int a,int b){return a>b?a:b;}

int findMaxForm(char** strs, int strsSize, int m, int n) {
    int dp[m + 1][n + 1];
    memset(dp,0,sizeof(dp));
    for(int i=0;i<strsSize;i++){
        char*str=strs[i];
        int zero_count = 0, one_count = 0;
        for (int j=0;str[j];j++){
            char c=str[j];
            if (c == '0') {
                ++zero_count;
            } else if (c == '1') {
                ++one_count;
            }
        }
        for (int i = m; i - zero_count >= 0; --i) {
            for (int j = n; j - one_count >= 0; --j) {
                dp[i][j] = max(dp[i][j], dp[i - zero_count][j - one_count] + 1);
            }
        }
    }
    return dp[m][n];
}

