#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;

ll gcd(ll a, ll b, ll*s, ll*t){
    ll s0=1, s1=0;
    ll t0=0, t1=1;
    while (b != 0) {
        ll q = a/b;
        ll tmp = a%b;
        a = b;
        b = tmp;
        tmp = s0 - q*s1;
        s0 = s1;
        s1 = tmp;
        tmp = t0 - q*t1;
        t0 = t1;
        t1 = tmp;
    }
   *s = s0;
   *t = t0;
    return a;
}
void calcThreeLargest(ll x, ll y, ll m[]){
    ll maxVal = (x + y - sqrt(x*x+y*y-x*y))/6.0;
    m[0] = 0;
    for(ll val = maxVal-2; val <= maxVal+2; val++) {
        ll vol = ((4*val - 2*(x+y))*val + x*y)*val;
        if (vol > m[0]) {
            m[2] = m[1];
            m[1] = m[0];
            m[0] = vol;
        }
        else if (vol == m[0])
            continue;
        else if (vol > m[1]) {
            m[2] = m[1];
            m[1] = vol;
        }
        else if (vol == m[1])
            continue;
        else if (vol > m[2])
            m[2] = vol;
    }
}
void solve(ll a[], ll m[], int n, ll*x, ll*mod){
    ll s, t;
    ll a1 = a[0];
    ll m1 = m[0];
    for ( int i = 1; i < n; i++ ) {
        int a2 = a[i];
        int m2 = m[i];
        ll g =gcd(m1, m2, &s, &t);
        if ( a1 % g != a2 % g ){
            fprintf(stderr, "ERROR: unsolvable set of equations\n");
           *x   = -1;
           *mod = -1;
            return;
        }
        gcd(m1/g, m2/g, &s, &t);
       *mod = m1 / g * m2;
        ll x = (a1*(m2/g)*t + a2*(m1/g)*s) % (*mod);
        a1 = x;
        if (a1 < 0)
            a1 += (*mod);
        m1 = *mod;
    }
   *x = a1;
}
int main(){
    ll x, y, low, high;
    ll a[3], m[3];
    ll s, t;
    ll ans, mod;
    scanf("%lld %lld %lld %lld %lld %lld %lld", &x, &y, &a[0], &a[1], &a[2], &low, &high);
    calcThreeLargest(x, y, m);
    solve(a, m, 3, &ans, &mod);
    while (ans < low)
        ans += mod;
    printf("%lld\n", ans);
    if(ans > high)        fprintf(stderr, "ERROR: answer out of range\n");
    if(ans + mod <= high) fprintf(stderr, "ERROR: second solution\n"    );
    return 0;
}
