#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>
typedef long long ll;
ll min(ll a,ll b){return a<b?a:b;}
ll max(ll a,ll b){return a>b?a:b;}

#define rep(i,n) for(i=0;i<n;i++)

int main()
{
    ll i, j, n, tt;
    tt = 1;
    while(tt--)
    {
        ll p = 0, k, a, sum=0;
        scanf("%lld %lld", &n, &k);
        rep(i,n)
        {
            scanf("%lld", &a);
            p+=(a/2);
            sum+=a;
        }
        if(p<k)
            puts("-1");
        else
            printf("%lld\n", min((ll)(n+1+2*(k-1)), sum) );
    }
    return 0;
}





























