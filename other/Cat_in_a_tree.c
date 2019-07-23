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
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
/////////////////////////////

int N,D;
vec*T;
int*opt;
int*optdist;
int*sacrdist;

void DFS(int pos){
  if(T[pos].sz == 0){
    opt     [pos] = 1;
    optdist [pos] = 0;
    sacrdist[pos] = D;
    return;
  }
  int v = T[pos].ptr[0];
  DFS(v);
  if(optdist[v] + 1 >= D) {
    opt     [pos] = opt[v] + 1;
    optdist [pos] = 0;
    sacrdist[pos] = optdist[v] + 1;
  }
  else {
    opt     [pos] = opt[v];
    optdist [pos] = optdist[v] + 1;
    sacrdist[pos] = sacrdist[v] + 1;
  }
  for(int i = 1; i < T[pos].sz; ++i){
    int v = T[pos].ptr[i];
    DFS(v);
    int doo  = optdist[pos] + optdist[v] + 1;
    int mdoo = min(optdist[pos], optdist[v] + 1);
    int dos  = optdist[pos] + sacrdist[v] + 1;
    int mdos = min(optdist[pos], sacrdist[v] + 1);
    int dso  = sacrdist[pos] + optdist[v] + 1;
    int mdso = min(sacrdist[pos], optdist[v] + 1);
    int dss  = sacrdist[pos] + sacrdist[v] + 1;
    int mdss = min(sacrdist[pos], sacrdist[v] + 1);
    if(doo >= D){
      opt     [pos] += opt[v];
      optdist [pos] = mdoo;
      sacrdist[pos] = max(mdos, mdso);
    }
    else if (dos >= D || dso >= D){
      opt[pos] += opt[v] - 1;
      if(dos >= D)
        optdist[pos] = mdos;
      else
        optdist[pos] = 0;
      if(dso >= D)
        optdist[pos] = max(optdist[pos], mdso);
      sacrdist[pos] = mdss;
    }
    else{
      puts("error!");
      exit(0);
    }
  }
}
int main(){
  scanf("%d %d", &N, &D);
  T = calloc(N, sizeof(vec));
  opt      = calloc(N, sizeof(int));
  optdist  = calloc(N, sizeof(int));
  sacrdist = calloc(N, sizeof(int));
  for(int i = 1; i < N; ++i){
    int a;
    scanf("%d", &a);
    T[a].ptr = pushback(T[a].ptr, &T[a].sz, i);
  }
  DFS(0);
  printf("%d\n", opt[0]);
  return 0;
}
