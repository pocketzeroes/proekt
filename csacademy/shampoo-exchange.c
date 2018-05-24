#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
inline ll min(ll a, ll b){return a<b?a:b;}
inline ll max(ll a, ll b){return a>b?a:b;}

int N;
ll X,Q[101010];

int cmp(const void*pb, const void*pa){
    ll*a=(ll*)pa;
    ll*b=(ll*)pb;
    return *a < *b ? -1:1;
}
int main(){
    int i,j,k,l,r,x,y;
    scanf("%d %lld", &N, &X);
    ll S=0;
    for(i=0; i<N; i++){
        scanf("%lld", &Q[i]);
        S += Q[i];
    }
    qsort(Q, N, sizeof(ll), cmp); // reverse
    ll num = (S+(X-1))/X;
    ll TS=0;
    for(i=0; i<num; i++)
        TS+=Q[i];
    ll mi=0;
    for(x=num; x<N; x++)
        mi = max(mi,Q[x]);
    ll ret = (1LL<<30)-1;
    for(i=29; i>=0; i--){
        ll pat = ret-(1LL<<i);
        if(pat < mi)
            continue;
        ll tot  = 0;
        ll pour = 0;
        for(x=0; x<num; x++)
            tot += min(pat,X-Q[x]);
        if(tot>=S-TS)
            ret = pat;
    }
    printf("%lld %lld\n", num, ret);
    return 0;
}
