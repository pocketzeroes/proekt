typedef long long ll;
enum{mod =(int) 1e9 + 7};
enum{ N = 1011};
int dp[N][N];
int cnt[N][26];

int numWays(char**words, int wordsSz, char*target){
    int n = strlen(words[0]);
    int m = strlen(target);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < 26; j++)
            cnt[i + 1][j] = 0;
    }
    for(int z=0;z<wordsSz;z++){char*tmp = words[z];
        for(int i = 0; i < n; i++) {
            cnt[i + 1][tmp[i] - 'a']++;
        }
    }
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= m; j++) {
            if(j == 0) {
                dp[i][j] = 1;
            }
            else {
                dp[i][j] = 0;
                if(i > 0) {
                    dp[i][j] = (dp[i][j] + dp[i - 1][j]) % mod;
                    dp[i][j] = (dp[i][j] + dp[i - 1][j - 1] * (ll)cnt[i][target[j - 1] - 'a']) % mod;
                }
            }
        }
    }
    return dp[n][m];
}
