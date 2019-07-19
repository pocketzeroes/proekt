#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
inline int min(int a,int b){return a<b?a:b;}

char buff[1000000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}

typedef long long ll;
typedef struct{
  ll first;
  ll second;
}pair;
pair newPair(ll a, ll b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}
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

////////////////////

inline pair do_or(pair l, pair r){
  return (pair){l.first|r.first, l.second|r.second};
}
bool solve(int i, int N, int j, int s, pair msk, pair*bm, vec*sol){
  if (j == s){
    int c = __builtin_popcountll(msk.first)+
            __builtin_popcountll(msk.second);
    return(c == N);
  }
  if(i == -1)
    return false;
  sol->ptr = pushback(sol->ptr, &sol->sz, i);
  if (solve(i-1, N, j+1, s, do_or(msk, bm[i]), bm, sol))
    return true;
  sol->sz--;
  return solve(i-1, N, j, s, msk, bm, sol);
}
int main() {
  int N, tcase = 0;
  while(scanf("%d", &N)==1){
    ++tcase;
    bool B[N][N]; memset(B, 0, sizeof(B));
    pair bm[N];   memset(bm, 0, sizeof(bm));
    for (int i = 0; i < N; ++i){
      char*ss = getstr();
      for (int j = 0; j < N; ++j)
        B[i][j] = ss[j] == '1';
      B[i][i] = true;
      for (int j = 0; j < min(60, N); ++j)
        if (B[i][j])
          bm[i].first |= (1LL<<j);
      for (int j = 60; j < N; ++j)
        if (B[i][j])
          bm[i].second |= (1LL<<(j-60));
    }
    vec sol=newVec();
    bool f = false;
    for (int s = 1; !f && s <= 6; ++s){
      if (solve(N - 1, N, 0, s,(pair){0LL, 0LL}, bm, &sol))
        f = true;
    }
    if (!f){
      bool taken[N]; memset(taken, 0, sizeof(taken));
      for(int r=1; r<=7; ++r){
        int sz = 0, 
            id = -1;
        for(int i=0; i<N; ++i){
          int this_sz=0;
          for(int j=0; j<N; ++j){
            if(B[i][j] && !taken[j])
              ++this_sz;
          }
          if(this_sz > sz){
            sz = this_sz;
            id = i;
          }
        }
        sol.ptr = pushback(sol.ptr, &sol.sz, id);
        for(int i=0; i<N; ++i)
          if(B[id][i])
            taken[i] = true;
      }
    }
    printf("Case %d: %d", tcase, sol.sz);
    for(int i=0; i< sol.sz; ++i){
      printf(" %d", 1+sol.ptr[i]);
    }
    puts("");
  }
  return 0;
}
