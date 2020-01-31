#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#include<float.h>

typedef struct{
  double first;
  int    second;
}pdi;
pdi newpdi(double a, int b){
  return(pdi){a, b};
}
int cmpPdi(pdi a, pdi b){
  if(a.first  != b.first) return(a.first  < b.first )?-1:1;
  if(a.second != b.second)return(a.second < b.second)?-1:1;
  return 0;
}
pdi maxP(pdi a, pdi b){return cmpPdi(a,b)>0?a:b;}

#define ff first_first
#define fs first_second
#define se second

#define pb(zpv, zvv) zpv.ptr = pushback(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

//////////////////////////
double A, B, cur;
typedef struct{
  double first_first,
         first_second;
  int    second;
}obj;
obj*in;

int cmpO(const void*pa, const void*pb){
  obj*a = (obj*)pa;
  obj*b = (obj*)pb;
  if(a->ff != b->ff) return(a->ff < b->ff)?-1:1;
  if(a->fs != b->fs) return(a->fs < b->fs)?-1:1;
  if(a->se != b->se) return(a->se < b->se)?-1:1;
  return 0;
}

int N, nex;
vec ans;

void solve(){
  nex = 0;
  ans.sz=0;
  scanf("%d", &N);
  in = calloc(N, sizeof(obj));
  for(int i=0; i<N; i++){
    scanf("%lf %lf", &in[i].first_first, &in[i].first_second);
    in[i].second = i;
  }
  qsort(in, N, sizeof(obj), cmpO);
  pdi mx = (pdi){-DBL_MAX, -1};
  while(nex < N && in[nex].first_first <= A){
    mx = maxP(mx, (pdi){in[nex].first_second, in[nex].second});
    nex++;
  }
  if(nex == 0){
    puts("impossible");
    return;
  }
  pb(ans, mx.second);
  while(mx.first < B){
    cur = mx.first;
    while(nex < N && in[nex].first_first <= cur){
      mx = maxP(mx, (pdi){in[nex].first_second, in[nex].second});
      nex++;
    }
    if(mx.first == cur){
      puts("impossible");
      return;
    }
    pb(ans, mx.second);
  }
  printf("%d\n", ans.sz);
  for(int z=0; z<ans.sz; z++)
    printf("%d ", ans.ptr[z]);
  puts("");
}
int main(){
  while(scanf("%lf %lf", &A, &B)==2)
    solve();
  return 0;
}
