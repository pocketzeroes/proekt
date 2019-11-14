#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
ll upper_bound(ll*a, ll n, ll x){
    ll l = 0;
    ll h = n;
    while(l < h){
        ll mid = (l + h) / 2;
        if(x >= a[mid])
            l = mid + 1;
        else
            h = mid;
    }
    return l;
}

#define INF 1e12
enum{ maxn = 111111};
int n, r, w, h;

typedef struct{
    ll a, b;
}node;
int cmpN(const void*pa, const void*pb){
    node*t=(node*)pa;
    node*c=(node*)pb;
    if(t->a != c->a)
        return(t->a < c->a)?-1:1;
    return(t->b < c->b)?-1:1;
}

node p [maxn];
ll   a [maxn],
     dp[maxn];

int LIS(ll*a){
    for(int i=1; i<n; i++)
        dp[i] = INF;
    dp[0] = a[0];
    int len = 1;
    for(int i=1; i<n; i++){
        if(a[i] >= dp[len-1])
            dp[len++] = a[i];
        else
            dp[upper_bound(dp, n, a[i])] = a[i];
    }
    return len;
}
int main(){
    while(~scanf("%d %d %d %d", &n, &r, &w, &h)){
        for(int i=0; i<n; i++){
            ll x, y;
            scanf("%lld %lld", &x, &y);
            p[i].a = 1ll*r*x+y,
            p[i].b = 1ll*r*(w-x)+y;
        }
        qsort(p, n, sizeof(node), cmpN);
        for(int i=0; i<n; i++)
            a[i] = p[i].b;
        printf("%d\n", LIS(a));
    }
    return 0;
}
