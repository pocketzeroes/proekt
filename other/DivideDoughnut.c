#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;

#define mod   1000000000ll
#define half   500000000ll
ll n;


ll ask(ll l, ll r){
    ll rec;
    printf("QUERY %lld %lld\n", l, r); fflush(stdout);
    scanf("%lld", &rec);
    return rec;
}
void yes(ll l) {
    printf("YES %lld\n", l); fflush(stdout);
    exit(0);
}
void solve(ll l, ll r){
    ll mid;
    if (r <= l)
        yes(l);
    if (l <= r)
        mid = (l + r) / 2;
    else
        mid = (l + r + mod) / 2;
    mid %= mod;
    ll rec = ask(mid, (mid + half - 1) % mod);
    if (rec == n / 2)
        yes(mid);
    else if (rec < n / 2)
        solve(mid + 1, r);
    else
        solve(l, mid - 1);
}
signed main(){
    scanf("%lld", &n);
    solve(0, mod - 1);
}
