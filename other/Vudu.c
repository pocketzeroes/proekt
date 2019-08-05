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
  double first;
  int    second;
}pair;
pair newPair(double a, int b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
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
enum{ MAXN = 1 << 20};
int n;
double a[MAXN];


int loga[MAXN];

void update (int pos) {
  pos += 10;
  while (pos < MAXN) {
    ++loga[pos];
    pos += pos&-pos;
  }
}
int query (int pos) {
  pos += 10;
  int ret = 0;
  while (pos > 0) {
    ret += loga[pos];
    pos -= pos&-pos;
  }
  return ret;
}
int main(){
  scanf("%d", &n);
  for (int i = 0; i < n; ++i)
    scanf("%lf", &a[i]);
  int p;
  scanf("%d", &p);
  for (int i = 0; i < n; ++i) {
    a[i] -= p;
    if (i > 0)
      a[i] += a[i-1];
  }
  vecp V = newVecP();
  for(int i = 0; i < n; ++i)
    V.ptr = pushbackP(V.ptr, &V.sz, newPair(a[i], i));
  V.ptr = pushbackP(V.ptr, &V.sz, newPair(0, -1));
  qsort(V.ptr, V.sz, sizeof(pair), cmpP);
  int pos = 0;
  ll ans = 0;
  for (int i = 0; i < V.sz; ++i){
    while (pos < i && (V.ptr[i].first - V.ptr[pos].first) >= 0)
      update(V.ptr[pos++].second);
    ans += query(V.ptr[i].second);
  }
  printf("%lld\n", ans);
  return 0;
}
