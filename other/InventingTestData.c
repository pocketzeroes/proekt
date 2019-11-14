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
  int first;
  int second;
}pair;
pair newpair(int a, int b){
  return(pair){a,b};
}
typedef struct{
  int   first;
  pair second;
}trip;
trip newtrip(int a, pair b){
  return(trip){a,b};
}

int cmpP(pair a, pair b){
  if(a.first  != b.first) return(a.first  < b.first )?-1:1;
  if(a.second != b.second)return(a.second < b.second)?-1:1;
  return 0;
}
int cmpT(const void*pa, const void*pb){
  trip*a = (trip*)pa;
  trip*b = (trip*)pb;
  if(a->first != b->first)return(a->first < b->first )?-1:1;
  return cmpP(a->second, b->second);
}

#define pb(zpv, zvv) zpv.ptr = pushbackT(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
trip*pushbackT(trip*array, int *size, trip value){
  trip*output = resizeArray(array, trip, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
  trip*ptr;
  int sz;
}vect;
vect newVecT(){
  vect rez;
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
}

enum{ MAXN = 1000123};
int T, N;
int boss[MAXN],
    size[MAXN];

int main() {
  scanf("%d", &T);
  while(T--){
    scanf("%d", &N);
    vect V = newVecT();//of trip
    int x, y, z;
    for(int n=0; n<N-1; ++n){
      scanf("%d %d %d", &x, &y, &z);
      x--, y--;
      pb(V, newtrip(z, newpair(x,y)));
    }
    for(int n=0; n<N; ++n)
      boss[n]=n;
    for(int n=0; n<N; ++n)
      size[n]=1;
    qsort(V.ptr, V.sz, sizeof(trip), cmpT);
    ll res = 0;
    for(int i=0; i<V.sz; ++i){
      int a = V.ptr[i].second.first,
          b = V.ptr[i].second.second;
      while(a!=boss[a])
        a=boss[a];
      while(b!=boss[b])
        b=boss[b];
      ll s1 = size[a],
         s2 = size[b];
      res += s1*s2*(V.ptr[i].first+1)-1;
      if(s1 < s2){
        boss[a]=b;
        size[b]+=size[a];
      }
      else{
        boss[b]=a;
        size[a]+=size[b];
      }
    }
    printf("%lld\n", res);
  }
  return 0;
}
