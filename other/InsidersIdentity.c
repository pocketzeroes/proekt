#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;

int cmp(const void * a, const void * b){
  return ( *(int*)a - *(int*)b );
}
int unique(int *a, int len){
	int i, j;
	for (i = j = 0; i < len; i++)
		if (a[i] != a[j]) a[++j] = a[i];
	return j + 1;
}
int lower_bound(int*a, int n, int x){
  int l = 0;
  int h = n;
  while (l < h) {
    int mid = (l + h) / 2;
    if (x <= a[mid]) 
      h = mid;
    else
      l = mid + 1;
  }
  return l;
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
vec newVec(){
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

int main(){
  int n;
  char S[32];
  scanf("%d%s", &n, &S);
  vec state_space = newVec();
  void dfs(int now, int i){
    state_space.ptr = pushback(state_space.ptr, &state_space.sz, now + (1<<i));
    if(i + 1 < strlen(S)){
      if (S[i] == '*')
        dfs(now*2, i+1);
      dfs(now*2+1, i+1);
    }
  }
  dfs(0, 0);
  qsort(state_space.ptr, state_space.sz, sizeof(int), cmp);
  state_space.sz=unique(state_space.ptr, state_space.sz);
  vec patterns = newVec();
  patterns.ptr=pushback(patterns.ptr, &patterns.sz, 0);
  for(int i=0, p=0; S[i]; i++){
    p = p * 2 + (S[i] == '1');
    patterns.ptr=pushback(patterns.ptr, &patterns.sz, p);
  }
  const int DONE = -1;
  int GetNextValidState(int state){
    int len = 31 - __builtin_clz(state);
    for (int i = len; i >= 0; i--){
      if((state&patterns.ptr[i]) == patterns.ptr[i]){
        if(i == strlen(S))
          return DONE;
        else{
          int nxt = (1<<i) + (state & ((1<<i)-1));
          return lower_bound(state_space.ptr, state_space.sz, nxt);
        }
      }
    }
    return 1;
  }
  int add0[state_space.sz];
  int add1[state_space.sz];
  for (int i = 0; i < state_space.sz; i++){
    int state = state_space.ptr[i];
    add0[i] = GetNextValidState(state*2);
    add1[i] = GetNextValidState(state*2+1);
  }
  ll ans = 0;
  ll dp[state_space.sz]; memset(dp, 0, sizeof(dp));
  dp[0] = 1;
  for(int i = 1; i <= n; i++){
    ll dp_next[state_space.sz]; memset(dp_next, 0, sizeof(dp_next));
    for(int j = 0; j < state_space.sz; j++){
      if(add0[j] == DONE)
        ans += dp[j] * (1LL<<(n-i));
      else
        dp_next[add0[j]] += dp[j];
      if(add1[j] == DONE)
        ans += dp[j] * (1LL<<(n-i));
      else
        dp_next[add1[j]] += dp[j];
    }
    ll tmp[state_space.sz];
    memcpy(tmp    , dp     , sizeof(dp));
    memcpy(dp     , dp_next, sizeof(dp));
    memcpy(dp_next, tmp    , sizeof(dp));
  }
  printf("%lld\n", ans);
  return 0;
}
