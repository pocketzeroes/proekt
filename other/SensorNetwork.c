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
//////////////////////////////////
enum{ infinity = 1000000000};
enum{ MAXV     = 350};

typedef struct{
 int a, b, w;
}edge;

edge*pushbackE(edge*array, int *size, edge value){
  edge*output = resizeArray(array, edge, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	edge*ptr;
	int sz;
}vece;
vece newVecE(){
	vece rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

int cmpE(const void*pa, const void*pb){
  edge*e=(edge*)pa;
  edge*f=(edge*)pb;
  return(e->w < f->w)?-1:1;
}
int n;
vece edges;
int parent[MAXV];
int ret, minedge, maxedge, treesize;
int weight[MAXV][MAXV];

int commonancestor(int a, int b){
  bool vis[MAXV];
  for(int i = 0; i < n; i++)
    vis[i] = false;
  int z = a;
  vis[z] = true;
  do{
    z = parent[z];
    if(z >= 0)
      vis[z] = true;
  }
  while(z >= 0 && parent[z] != z);
  int x = b;
  while(x >= 0 && !vis[x] && x != parent[x])
    x = parent[x];
  if(!vis[x])
    return -1;
  else
    return x;
}
void findremove(int a, int b){
  int x = commonancestor(a, b);
  edge light;
  light.w = infinity;
  int y = a;
  while(y != x){
    if(weight[y][parent[y]] < light.w){
      light.a = y;
      light.b = parent[y];
      light.w = weight[y][parent[y]];
    }
    y = parent[y];
  }
  bool inb = false;
  y = b;
  while(y != x){
    if(weight[y][parent[y]] < light.w){
      light.a = y;
      light.b = parent[y];
      light.w = weight[y][parent[y]];
      inb = true;
    }
    y = parent[y];
  }
  if(inb)
    y = b;
  else
    y = a;
  vec v=newVec();
  v.ptr = pushback(v.ptr, &v.sz, y);
  while(y != light.a){
    y = parent[y];
    v.ptr = pushback(v.ptr, &v.sz, y);
  }
  for(int i = v.sz - 1; i > 0; i--)
    parent[v.ptr[i]] = v.ptr[i-1];
  if(inb)
    parent[b] = a;
  else
    parent[a] = b;
  treesize--;
  minedge = infinity;
  for(int i = 0; i < n; i++)
    if(parent[i] != -1 && parent[i] != i)
      minedge = min(minedge, weight[i][parent[i]]);
  return;
}
void process(edge e){
  int x = commonancestor(e.a, e.b);
  if(x != -1)
     findremove(e.a, e.b);
  else if(parent[e.a] >= 0 && parent[e.b] >= 0){
    int y = e.a;
    vec v = newVec();
    v.ptr = pushback(v.ptr, &v.sz, y);
    while(y != parent[y]){
      y = parent[y];
      v.ptr = pushback(v.ptr, &v.sz, y);
    }
    for(int i = v.sz - 1; i > 0; i--)
      parent[v.ptr[i]] = v.ptr[i-1];
    parent[e.a] = e.b;
  }
  else if(parent[e.a] == -1){
    parent[e.a] = e.b;
    if(parent[e.b] == -1)
      parent[e.b] = e.b;
  }
  else
    parent[e.b] = e.a;
  treesize++;
  maxedge = e.w;
  if(treesize == 1)
    minedge = e.w;
  if(treesize == n - 1)
    ret = min(ret, maxedge - minedge);
  return;
}
int main(){
  for(;;){
    int nedges;
    scanf("%d", &n);
    if(!n)
      break;
    scanf("%d", &nedges);
    int x, y, z;
    edge e;
    edges.sz=0;
    for(int i = 0; i < nedges; i++){
      scanf("%d %d %d", &x, &y, &z);
      e.a = x;
      e.b = y;
      e.w = z;
      weight[x][y] = z;
      weight[y][x] = z;
      edges.ptr = pushbackE(edges.ptr, &edges.sz, e);
    }
    qsort(edges.ptr, edges.sz, sizeof(edge), cmpE);
    memset (parent, -1, sizeof(parent));
    ret = infinity;
    treesize = 0;
    minedge = -infinity;
    maxedge =  infinity;
    for(int i = 0; i < nedges; i++)
      process(edges.ptr[i]);
    printf("%d\n", ret);
  }
  return 0;
}
