#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
ll max(ll a, ll b){return a>b?a:b;}
const ll INF = 0xffffffffll * 100000ll;

#define dfill(arr, sz1, sz2, val)do{     \
  for(int i=0; i<sz1; i++)               \
    for(int j=0; j<sz2; j++)             \
      arr[i][j] = val;                   \
}while(0)

int main(){
    ll n, k;
    scanf("%lld%lld", &n, &k);
    ll A[n];
    for(ll i=0; i<n; ++i)
        scanf("%lld", &A[i]);
    ll Best   [n][k+1]; dfill(Best   , n, k+1, -INF);
    ll BestInc[n][k+1]; dfill(BestInc, n, k+1, -INF);
    for(ll i = 0; i < n; ++i)
        Best[i][0] = 0;
    Best[0][1] = BestInc[0][1] = A[0];
    for(ll i = 1; i < n; ++i){
        for(ll j = 1; j <= k; ++j){
            BestInc[i][j] = max(BestInc[i-1][j], Best[i-1][j-1]) + A[i];
            Best[i][j] = max(Best[i-1][j], BestInc[i][j]);
        }
    }
    printf("%lld\n", Best[n-1][k]);
    return 0;
}
