inline int min(int a,int b){return a<b?a:b;}
inline int max(int a,int b){return a>b?a:b;}

int findRotateSteps(char*ring,char* key) {
    int ringsize=strlen(ring);
    int  keysize=strlen(key);
    int dp[101][101];
    memset(dp, -1, sizeof(dp));
    dp[0][0] = 0;
    for (int i=0; key[i]; ++i) {
        for (int j=0; ring[j]; ++j) {
            if (ring[j] != key[i]) { continue; }
            for (int k=0; ring[k]; ++k) {
                if (dp[i][k] < 0) { continue; }
                int a = max(k, j), b = min(k, j);
                int ab = a - b, ba = ringsize + b - a;
                int p = min(ab, ba) + 1 + dp[i][k];
                if (dp[i+1][j] < 0) {
                    dp[i+1][j] = p;
                }
                else {
                    dp[i+1][j] = min(dp[i+1][j], p);
                }
            }
        }
    }
    int last = keysize, ans = 0x7fffffff;
    for (int i=0; i<ringsize; ++i) {
        if (dp[last][i] < 0) { continue; }
        ans = min(ans, dp[last][i]);
    }
    return ans;
}
