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

typedef struct{
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


int getbit(int s, int i){
    return (s >> i) & 1;
}
int onbit(int s, int i){
    return s | ((int)(1) << i);
}
int offbit(int s, int i){
    return s & (~((int)(1) << i));
}
int cntbit(int s){
    return __builtin_popcount(s);
}

int test;
ll f[1 << 20], F[22], a[22][10005];
int n, m, q;

void sol(){
    memset(f, 0, sizeof(f));
    scanf("%d %d %d", &n, &m, &q);
    for(int i = 0; i < (n); ++i)
        for(int j = 0; j < (m); ++j)
            scanf("%lld", &a[i][j]);
    memset(f, 0, sizeof(f));
    memset(F, 0, sizeof(F));
    ll RR = 0;
    for(int j = 0; j < (m); ++j){
        vecp V=newVecP();
        for(int i = 0; i < (n); ++i)
            V.ptr = pushbackP(V.ptr, &V.sz, newPair(a[i][j], i));
        qsort(V.ptr, V.sz, sizeof(pair), cmpP);
        ll Max = V.ptr[n - 1].first;
        RR += Max;
        int mask = 0;
        for(int i = n - 1; i > 0; i--){
            mask = onbit(mask, V.ptr[i].second);
            f[mask] += V.ptr[i].first - V.ptr[i - 1].first;
        }
    }
    for(int i = 0; i < (n); ++i)
        for(int mask = 0; mask < (1 << n); ++mask)
            if(getbit(mask, i))
                f[mask] += f[offbit(mask, i)];
    for(int mask = 0; mask < (1 << n); ++mask)
        F[n - cntbit(mask)] = max(F[n - cntbit(mask)], f[mask]);
    for(int iq = 0; iq < (q); ++iq){
        int u;
        scanf("%d", &u);
        printf("%lld\n", RR - F[u]);
    }
}
int main(){
    scanf("%d", &test);
    for(int itest = (1); itest <= (test); ++itest)
        sol();
}
