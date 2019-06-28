#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
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

int N,M;
int*u;
vec s;
vec*c1;
vec*c2;

void dfs1 (int n){
  if (u[n])
    return;
  u[n]=-1;
  for (int i=0; i<c1[n].sz; i++)
    dfs1(c1[n].ptr[i]);
  s.ptr = pushback(s.ptr, &s.sz, n);
}
void dfs2(int n, int mark){
  if(u[n]!=-1)
    return;
  u[n] = mark;
  for (int i=0; i<c2[n].sz; i++)
    dfs2(c2[n].ptr[i], mark);
}
int main (){
  int  runs;
  scanf("%d", &runs);
  while(runs--){
    scanf("%d %d", &N, &M);
    c1=calloc(N, sizeof(vec));
    c2=calloc(N, sizeof(vec));
    for(int i=0; i<M; i++){
      int a,b;
      scanf("%d %d", &a, &b);
      a--, b--;
      c1[a].ptr = pushback(c1[a].ptr, &c1[a].sz, b);
      c2[b].ptr = pushback(c2[b].ptr, &c2[b].sz, a);
    }
    s.sz=0;
    int mark=0;
    u = calloc(N, sizeof(int));
    for(int i=0; i<N; i++)
      dfs1(i);
    for(int i=N-1; i>=0; i--)
      if(u[s.ptr[i]]==-1)
        dfs2(s.ptr[i], mark++);
    if(mark==1){
      puts("0");
      continue;
    }
    int  nin[mark]; memset( nin,0, sizeof( nin));
    int nout[mark]; memset(nout,0, sizeof(nout));
    for (int i=0; i<N; i++){
      for (int j=0; j<c1[i].sz; j++){
        if (u[i]!=u[c1[i].ptr[j]]){
          nout[u[i]]++;
          nin [u[c1[i].ptr[j]]]++;
        }
      }
    }
    int nin0 =0,
        nout0=0;
    for(int i=0; i<mark; i++){
      if(nin[i]==0)
        nin0++;
      if(nout[i]==0)
        nout0++;
    }
    printf("%d\n", max(nin0,nout0) );
  }
  return 0;
}
