#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
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

vec adj[300000];
int val[300000];
int cnt[600000];
bool ok;

void prop(int v, int c){
  if (val[v] != -1){
    ok &= val[v] == c;
    return;
  }
  val[v] = c;
  for(int z=0;z<adj[v].sz;z++){int w = adj[v].ptr[z];
    prop(w, c^1);
  }
}
int main(){
  int n, m;
  scanf("%d %d", &n, &m);
  memset(val, -1, sizeof(val));
  ok = true;
  for(int i = 0; ok && i < m; ++i){
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    if(c == 2){
      prop(a, 1);
      prop(b, 1);
    }
    else if(c == 0){
      prop(a, 0);
      prop(b, 0);
    }
    else{
      adj[a].ptr = pushback(adj[a].ptr, &adj[a].sz, b);
      adj[b].ptr = pushback(adj[b].ptr, &adj[b].sz, a);
    }
  }
  for(int i = 1; ok && i <= n; ++i){
    if(val[i] != -1){
      for(int z=0;z<adj[i].sz;z++){int w = adj[i].ptr[z];
        prop(w, val[i]^1);
      }
    }
  }
  int cmp = 2;
  for(int i = 1; ok && i <= n; ++i){
    if(val[i] == -1){
      prop(i, cmp);
      cmp += 2;
    }
  }
  if(!ok){
    printf("impossible\n");
  }
  else{
    memset(cnt, 0, sizeof(cnt));
    for(int i = 1; i <= n; ++i){
      ++cnt[val[i]];
    }
    int res = cnt[1];
    for(int t = 2; t < cmp; t += 2){
      res += min(cnt[t], cnt[t+1]);
    }
    printf("%d\n", res);
  }
  return 0;
}
