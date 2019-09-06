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

enum{ MAXN = 10000};
vec gph[MAXN];
bool seen[MAXN];
int n;

bool is_nbr(int a, int b){
  for(int z=0;z<gph[a].sz;z++){int v = gph[a].ptr[z];
    if(v == b)
      return true;
  }
  return false;
}
bool testvs(int a, int b){
  bool adj = is_nbr (a, b);
  int ncom = 0;
  for(int z=0;z<gph[a].sz;z++){int v = gph[a].ptr[z];
    if(is_nbr (b, v))
      ncom++;
  }
  if(adj)
    return ncom == 0;
  return ncom <= 1;
}
bool test_component(int from){
  vec wl  =newVec();
  vec deg3=newVec();
  int a, b;
  pb(wl, from);
  seen[from] = true;
  while(wl.sz>0){
    a = wl.ptr[wl.sz-1];
    wl.sz--;
    if(gph[a].sz == 3)
      pb(deg3, a);
    for(int z=0;z<gph[a].sz;z++){int v = gph[a].ptr[z];
      if(!seen[v]){
        seen[v] = true;
        pb(wl, v);
      }
    }
  }
  if(deg3.sz >= 5)
    return true;
  for(a = 0; a < deg3.sz; a++)
    for(b = a + 1; b < deg3.sz; b++)
      if(testvs(deg3.ptr[a], deg3.ptr[b]))
        return true;
  return false;
}
bool good_tree(){
  int i;
  for(i = 0; i < n; i++)
    if(gph[i].sz >= 4)
      return true;
  for(i = 0; i < n; i++)
    seen[i] = false;
  for(i = 0; i < n; i++)
    if(!seen[i] && gph[i].sz == 3 && test_component(i))
      return true;
  return false;
}
int main(){
  int m, i, f, t;
  while(scanf ("%d%d", &n, &m) == 2){
    for(i = 0; i < m; i++){
      scanf("%d%d", &f, &t);
      f--, t--;
      pb(gph[f], t);
      pb(gph[t], f);
    }
    printf("%s\n", good_tree() ? "YES" : "NO");
    for(i = 0; i < n; i++)
      gph[i].sz=0;
  }
  return 0;
}
