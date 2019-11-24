#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
typedef long long ll;
enum{ MOD = 1000000007};

int numWays(int steps, int L){
    L = fmin(L, steps + 1);
    ll dp[L]; clr(dp);
    dp[0] = 1;
    for(int t=(0),t_end_=(steps);t<t_end_;t++){
        ll dpnew[L]; clr(dpnew);
        for(int i=(0),i_end_=(L);i<i_end_;i++){
            if(i){
                dpnew[i-1]+=dp[i]; dpnew[i-1]%=MOD;
            }
            dpnew[i] += dp[i]; dpnew[i]%=MOD;
            if(i + 1 < L){
                dpnew[i+1]+=dp[i]; dpnew[i+1]%=MOD;
            }
        }
        memcpy(dp, dpnew, sizeof(dp));
    }
    return dp[0];
}
