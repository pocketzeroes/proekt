#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
const ll MOD = 1e9+7;

void fill(ll*arr, int sz, ll val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
int main(){
    int H, W;
    scanf("%d %d", &H, &W);
    if(H == 1){
        printf("%d\n", (int)(W == 1));
        return 0;
    }
    ll dp[W][H]; memset(dp, 0, sizeof(dp));
    fill(dp[0], H, 1LL);
    for(int w = 1; w < W; ++w)
        for(int h = 1; h < H; ++h)
            for(int i = 0; i < w; ++i)
                dp[w][h] = (dp[w][h] + dp[i][h-1] * dp[w-1-i][h]) % MOD;
    printf("%lld\n", ((MOD + dp[W-1][H-1] - dp[W-1][H-2]) % MOD));
    return 0;
}
