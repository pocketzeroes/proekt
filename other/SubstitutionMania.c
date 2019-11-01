#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

void swap(int*nums, int i, int j) {
   int t   = nums[i];
   nums[i] = nums[j];
   nums[j] = t;
}
void reverse(int*nums,int start,int end){
    while( start < end) {
        swap(nums, start, end);
        start++;
        end  --;
    }
}

char buff[100001];
char*getln(){
  gets(buff);
  return strdup(buff);
}
char*getstr(){
  int rv = scanf("%s", &buff);
  if(rv!=1)return NULL;
  return strdup(buff);
}

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
/////////////////////////////////
typedef long long ll;
typedef long double ld;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
enum{ N = 12};
enum{ M = 26};
char*v[N];
char adj[N][M];
char dp [M][1<<N][M];
bool pre[M][1<<N][M][N];


bool solve(int s, int g, int bm){
  if(bm==0)
    return s==g;
  if(dp[s][bm][g]!=-1)
    return dp[s][bm][g];
  bool res = false;
  for(int i=0;i<N;i++){
    if(bm&1<<i){
      int ng = adj[i][g];
      if(solve(s,ng,bm^1<<i)){
        res = true;
        pre[s][bm][g][i] = true;
      }
    }
  }
  return dp[s][bm][g] = res;
}
bool dfs(vec*order, int goal[M], int bm){
  if(bm==0)
    return true;
  for(int i=0;i<N;i++){
    if(bm&1<<i){
      bool ok = true;
      for(int j=0;j<M;j++){
        if(goal[j]!=-1){
          ok &= pre[j][bm][goal[j]][i];
        }
      }
      if(ok){
        int nxt[M];
        memset(nxt,-1,sizeof nxt);
        for(int j=0;j<M;j++){
          if(goal[j]!=-1){
            nxt[j] = adj[i][goal[j]];
          }
        }
        if(dfs(order, nxt, bm^1<<i)){
          order->ptr = pushback(order->ptr, &order->sz, i);
          return true;
        }
      }
    }
  }
  return false;
}
int main(){
  char*s=getln();
  char*t=getln();
  int goal[M];
  memset(goal,-1,sizeof goal);
  int m = strlen(s);
  for(int i=0; i<m; i++){
    if(s[i]==' ') 
      continue;
    goal[s[i]-'a'] = t[i]-'a';
  }
  int n;
  scanf("%d", &n);
  for(int i=0; i<n; i++){
    v[i] = getstr();
    for(int j=0;j<M;j++){
      adj[i][v[i][j]-'a'] = j;
    }
  }
  memset(dp,-1,sizeof dp);
  for(int i=0; i<M; i++){
    if(goal[i]!=-1){
      assert(solve(i,goal[i],(1<<n)-1));
    }
  }
  vec order = newVec();
  dfs(&order, goal, (1<<n)-1);
  reverse(order.ptr, 0, order.sz-1);
  for(char*w; (w=getstr())!=NULL;){
    for(int z=0;w[z];z++){char c=w[z];
      for(int q=0; q<order.sz; q++){int i = order.ptr[q];
        c = adj[i][c-'a']+'a';
      }
      putchar(c);
    }
    printf(" ");
  }
  puts("");
  return 0;
}
