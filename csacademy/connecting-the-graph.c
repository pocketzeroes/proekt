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
  int first, second;
}pair;
pair newpair(int a, int b){
  return(pair){a,b};
}

typedef struct{
  ll   first;
  pair second;
}trip;
trip newtrip(ll a, pair b){
  return(trip){a,b};
}

int cmpP(const void*pa, const void*pb){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}
int cmpT(const void*pa, const void*pb){
  trip*a = (trip*)pa;
  trip*b = (trip*)pb;
  if(a->first != b->first)
    return(a->first < b->first )?-1:1;
  return cmpP(&a->second, &b->second);
}
///////////////////////////
enum{NMAX =(int)1e5};
int n,m;
trip*edges;//of trip{ll, pair}
int  esz;
pair vals[NMAX + 5];
int  dsu [NMAX + 5];

int fi_root(int nod){
   if(dsu[nod] == 0)
      return nod;
   return dsu[nod] = fi_root(dsu[nod]);
}
void unite(int x, int y){
   x = fi_root(x);
   y = fi_root(y);
   if(x == y)
      return;
   dsu[x] = y;
}
int main(){
   scanf("%d %d", &n, &m);
   edges = calloc(m+n, sizeof(trip));
   for(int i=1; i<=n; i++){
      scanf("%d", &vals[i].first);
      vals[i].second = i;
   }
   qsort(vals+1, n, sizeof(pair), cmpP);
   for(int i=1; i<=m; i++){
      int x, y;
      scanf("%d %d", &x, &y);
      edges[esz++] = newtrip(0, newpair(x,y));
   }
   for(int i=1; i<n; i++)
      edges[esz++] = newtrip(1LL*(vals[i].first-vals[i+1].first)*(vals[i].first-vals[i+1].first), newpair(vals[i].second,vals[i + 1].second));
   qsort(edges, esz, sizeof(trip), cmpT);
   ll ans = 0;
   for(int z=0;z<esz;z++){trip it = edges[z];
      if(fi_root(it.second.first) != fi_root(it.second.second)){
         unite(it.second.first,it.second.second);
         ans += it.first;
      }
   }
   printf("%lld\n", ans);
   return 0;
}
