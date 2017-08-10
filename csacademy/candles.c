#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))


typedef long long ll;  


enum{ M = (ll)1e9+7};
enum{ N = (ll)1e5+7};

ll c[N];
ll h[N];

ll n;

int cmp(const void*pa, const void*pb)
{
    ll*a=(ll*)pa;
    ll*b=(ll*)pb;
    return *a < *b ? 1:-1;
}

bool pos(ll k)
{
    ll val = 0;
    ll sum = 0;
    ll v[n+1];
    memset(v,0,sizeof(v));
    for(ll i=0;i<k;i++)
    {   
        if(c[i]>n) 
            return false;
        sum += c[i];
        v[c[i]]++;
    }
    for(ll i=n-1;i>=1;i--)
        v[i] += v[i+1];
    for(ll i=0;i<n;i++)
    {
        val += min(h[i],v[i+1]);
        if(h[i]<v[i+1] && i+2<n+1)
            v[i+2] += (v[i+1]-h[i]);
    }
    return sum<=val;
}
int main()
{
    ll m;
    scanf("%lld %lld", &n, &m);
    for(ll i=0;i<n;i++)
        scanf("%lld", &h[i]);
    qsort(h, n, sizeof(ll), cmp); //  reverse
    for(ll i=0;i<m;i++)
        scanf("%lld", &c[i]);
    ll l = 0;
    ll hh = m;
    while(l<hh)
    {
        ll mid = (l+hh+1)>>1;
        if(pos(mid))
            l = mid;
        else
            hh = mid-1;
    }
    printf("%lld\n", l);  
}




















































