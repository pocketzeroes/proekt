#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
typedef struct{
  ll first, second;
}pll;
pll newpll(int a, int b){
  return(pll){a,b};
}
int cmpP(pll a, pll b){
  if(a.first  != b.first) return(a.first  < b.first )?-1:1;
  if(a.second != b.second)return(a.second < b.second)?-1:1;
  return 0;
}
pll maxP(pll a, pll b){return cmpP(a, b)>0?a:b;}

//struct SparseTable{

ll n;
ll*v;
ll*rmqValues;
static inline ll node(ll l, ll i){
    return i+l*n;
}
void SparseTable(ll*values){
    ll d = log2(n);
    v = calloc((d + 1) * n, sizeof(ll));
    memcpy(v, values, n*sizeof(ll));
    for(ll L = 0, s = 1; L < d; L++, s *= 2){
        for(ll i = 0; i < n; i++){
            v[node(L + 1, i)] = fmaxl(v[node(L, i)], v[node(L, fminl(i + s, n - 1))]);
        }
    }
}
ll query(ll lo, ll hi){
    if (lo >= hi)
        return 0;
    ll l = (ll)log2(hi - lo);
    return fmaxl(v[node(l, lo)], v[node(l, hi - (1 << l))]);
}
//};
int main(){
    scanf("%lld", &n);
    ll capacity [n];
    rmqValues = calloc(n, sizeof(ll));
    for(ll i=0; i<n; i++){
        scanf("%lld", &capacity[i]);
        rmqValues[i] = capacity[i]-500*i;
    }
    SparseTable(rmqValues);
    pll ans = newpll(1, 0);
    pll prevBest;
    for(ll st = n - 1; st >= 0; st--){
        pll best = newpll(1, st);
        if(st < n - 1){
            ll nextMx = prevBest.first;
            ll nextI  = prevBest.second;
            if(1000 + nextMx * 500 > capacity[st]){
                best =(pll){ nextMx + 1, nextI };
            }
        }
        ll lo = st + best.first;
        ll hi = n;
        while(hi > lo){
            ll mid = lo + (hi - lo) / 2;
            if(query(st + best.first, fminl(mid + 1, n)) >= 1000 - st * 500)
                hi = mid;
            else
                lo = mid + 1;
        }
        best.first = lo - st;
        ans = maxP(ans, best);
        prevBest = best;
    }
    printf("%lld %lld\n", ans.first, ans.second);
    free(rmqValues);
    return 0;
}
