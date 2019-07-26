#include<stdio.h>
#include<assert.h>
#include<time.h>

enum{ MAXN = 15};

typedef long long ll;
#define I64d "%lld";

ll MOD = 1000000007;
ll dp_count[1<<MAXN];
ll dp_sum  [1<<MAXN];
ll dp_self [1<<MAXN];
ll self[MAXN], sum[MAXN];
int last_bit[1<<MAXN];
int p[MAXN], a[MAXN];

int isprime(int p)
{
    int i;
    for(i=2;i*i<=p;i++)
        if(p%i==0)
            return 0;
    return 1;
}

ll bigmod(ll p, ll a)
{
    if(a==0) return 1;
    ll x = bigmod(p,a/2);
    x = (x*x)%MOD;
    if(a&1) x=(x*p)%MOD;
    return x;
}

ll calc_series_sum(ll p, ll a)
{
    if(a==0) return 1;
    if(a&1)
    {
        ll x = calc_series_sum((p*p)%MOD,a/2);
        return (x + x*p)%MOD;
    }
    ll x = calc_series_sum(p, a-1);
    return (1 + x*p)%MOD;
}

int main(){
    int T, i, lim, c, n, ks, rest;
    ll ans, now;
    scanf("%d",&T);
    assert(1<=T && T<=500);
    lim = (1<<MAXN)-1;
    last_bit[0] = 0;
    for(i=1;i<=lim;i++){
        if(i&1)
            last_bit[i] = 0;
        else
            last_bit[i] = last_bit[i>>1]+1;
    }
    for(ks=1;ks<=T;ks++){
        scanf("%d",&n);
        assert(1<=n && n<=MAXN);
        for(i=0;i<n;i++){
            scanf("%d%d",&p[i],&a[i]);
            assert(isprime(p[i]) && 1<=p[i] && p[i]<=1000);
            assert(1<=a[i] && a[i]<=50);
            sum[i] = calc_series_sum(p[i], a[i]-1);
            self[i] = bigmod(p[i], a[i]);
        }
        lim = (1<<n)-1;
        dp_count[0] = 1;
        dp_sum[0] = 1;
        dp_self[0] = 1;
        for(i=1;i<=lim;i++){
            c = last_bit[i];
            dp_count[i] = (dp_count[i^(1<<c)]*(a[c]+1))%MOD;
            dp_sum[i] = (dp_sum[i^(1<<c)]*sum[c])%MOD;
            dp_self[i] = (dp_self[i^(1<<c)]*self[c])%MOD;
        }
        ans = 0;
        for(i=0;i<=lim;i++){
            rest = lim^i;
            now = (dp_self[i]*dp_count[i])%MOD;
            now = (dp_sum[rest]*now)%MOD;
            ans = (ans + now)%MOD;
        }
        ans = (ans + dp_self[lim])%MOD;
        printf("Case %d: %lld\n",ks, ans);
    }
    return 0;
}
