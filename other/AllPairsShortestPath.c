#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
const ll inf=(ll)1e18+10;
#define dfill(arr, sz1, sz2, val)do{     \
  for(int i=0; i<sz1; i++)               \
    for(int j=0; j<sz2; j++)             \
      arr[i][j] = val;                   \
}while(0)


int main(){
    ll n, m, q;
    while(1){
        scanf("%lld %lld %lld", &n, &m, &q);
        if(n == 0 && m == 0 && q == 0)
            break;
        ll v[n][n]; dfill(v, n, n, inf);
        for(ll i=0; i<n; i++)
            v[i][i] = 0;
        for(ll i=0; i<m; i++){
            ll n1, n2, w;
            scanf("%lld %lld %lld", &n1, &n2, &w);
            v[n1][n2] = fminl(v[n1][n2], w);
        }
        for(ll k=0; k<n; k++){
            for(ll i=0; i<n; i++){
                for(ll j=0; j<n; j++){
                    if(v[i][k] < inf && v[k][j] < inf)
                       v[i][j] = fminl(v[i][j], v[i][k] + v[k][j]);
                }
            }
        }
        for(ll i=0; i<n; i++){
            for(ll j=0; j<n; j++){
                for(ll k = 0; k < n; k++){
                    if(v[k][k] < 0 && v[i][k] != inf && v[k][j] != inf)
                        v[i][j] = -inf;
                }
            }
        }
        for(ll i=0; i<q; i++){
            ll n1, n2;
            scanf("%lld %lld", &n1, &n2);
            if(v[n1][n2] == inf){
                puts("Impossible");
                continue;
            }
            if(v[n1][n2] == -inf){
                puts("-Infinity");
                continue;
            }
            printf("%lld\n", v[n1][n2]);
        }
        puts("");
    }
    return 0;
}
