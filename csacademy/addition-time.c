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
  ll  first;
  int second;
}pli;
pli newpli(ll a, int b){
  return(pli){a,b};
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
#define pbp(zpv, zvv) zpv.ptr = pushbackP(zpv.ptr, &zpv.sz, zvv)
pli*pushbackP(pli*array, int*size, pli val){
  pli*output = resizeArray(array, pli, *size + 1);
  output[(*size)++] = val;
  return output;
}
typedef struct{
	pli*ptr;
	int sz;
}vecp;
vecp newVecP(){
	vecp rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
int cmpP(const void*pa, const void*pb){
  pli*a=(pli*)pa;
  pli*b=(pli*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}

/////////////////////////////
int main(){
  int n;
  ll  x;
  scanf("%d %lld", &n, &x);
  ll v[n];
  for(int i=0; i<n; ++i)
    scanf("%lld", &v[i]);
  int m = n / 2;
  vecp l = newVecP();
  vecp r = newVecP();//of pli
  for(int msk=0; msk<(1<<m); ++msk){
    ll sum = 0;
    for(int i=0; i<m; ++i)
      if(msk & (1 << i))
        sum += v[i];
    pbp(l, newpli(sum, msk));
  }
  for(int msk=0; msk<(1<<(n-m)); ++msk){
    ll sum=0;
    for(int i=0; i<n-m; ++i)
      if(msk&(1 << i))
        sum += v[i + m];
    pbp(r, newpli(sum, msk));
  }
  qsort(l.ptr, l.sz, sizeof(pli), cmpP);
  qsort(r.ptr, r.sz, sizeof(pli), cmpP);
  int at = r.sz-1;
  for(int i=0; i<l.sz; ++i){
    while(l.ptr[i].first + r.ptr[at].first > x){
      if((at--) == 0){
        puts("-1");
        return 0;
      }
    }
    if(l.ptr[i].first + r.ptr[at].first == x){
      printf("%d\n", __builtin_popcount(l.ptr[i].second) + __builtin_popcount(r.ptr[at].second));
      for(int j=0; j<m; ++j)
        if(l.ptr[i].second & (1 << j))
          printf("%lld ", v[j]);
      for(int j=0; j<n-m; ++j)
        if(r.ptr[at].second & (1 << j))
          printf("%lld ", v[j + m]);
      puts("");
      return 0;
    }
  }
  puts("-1");
  return 0;
}
