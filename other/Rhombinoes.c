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
///////////////////
enum{ MAXN = 1005};
enum{ MAXW = 105 };
enum{ MAXH = 105 };

vec  E    [MAXN];
int  match[MAXN];
bool vis  [MAXN];
bool is_dead[MAXW][MAXH];

bool dfs(int i){
  if (vis[i])
    return false;
  vis[i] = true;
  int numE = E[i].sz;
  for(int x=0;x<numE;++x){ int j = E[i].ptr[x];
    if (match[j] < 0 || dfs(match[j]))
      return(match[i]=j,match[j]=i,true);
  }
  return false;
}
int bip_match(int N){
  memset(match,-1,sizeof(match));
  int ans = 0;
  for(int i=0;i<N;++i){
    if(match[i] < 0){
      memset(vis,0,sizeof(vis));
      ans += dfs(i);
    }
  }
  return ans;
}
void add_edge(int i, int j){
  E[i].ptr = pushback(E[i].ptr, &E[i].sz, j);
  E[j].ptr = pushback(E[j].ptr, &E[j].sz, i);
}
int main(){
  int W, H, K, x, y;
  scanf("%d %d %d", &W, &H, &K);
  memset(is_dead, 0, sizeof(is_dead));
  for(int q=0; q<K; ++q){
    scanf("%d %d", &x, &y);
    is_dead[x][y] = true;
  }
  int x2, y2;
  for(int x=0; x<W; ++x){
    for(int y=0; y<H; ++y){
      if(is_dead[x][y])
        continue;
      if((((((x)+(y))%2) == 1) && ((y)<(H-1)))){
        x2 = x;
        y2 = y+1;
        if(!is_dead[x2][y2])
          add_edge(((y)*W + (x)), ((y2)*W + (x2)));
      }
      if(((x)<(W-1))){
        x2 = x+1;
        y2 = y;
        if(!is_dead[x2][y2])
          add_edge(((y)*W + (x)), ((y2)*W + (x2)));
      }
    }
  }
  int ans = bip_match(W*H);
  printf("%d\n", ans);
  return 0;
}
