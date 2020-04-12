#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
enum{MOD =(int)1e9+7};

int numOfWays(int n){
    int states[12];
    int ssz=0;
    for(int i=0; i<3; ++i){
        for(int j=0; j<3; ++j){
            for(int k=0; k<3; ++k){
                if(i != j && j != k)
                    states[ssz++] = (9 * i + 3 * j + k);
            }
        }
    }
    int m = ssz; // 12
    int adj[12][12]; clr(adj);
    for(int i=0; i<m; ++i){
        for(int j=0; j<m; ++j){
            int x = states[i];
            int a1 = x / 9;
            int b1 = (x / 3) % 3;
            int c1 = x % 3;
            x = states[j];
            int a2 = x / 9;
            int b2 = (x / 3) % 3;
            int c2 = x % 3;
            adj[i][j] = a1 != a2 && b1 != b2 && c1 != c2;
        }
    }
    int dp[n][m]; clr(dp);
    fill(dp[0], m, 1);
    for(int i=1; i<n; ++i){
        for(int j=0; j<m; ++j){
            for(int k=0; k<m; ++k){
                if(adj[j][k]){
                    dp[i][k] += dp[i - 1][j];
                    if(dp[i][k] >= MOD)
                       dp[i][k] -= MOD;
                }
            }
        }
    }
    int ans=0;
    for(int j=0; j<m; ++j){
        ans += dp[n - 1][j];
        if(ans >= MOD)
           ans -= MOD;
    }
    return ans;
}
