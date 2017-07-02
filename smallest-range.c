#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

typedef struct pair{
    int first;
    int second;
}pair;
pair newPair(int a, int b){
    pair rez;
    rez.first =a;
    rez.second=b;
    return rez;
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
pair*pushbackP(pair*array, int *size, pair value){
    pair*output = resizeArray(array, pair, *size + 1);
    output[(*size)++] = value;
    return output;
}
int cmpP(const void*pa, const void*pb){
  pair*a=(pair*)pa;
  pair*b=(pair*)pb;
  int diff;
  diff = a->first  - b->first;  if(diff!=0) return diff;
  return a->second - b->second;
}
typedef struct{
	pair*ptr;
	int sz;
}vecp;
vecp newVecP() {
	vecp rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

////////////
int v[4000];

int*smallestRange(int**a, int aSz, int*aColSzs, int*retSz){
  const int n = aSz;
  vecp b=newVecP();
  memset(v, 0, sizeof v);
  for (int i = 0; i < n; ++i) {
    for(int z=0; z<aColSzs[i]; z++){int x = a[i][z];
      b.ptr=pushbackP(b.ptr, &b.sz, newPair(x, i));
    }
  }
  qsort(b.ptr, b.sz, sizeof(pair), cmpP);
  int best = INT_MAX;
  pair ret = newPair(INT_MIN, INT_MAX);
  int cnt = 0;
  for (int i = 0, j = 0; i < b.sz; ++i){
    int x = b.ptr[i].second;
    if (++v[x] == 1){
      cnt++;
    }
    while (cnt == n) {
      if (b.ptr[i].first - b.ptr[j].first < best){
        ret = newPair(b.ptr[j].first, b.ptr[i].first);
        best = ret.second - ret.first;
      }
      int x = b.ptr[j++].second;
      if (--v[x] == 0) {
        cnt--;
      }
    }
  }
 *retSz=2;
  int*rv=malloc(2*sizeof(int));
  rv[0]=ret.first;
  rv[1]=ret.second;
  return rv;
}


