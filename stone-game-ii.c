int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

int dp[200][200];
int*pile;
int pile_sz;
int sum[200];

int go(int at, int m){
    if (at + m * 2 >= pile_sz)
        return sum[pile_sz] - sum[at];
    if (dp[at][m] != -1)
        return dp[at][m];
    int best = 0x3F3F3F3F;
    for (int x = 1; x <= 2 * m; ++x) {
        int other = go(at + x, max(x, m));
        best = min(best, other);
    }
    return dp[at][m] = (sum[pile_sz] - sum[at] - best);
}
int stoneGameII(int*piles, int pilesSz){
    pile = piles;
    pile_sz=pilesSz;
    sum[0] = 0;
    for(int i=0; i<pilesSz; i++) {
        sum[i + 1] = sum[i] + piles[i];
    }
    memset(dp,-1,sizeof(dp));
    return go(0, 1);
}
