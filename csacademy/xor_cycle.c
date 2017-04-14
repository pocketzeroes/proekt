#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<stdint.h>
#include<limits.h>

typedef unsigned long long ll;
#define int long long

typedef struct tripS
{
    int first ;
    int second;
    int third ;
}trip;
trip newTrip(int _x, int _y, int _z)
{
    trip rez;
    rez.first =_x;
    rez.second=_y;
    rez.third =_z;
    return rez;
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
trip*pushbackT(trip*array, int *size, trip value){
    trip*output = resizeArray(array, trip, *size + 1);
    output[(*size)++] = value;
    return output;
}
ll*pushback(ll*array, int *size, ll value){
    ll*output = resizeArray(array, ll, *size + 1);
    output[(*size)++] = value;
    return output;
}


enum{ MAXN =(int32_t) 1e5 + 10};
trip*a   [MAXN];
int sizes[MAXN];
bool mark[MAXN];
ll*vec=NULL;int vecSz=0;
ll h     [MAXN];

void dfs(int v, int e){
    mark[v] = 1;
    for(int i=0;i<sizes[v];i++){
        trip hlp=a[v][i];
        int u = hlp.first, w = hlp.second, id = hlp.third;
        if(id == e)
            continue;
        if(!mark[u]){
            h[u] = h[v] ^ w;
            dfs(u, id);
        }
        else
            vec=pushback(vec, &vecSz, h[v] ^ h[u] ^ w);
    }
}
int32_t main(){
    ll n, m;
    scanf("%lld %lld", &n, &m);
    for(int i = 0; i < m; i++){
        ll x, y, z;
        scanf("%lld %lld %lld", &x, &y, &z);
        x--;
        a[x]=pushbackT(a[x], sizes+x, newTrip(--y, z, i));
        a[y]=pushbackT(a[y], sizes+y, newTrip(x  , z, i));
    }
    dfs(0, -1);
    n = vecSz;
    ll ans = 0;
    for(int i = 60; i > -1; i--){
        int id = -1;
        for(int j = 0; j < n; j++){
            if((vec[j] & (1LL<<i)))
                id = j;
        }
        if(id == -1)
            continue;
		if(!(ans & (1LL<<i)))
            ans ^= vec[id];
        for(int j = 0; j < n; j++)
            if((vec[j] & (1LL<<i)))
				vec[j] ^= vec[id];
    }
    printf("%lld\n", ans);
    return 0;
}


























































