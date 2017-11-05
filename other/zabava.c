#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
ll min(ll a, ll b){return a<b?a:b;}
#define LLINF 9000000000000000000LL;

ll nsum(ll N){
    return N * (N + 1LL) / 2LL;
}
ll solve(ll S, ll K){
    if (S <= 1) 
        return S;
    if (K >= S) 
        K = LLINF;
    ll sz  = S / (K+1);
    ll rem = S % (K+1);
    return rem * nsum(sz+1) + (K+1 - rem) * nsum(sz);
}
int main(){
    int N, M, K;
    scanf("%d %d %d", &N, &M, &K);
    int S[M]; memset(S, 0, sizeof(S));
    while(N--){
        int v;
        scanf("%d", &v);
        S[v - 1]++;
    }
    ll dp[M][K+1];
    for(int i=0; i<M;   i++)
        for(int j=0; j<K+1; j++)
            dp[i][j] = LLINF;
    for (int m = 0; m < M; ++m){
        dp[m][0] = nsum(S[m]) + (m > 0 ? dp[m-1][0] : 0LL);
        for (int s = 0; s <= K; ++s){
            ll cost = solve(S[m], s);
            if (m == 0) 
                dp[m][s] = cost;
            else for (int r = 0; r + s <= K; ++r)
                dp[m][r+s] = min(dp[m][r+s], dp[m-1][r]+cost);
        }
    }
    ll ans = dp[M - 1][0];
    for (int s = 1; s <= K; ++s)
        ans = min(ans, dp[M - 1][s]);
    printf("%lld\n", ans);
    return 0;
}



