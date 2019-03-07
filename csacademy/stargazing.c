#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
ll min(ll a, ll b){return a<b?a:b;}
ll max(ll a, ll b){return a>b?a:b;}

ll lower_bound(ll*a, ll n, ll x){
  ll l = 0;
  ll h = n;
  while (l < h){
    ll mid = (l + h) / 2;
    if(x <= a[mid])
      h = mid;
    else
      l = mid + 1;
  }
  return l;
}

typedef struct{
  ll first;
  int second;
}pair;
pair newPair(ll a, int b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}
int cmpP(const void*pa, const void*pb){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}
int cmpLL(const void*pa, const void*pb){
  ll*a =(ll*)pa;
  ll*b =(ll*)pb;
  return(*a < *b)?-1:1;
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
ll*pushback(ll*array, int*size, ll value){
  ll*output = resizeArray(array, ll, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
  ll*ptr;
  int sz;
}vecl;
vecl newVecL(){
  vecl rez;
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
}

enum{ Maxq = 100005    };
enum{ mod  = 1000000007};
ll n;
int q;
pair seq[Maxq];
ll  mem[Maxq];
vecl dvs;
ll mn[Maxq], 
   mx[Maxq];
int res;

ll gcd(ll x, ll y){
  return x? gcd(y % x, x): y;
} 

int main(){
  scanf("%lld %d", &n, &q);
  for (int i = 0; i < q; i++)
    scanf("%d %lld", &seq[i].second, &seq[i].first);
  qsort(seq, q, sizeof(pair), cmpP);
  int fir = 0;
  while (seq[fir].second == 0)
    fir++;
  int lst = q - 1;
  while (seq[lst].second == 0)
    lst--;
  ll cur = 0;
  ll obt = -1;
  for (int i = 0; i < q; i++){
    if(seq[i].second == 0)
      mem[i] = obt == -1? cur: gcd(cur, seq[i].first - obt);
    else{
      if (obt != -1)
        cur = gcd(cur, seq[i].first - obt);
      obt = seq[i].first;
    }
  }
  for(ll i = 1; i * i <= cur; i++){
    if (cur % i == 0){
      dvs.ptr = pushback(dvs.ptr, &dvs.sz, i);
      if(i*i < cur)
        dvs.ptr = pushback(dvs.ptr, &dvs.sz, cur/i);
    }
  }
  qsort(dvs.ptr, dvs.sz, sizeof(ll), cmpLL);
  for(int i = 0; i < dvs.sz; i++){
    mn[i] = 1;
    mx[i] = n;
  }
  cur = 0;
  obt = -1;
  for(int i = q - 1; i >= 0; i--){
    if(seq[i].second == 0){
      ll newmem = obt == -1? cur: gcd(cur, obt - seq[i].first);
      ll nd = gcd(mem[i], newmem);
      int ind = lower_bound(dvs.ptr, dvs.sz, nd);
      if (ind < dvs.sz && dvs.ptr[ind] == nd){
        if (i < fir)
          mn[ind] = max(mn[ind], seq[i].first + 1);
        else if (i < lst) { 
          mn[ind] = n + 1, 
          mx[ind] = 0;
        }
        else 
          mx[ind] = min(mx[ind], seq[i].first - 1);
      }
    }
    else {
      if (obt != -1)
        cur = gcd(cur, obt - seq[i].first);
      obt = seq[i].first;
    }
  }
  for (int i = dvs.sz - 1; i >= 0; i--){
    for (int j = i + 1; j < dvs.sz; j++){
      if(dvs.ptr[j] % dvs.ptr[i] == 0){
        mn[i] = max(mn[i], mn[j]);
        mx[i] = min(mx[i], mx[j]);
      }
    }
    ll a = mn[i] <= seq[fir].first? 1 + (seq[fir].first - mn[i]) / dvs.ptr[i]: 0;
    ll b = seq[lst].first <= mx[i]? 1 + (mx[i] - seq[lst].first) / dvs.ptr[i]: 0;
    a %= mod;
    b %= mod;
    res = (res + a * b) % mod;
  }
  printf("%d\n", res);
  return 0;
}
