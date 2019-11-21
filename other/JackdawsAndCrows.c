#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)

typedef long long ll;
typedef struct{
  ll first;
  ll second;
}pll;
pll newpll(ll a, ll b){
  return(pll){a,b};
}
int cmpP(const void*pa, const void*pb){
  pll*a = (pll*)pa;
  pll*b = (pll*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}

const ll oo = 0x3f3f3f3f3f3f3f3fLL;

enum{ WILD = 1000*1000*1000LL+1};

typedef struct node{
  ll val, prev, next;
}node;
inline int sign(ll v){
  return(0 < v) - (v < 0);
}
inline ll abso(ll v){
  return sign(v) * v;
}
inline int sign_mod2(ll v){
  v %= 2;
  return (v == 0) - (v > 0);
}
inline bool is_alternating(node*nodes, size_t a, size_t b){
  ll dist = abso(a - b);
  return sign(nodes[a].val * nodes[b].val) == sign_mod2(dist);
}
ll prepare(node*nodes, ll n){
  ll last_valid = -1;
  ll removals = 0;
  for(ll i = (0); i < (n); i++){
    if(nodes[i].val == 0){
      removals++;
      nodes[i].val = WILD;
    }
    else{
      if(last_valid != -1){
        if(nodes[last_valid].val * nodes[i].val > 0)
          removals++;
        nodes[last_valid].next = i;
        nodes[i].prev = last_valid;
      }
      else{
        nodes[i].prev = -1;
        nodes[n].prev = i;
      }
      last_valid = i;
    }
  }
  if(last_valid != -1){
    nodes[last_valid].next = -1;
    nodes[n].next = last_valid;
  }
  else{
    nodes[n].next = -1;
    nodes[n].prev = -1;
  }
  return removals;
}
ll check  (node*nodes, ll n){
  ll removals = 0;
  for(int i = nodes[n].prev; i < nodes[n].next; i = nodes[i].next){
    if(!is_alternating(nodes, i, nodes[i].next))
      removals++;
  }
  return removals;
}
ll update (node*nodes, ll n, size_t i){
  ll change = 0;
  if(nodes[i].prev != -1) {
    if(!is_alternating(nodes, i, nodes[i].prev))
      change -= 1;
    nodes[nodes[i].prev].next = nodes[i].next;
  }
  if(nodes[i].next != -1) {
    if(!is_alternating(nodes, i, nodes[i].next))
      change -= 1;
    nodes[nodes[i].next].prev = nodes[i].prev;
  }
  if(nodes[i].prev != -1 && nodes[i].next != -1 && !is_alternating(nodes, nodes[i].prev, nodes[i].next))
    change += 1;
  nodes[i].val = WILD;
  if(nodes[n].prev == i)
    nodes[n].prev = nodes[i].next;
  if(nodes[n].next == i)
    nodes[n].next = nodes[i].prev;
  return change;
}
int main(){
  ll n, x, y;
  scanf("%lld %lld %lld", &n, &x, &y);
  node nodes[n+1]; clr(nodes);
  pll  vals [n];
  for(ll i=0; i<n; i++){
    ll val;
    scanf("%lld", &val);
    vals[i] = newpll(abso(val), i);
    nodes[i].val = val;
    nodes[i].prev = i - 1;
    nodes[i].next = i + 1;
  }
  nodes[n-1].next = -1;
  nodes[n].prev = 0;
  nodes[n].next = n - 1;
  qsort(vals, n, sizeof(pll), cmpP);
  ll best = oo;
  ll index = 0;
  ll current_removal = 0;
  if(vals[0].first == 0){
    best = prepare(nodes, n) * y;
    current_removal = check(nodes, n);
    best = fminl(best, x * 1 + y * current_removal);
    while(index < n && vals[index].first == 0)
      index++;
  }
  else{
    current_removal = check(nodes, n);
    best = y * current_removal;
  }
  while(index < n){
    ll fakes = vals[index].first;
    while(index < n && vals[index].first == fakes){
      current_removal += update(nodes, n, vals[index].second);
      index++;
    }
    best = fminl(best, x * (fakes + 1) + y * current_removal);
  }
  printf("%lld\n", best);
  return 0;
}
