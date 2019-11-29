#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;

void fill(ll*arr, int sz, ll val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
typedef struct{
  ll first, second;
}pair;
pair newpair(ll a, ll b){
  return(pair){a,b};
}

int x[401],
    y[401],
    c[401];
ll  F[401][401];


ll calcTri(int a, int n, int b){
    pair l[2];
    l[0] = newpair(x[a]-x[n], y[a]-y[n]);
    l[1] = newpair(x[a]-x[b], y[a]-y[b]);
    return llabs(l[0].first*l[1].second-l[0].second*l[1].first);
}
ll f(int a,int b){
    if(b-a==1)
        return 0;
    ll tmp=0;
    if(F[a][b]==-1){
        for(int n=a+1;n<b;n++)
            tmp+=c[n];
        for(int n=a+1;n<b;n++)
            tmp=fmaxl(tmp,f(a,n)+f(n,b)+calcTri(a,n,b));
        F[a][b]=tmp;
    }
    return F[a][b];
}
int main(){
    int n;
    scanf("%d", &n);
    for(int i=0; i<n; ++i)
        scanf("%d %d %d", &x[i], &y[i], &c[i]);
    for(int i=0; i<401; ++i)
        fill(F[i], 401, -1ll);
    memcpy(x+n, x, n*sizeof(int));
    memcpy(y+n, y, n*sizeof(int));
    memcpy(c+n, c, n*sizeof(int));
    ll total = 0;
    for(int i=0; i<n; ++i)
        total+=c[i];
    for(int i=0; i<n; ++i)
        for(int m=i+1; m<n; m++)
            total = fmaxl(f(i,m)+f(m,i+n), total);
    printf("%lld\n", total);
    return 0;
}
