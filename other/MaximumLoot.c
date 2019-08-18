#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
typedef struct{
  ll first;
  ll second;
}pair;
pair newPair(ll a, ll b){
  return(pair){a, b};
}
pair*pushbackP(pair*array, int *size, pair value){
  pair*output = resizeArray(array, pair, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
  pair*ptr;
  int sz;
}vecp;
vecp newVecP(){
  vecp rez;
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
}
int cmpP(const void*pa, const void*pb){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}

enum{ magic_constant = 38};
ll mc[1 << ((77 - magic_constant) / 2)];

int main(){
  int T;
  scanf("%d", &T);
  while (T--) {
    int n, _C;
    scanf("%d %d", &n, &_C);
    ll C = (ll)(_C);
    int v[n];
    int c[n];
    for (int i = 0; i < n; ++i) scanf("%d", &v[i]);
    for (int i = 0; i < n; ++i) scanf("%d", &c[i]);
    ll VMax = 0LL;
    for (int i = 0; i < n; ++i) VMax += v[i];
    if (n <= magic_constant) {
      int sz = n / 2;
      vecp val=newVecP();
      for (unsigned int mask = 0; mask < (1 << sz); ++mask) {
        ll cost = 0LL, value = 0LL;
        for (int i = 0; i < sz; ++i) {
          if (1&(mask >> i)) {
            cost += c[i];
            value += v[i];
          }
        }
        if (cost <= C)
          val.ptr = pushbackP(val.ptr, &val.sz, (pair){cost, value});
      }
      qsort(val.ptr, val.sz, sizeof(pair), cmpP);
      for (int i = 1; i < val.sz; ++i)
        val.ptr[i].second = fmax(val.ptr[i].second, val.ptr[i-1].second);
      ll best = 0LL;
      for (unsigned int mask = 0; mask < (1 << (n - sz)); ++ mask) {
        ll cost = 0LL, value = 0LL;
        for (int i = sz; i < n; ++i) {
          if (1&(mask >> (i - sz))) {
            cost += c[i];
            value += v[i];
          }
        }
        int l = 0, r = -1 + val.sz;
        while (l < r) {
          int m = (l + r) / 2;
          if (val.ptr[m].first + cost <= C)
            l = m + 1;
          else
            r = m;
        }
        while (l > 0 && val.ptr[l].first + cost > C)
          l--;
        if(val.ptr[l].first + cost <= C && val.ptr[l].second + value > best)
          best = val.ptr[l].second + value;
      }
      printf("%lld\n", best);
    }
    else {
      memset(mc, -1, sizeof(mc));
      mc[0] = 0LL;
      for (int i = 0; i < n; ++i)
       for (int val = VMax - v[i]; val >= 0; --val) {
        if (mc[val] >= 0 && (mc[val + v[i]] > mc[val] + c[i] || mc[val + v[i]] == -1) && mc[val] + c[i] <= C)
          mc[val + v[i]] = mc[val] + c[i];
       }
      ll best = VMax;
      while (mc[best] == -1)
        best--;
      printf("%lld\n", best);
    }
  }
  return 0;
}
