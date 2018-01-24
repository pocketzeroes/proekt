#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
ll min(ll a, ll b){return a<b?a:b;}
#define rep(i,a,b) for( int i=a; i<b; i++)

enum{ N=100005};

int cmp(const void*pb, const void*pa){
    ll*a =(ll*)pa;
    ll*b =(ll*)pb;
    return(*a < *b)?-1:1;
}

int main(){
    ll n,m;
    scanf("%lld %lld", &n, &m);
    ll a[N],b[N];
    rep(i,0,n)
        scanf("%lld", &a[i]);
    rep(i,0,m)
        scanf("%lld", &b[i]);
    qsort(a, n, sizeof(ll), cmp);//reverse
    qsort(b, m, sizeof(ll), cmp);//reverse
    ll al=0, bo=0;
    for(int i=0; i<min(n,m); i++){
        if (a[i]>b[i])
            al++;
        else
            bo++;
    }
    printf("%lld %lld\n", al, bo);
}

