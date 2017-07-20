#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<stdbool.h>
#include<limits.h>


#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}

typedef struct vecS {
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;// = malloc(sizeof(vec));
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

////////////////////

int t, n, u, v, vst[100005];
vec adj[100005], odd, even;
int leaf, leaf2;

void dfs(int x){
  if (vst[x] & 1)
    odd.ptr = pushback(odd.ptr, &odd.sz ,x);
  else
    even.ptr = pushback(even.ptr, &even.sz ,x);
  if (adj[x].sz == 1)
    leaf = x;
  for(int z=0;z<adj[x].sz;z++){ int nex = adj[x].ptr[z];
    if(!vst[nex]){
      vst[nex] = 1 + vst[x];
      dfs(nex);
    }
  }
}

int main(){
  scanf("%d", &t);
  while (t--){
    scanf("%d", &n);
    odd.sz=0;
    even.sz=0;
    for (int i = (1); i <= (n); i++) 
      adj[i].sz=0, vst[i] = 0;
    for (int i = (0); i <= ((int)(n - 1)-1); i++) {
      scanf("%d %d", &u, &v);
      adj[v].ptr = pushback(adj[v].ptr, &adj[v].sz ,u);
      adj[u].ptr = pushback(adj[u].ptr, &adj[u].sz ,v);
    }
    bool flag = false;
    for (int i = (1); i <= (n); i++) 
     if (adj[i].sz == n - 1) 
      flag = true;
    if (flag) {
      puts("-1");
      continue;
    }
    vst[1] = 1;
    dfs(1);
    if (vst[leaf] & 1) {
      for(int z=0;z<even.sz;z++){ int i = even.ptr[z];
        if (i != adj[leaf].ptr[0]) {
          leaf2 = i;
          break;
        }
      }
      for(int z=0;z<odd.sz;z++){ int i = odd.ptr[z];
        if (i != leaf)
          printf("%d ", i);
      }
      printf("%d %d ", leaf, leaf2);
      for(int z=0;z<even.sz;z++){ int i = even.ptr[z];
        if (i != leaf2)
          printf("%d ", i);
      }
      puts("");
    }
    else {
      for(int z=0;z<odd.sz;z++){ int i = odd.ptr[z];
        if (i != adj[leaf].ptr[0]) {
          leaf2 = i;
          break;
        }
      }
      for(int z=0;z<even.sz;z++){ int i = even.ptr[z];
        if (i != leaf) 
          printf("%d ", i);
      }
      printf("%d %d ", leaf, leaf2);
      for(int z=0;z<odd.sz;z++){ int i = odd.ptr[z];
        if (i != leaf2) 
          printf("%d ", i);
      }
      puts("");
    }
  }
}


















































