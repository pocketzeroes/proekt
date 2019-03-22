#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
typedef long double ld;

void solve(){
    ld r;
    ll n;
    scanf("%Lf%lld", &r, &n);
    ld currarea = M_PI * r * r;
    ld currcircles = 4;
    ld ans = 0;
    ans += currarea;
    ld curradd = currarea * currcircles / 4;
    for(ll i = 0; i < n-1; i++){
        ans += curradd;
        curradd *= .75;
    }
    printf("%.8Lf\n", ans);
}
int main(){
    ll cases;
    scanf("%lld", &cases);
    while(cases--)
        solve();
    return 0;
}


