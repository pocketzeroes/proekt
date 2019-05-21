#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define swap(a,b) do\
    {\
      a ^= b;\
      b ^= a;\
      a ^= b;\
    } while (0)

typedef long long ll;


ll GI(){
    ll x;
    scanf("%lld", &x);
    return x;
}
enum{ MN = 10111};
ll lab[MN];

void init(ll n){
    for (ll i = 0, _a = (n+2); i < _a; ++i)
      lab[i] = -1;
}
ll getRoot(ll u){
    if (lab[u] < 0)
        return u;
    return lab[u] = getRoot(lab[u]);
}
bool merge(ll u, ll v){
    u = getRoot(u);
    v = getRoot(v);
    if(u == v)
        return false;
    if(lab[u] > lab[v])
        swap(u, v);
    lab[u] += lab[v];
    lab[v] = u;
    return true;
}

typedef struct Edge {
    ll u, v, c;
}Edge;
Edge edges[1001111];

int cmpE(const void*pa, const void*pb){
    Edge*a=(Edge*)pa;
    Edge*b=(Edge*)pb;
    return (a->c < b->c)?-1:1;
}
signed main(){
    ll ntest =GI();
    for (ll test = (1), _b = (ntest); test <= _b; ++test){
        ll n, m, l, s;
        n=GI(); m=GI(); l=GI(); s=GI();
        for (ll i = (1), _b = (s); i <= _b; ++i) {
            ll x=GI();
            edges[m+i].u = x;
            edges[m+i].v = n+1;
            edges[m+i].c = 0;
        }
        for (ll i = (1), _b = (m); i <= _b; ++i) {
            edges[i].u=GI();
            edges[i].v=GI();
            edges[i].c=GI();
        }
        m += s;
        qsort(edges+1, m, sizeof(Edge), cmpE);
        init(n);
        ll res = 0;
        for (ll i = (1), _b = (m); i <= _b; ++i){
            ll u = edges[i].u,
               v = edges[i].v;
            if (getRoot(u) == getRoot(v))
                continue;
            merge(u, v);
            res += edges[i].c;
        }
        for (ll i = (1), _b = (n+1); i <= _b; ++i)
            assert(getRoot(i) == getRoot(1));
        printf("%lld\n", res + (n - s) * l);
    }
    return 0;
}
