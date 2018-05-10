#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>
typedef long long ll;
ll min(ll a, ll b){return a<b?a:b;}
ll max(ll a, ll b){return a>b?a:b;}
ll h[2002];
int main(){
    ll n, m, ans=0;
    scanf("%lld %lld", &n, &m);
    ll x[n+2],
       y[n+2];
    for(ll i=0; i<n; i++){
        scanf("%lld", &x[i]);
        scanf("%lld", &y[i]);
    }
    for(ll i=0,p,q; i<m; i++){
        scanf("%lld", &p);
        scanf("%lld", &q);
        ll mn=(ll)1e7,in;
        for(ll j=0; j<n; j++){
            ll d = ((x[j]-p)*(x[j]-p))+((y[j]-q)*(y[j]-q));
            if(mn>d){
                mn = d;
                in = j;
            }
            else if(mn==d) 
                in = min(in,j);
        }
        h[in]++;
    }
    for(int i=0; i<n; i++) 
        if(h[i]==1) 
            ans++;
    printf("%lld\n", ans);
    return 0;
}
