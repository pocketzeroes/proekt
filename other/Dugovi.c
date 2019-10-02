#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

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
/////////////////////

enum{ INF = 1 << 30};
enum{ MAXN = 300000};

int N, C;
pair nxt[MAXN];
#define who first
#define amount second
vec prev[MAXN];

int  seen  [MAXN];
bool ignore[MAXN];
vec  cycle [MAXN];
int ret;
int money[MAXN];

void find_cycles(){
  for (int i = 1; i <= N; ++i) {
    int node = i;
    if (!seen[node]) {
      for (; !seen[node]; node = nxt[node].who)
        seen[node] = i;
      if (seen[node] != i)
        continue;
      for (; !ignore[node]; node = nxt[node].who){
        ignore[node] = 1;
        pb(cycle[C], node);
      }
      C++;
    }
  }
}
void solve(int node){
  if(ignore[node])
    return;
  ignore[node] = 1;
  for(int i = 0; i < prev[node].sz; ++i)
    solve(prev[node].ptr[i]);
  money[nxt[node].who] += nxt[node].amount;
  ret -= fmin(money[node] - nxt[node].amount, 0);
}
void solve_outside_cycles(){
  for(int i = 1; i <= N; ++i)
    solve(i);
}
void solve_cycles(){
  for (int c = 0; c < C; ++c) {
    int min_cost = INF, start = -1;
    for (int i = 0; i < cycle[c].sz; ++i) {
      int cost = -fmin(money[cycle[c].ptr[i]] - nxt[cycle[c].ptr[i]].amount, 0);
      if (cost < min_cost) {
        min_cost = cost;
        start = cycle[c].ptr[i];
      }
    }
    ret += min_cost;
    money[nxt[start].who] += nxt[start].amount;
    for (int node = nxt[start].who; node != start; node = nxt[node].who) {
      money[nxt[node].who] += nxt[node].amount;
      ret -= fmin(money[node] - nxt[node].amount, 0);
    }
  }
}
int main(){
  scanf("%d", &N);
  for (int i = 1; i <= N; ++i) {
    scanf("%d %d", &nxt[i].who, &nxt[i].amount);
    pb(prev[nxt[i].who], i);
  }
  find_cycles();
  solve_outside_cycles();
  solve_cycles();
  printf("%d\n", ret);
  return 0;
}
