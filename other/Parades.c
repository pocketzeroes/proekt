#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

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
///////////////////////

enum{ N = 1000};
enum{ D = 10  };
int n;
bool graph[N][N], 
     pairs[N][N];
vec  up   [N];
bool local[D][D];
int  matching[1 << D];
int  lowbit  [1 << D];

int dfs(int u, int f){
  int result = 0;
  vec sons = newVec();
  for(int v=0; v<n; ++v){
    if(graph[u][v] && v != f){
      result += dfs(v, u);
      sons.ptr = pushback(sons.ptr, &sons.sz, v);
    }
  }
  for(int i=0; i<sons.sz; ++i){
    for(int z=0;z<up[sons.ptr[i]].sz;z++){int a = up[sons.ptr[i]].ptr[z];
      if(pairs[u][a]){
        result++;
        up[sons.ptr[i]].sz=0;
        break;
      }
    }
  }
  for(int i = 0; i < sons.sz; ++i){
    for(int j = i + 1; j < sons.sz; ++j){
      local[i][j] = false;
      for(int z=0;z<up[sons.ptr[i]].sz;z++){int a = up[sons.ptr[i]].ptr[z];
        for(int z1=0;z1<up[sons.ptr[j]].sz;z1++){int b = up[sons.ptr[j]].ptr[z1];
          if(pairs[a][b])
            local[i][j] = true;
        }
      }
    }
  }
  matching[0] = 0;
  for(int m = 1; m < (1 << sons.sz); ++m){
    int a = lowbit[m];
    matching[m] = matching[m - (1 << a)];
    for(int b = a + 1; b < sons.sz; ++b){
      if(((m >> b) & 1) && local[a][b])
        matching[m] = max(matching[m], 1 + matching[m - (1 << a) - (1 << b)]);
    }
  }
  result += matching[(1 << sons.sz) - 1];
  vec tmpv = newVec();
  tmpv.ptr = pushback(tmpv.ptr, &tmpv.sz, u);
  up[u] = tmpv;
  for(int i = 0; i < sons.sz; ++i){
    if(matching[(1 << sons.sz) - 1] == matching[(1 << sons.sz) - 1 - (1 << i)]){
      for(int z=0;z<up[sons.ptr[i]].sz;z++){int x = up[sons.ptr[i]].ptr[z];
        up[u].ptr = pushback(up[u].ptr, &up[u].sz, x);
      }
    }
  }
  return result;
}
int main(){
  for(int i = 1; i < (1 << D); ++i)
    lowbit[i] = (i & 1) ? 0 : (1 + lowbit[i >> 1]);
  int Z;
  scanf("%d", &Z);
  while(Z--){
    scanf("%d", &n);
    for(int i = 0; i < n; ++i)
      for(int j = 0; j < n; ++j)
        graph[i][j] = pairs[i][j] = false;
    for(int i=0; i<n-1; ++i){
      int a, b;
      scanf("%d %d", &a, &b);
      --a, --b;
      graph[a][b] = graph[b][a] = true;
    }
    int m;
    scanf("%d", &m);
    while(m--){
      int a, b;
      scanf("%d %d", &a, &b);
      --a, --b;
      pairs[a][b] = pairs[b][a] = true;
    }
    printf("%d\n", dfs(0, -1) );
  }
  return 0;
}
