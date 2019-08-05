#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

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
#define lo first
#define hi second


enum{ MAXN = 10010};
enum{ MAXK = 110  };

int n, v[MAXN];
vec  e[MAXN];
vecp s[MAXN];
vec  q[MAXK];
bool flag[MAXN][MAXK][MAXK];

void dfs(int x){
  for(int z=0;z<e[x].sz;z++){int y = e[x].ptr[z];
    dfs(y);
  }
  for(int i = 0; i < MAXK; ++i){
    q[i].sz=0;
  }
  for(int z=0;z<e[x].sz;z++){int y = e[x].ptr[z];
    for(int qq=0; qq<s[y].sz; qq++){pair it = s[y].ptr[qq];
      q[it.lo].ptr = pushback(q[it.lo].ptr, &q[it.lo].sz, it.hi);
    }
  }
  for(int lo = MAXK - 1; lo >= 1; --lo){
    if(lo == v[x]){
      for(int o=0; o<MAXK; o++)
        flag[x][lo][o] |= flag[x][lo+1][o];
      flag[x][lo][lo]=1;
    }
    else{
      for(int z=0;z<q[lo].sz;z++){int hi = q[lo].ptr[z];
        if (hi < v[x] || lo > v[x]) {
          for(int o=0; o<MAXK; o++)
            flag[x][lo][o] |= flag[x][hi+1][o];
          flag[x][lo][hi]=1;
        }
      }
    }
    for(int hi = MAXK - 1; hi >= lo; --hi){
      if (flag[x][lo][hi] && v[x] >= lo && v[x] <= hi){
        s[x].ptr = pushbackP(s[x].ptr, &s[x].sz, newPair(lo, hi));
      }
    }
  }
}
void init(){
  scanf("%d",&n);
  for(int i = 0; i < n; ++i)
    scanf("%d", &v[i]);
  for(int i = 0; i < n - 1; ++i){
    int a, b;
    scanf("%d %d", &a, &b);
    --a, --b;
    e[a].ptr = pushback(e[a].ptr, &e[a].sz, b);
  }
}
void solve(){
  dfs(0);
  printf("%d\n", s[0].sz);
}
int main(){
  init();
  solve();
  return 0;
}
