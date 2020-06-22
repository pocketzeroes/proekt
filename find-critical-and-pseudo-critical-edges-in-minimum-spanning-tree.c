#pragma GCC optimize "-O3"
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
int**newmat(int x, int y){
  int**rv = calloc(x, sizeof(int*));
  for(int i=0; i<x; i++)
    rv[i] = calloc(y, sizeof(int));
  return rv;
}
void freemat(int**m, int x){
  for(int i=0; i<x; i++)
    free(m[i]);
  free(m);
  m = NULL;
}

////////////////////////
int m;
enum{INF=0x3f3f3f3f};
int**edges;//[200][4];
int*uf;

int find(int x){
  if(x==uf[x])
    return x;
  else{
    uf[x] = find(uf[x]);
    return uf[x];
  }
}
int mst(int n, int unused){
  for(int i=0; i<n; i++)
    uf[i]=i;
  int cnt=0;
  int ans=0;
  for(int i=0; i<m; i++){
    if(i==unused)
      continue;
    int u=find(edges[i][0]),
        v=find(edges[i][1]);
    if(u==v)
      continue;
    uf[u]=v;
    cnt++;
    ans+=edges[i][2];
  }
  return cnt==n-1?ans:INF;
}
int mst2(int n, int choose){
  for(int i=0; i<n; i++)
    uf[i]=i;
  int cnt=1;
  int ans =  edges[choose][2];
  int u=find(edges[choose][0]),
      v=find(edges[choose][1]);
  uf[u]=v;
  for(int i=0; i<m; i++){
    int u=find(edges[i][0]),
        v=find(edges[i][1]);
    if(u==v)
      continue;
    uf[u]=v;
    cnt++;
    ans+=edges[i][2];
  }
  return cnt==n-1?ans:INF;
}
typedef int* intp;

int cmp(const void*pa, const void*pb){
  intp*aa=(intp*)pa;
  intp*bb=(intp*)pb;
  int*a = *aa;
  int*b = *bb;
  return(a[2]<b[2])?-1:1;
}

int**findCriticalAndPseudoCriticalEdges(int n, int**edj, int esz, int*edges0sz, int*rsz, int**csz){
  edges = newmat(200, 4);
  m = esz;
  for(int i=0; i<m; i++){
    edges[i][0] = edj[i][0];
    edges[i][1] = edj[i][1];
    edges[i][2] = edj[i][2];
    edges[i][3] = i;
  }
  qsort(edges, m, sizeof(intp), cmp);
  uf = calloc(n, sizeof(int));
  int mi = mst(n, -1);
  vec ans1 = newVec();
  vec ans2 = newVec();
  for(int i=0; i<m; i++){
    int unuse = mst (n, i),
        use   = mst2(n, i);
    if     (unuse==mi&&use==mi)
      pb(ans2, edges[i][3]);
    else if(unuse> mi&&use==mi)
      pb(ans1, edges[i][3]);
  }
  free(uf);
  freemat(edges, 200);
  int**ans=calloc(2, sizeof(int*));
  ans[0]=ans1.ptr;
  ans[1]=ans2.ptr;
  int*cols=calloc(2, sizeof(int));
  cols[0]=ans1.sz;
  cols[1]=ans2.sz;
 *csz=cols;
 *rsz=2;
  return ans;
}

// int main(){
//   return 0;
// }
