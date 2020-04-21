#define MOD 1000000007

int dp[55][105][55];

void add(int*a, int b){
    if(a){
        (*a) += b;
        if((*a) >= MOD)
           (*a) -= MOD;
    }
}
int numOfArrays(int n, int m, int k){
    memset(dp, 0, sizeof(dp));
    dp[0][0][0] = 1;
    for(int i = 0; i < n; i++)
        for(int j = 0; j <= m; j++)
            for(int l = 0; l <= n; l++)
                for(int ii = 1; ii <= m; ii++)
                    if(ii <= j)
                        add(&dp[i + 1][j][l], dp[i][j][l]);
                    else
                        add(&dp[i + 1][ii][l + 1], dp[i][j][l]);
    int ans = 0;
    for(int i = 0; i <= m; i++)
        add(&ans, dp[n][i][k]);
    return ans;
}
