#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

typedef long long int64;
typedef long long ll;
ll min(ll a,ll b){return a<b?a:b;}
ll max(ll a,ll b){return a>b?a:b;}

int main() {
    int n; 
    scanf("%d", &n);
    int elements[n];//, 0);
    for(int i=0;i<n;i++){
        scanf("%d", &elements[i]);
    }
    int64 mx = -2e9;
    int64 dp[n + 2];//, 0);
    memset(dp, 0, sizeof(dp));
    for (int i = n - 2; i >= 0; i--){
        dp[i] = elements[i] + elements[i + 1] + dp[i + 2];
        mx    = max(mx , dp[i]);
        dp[i] = max(0LL, dp[i]);
    }
    printf("%lld\n", mx);
    return 0;
}
