#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ INF   = 2000000000};
enum{ MAX   = 310};
enum{ MAX_N = (MAX*MAX*2)};
enum{ MAX_C = 101000};

typedef struct{
  int dest, capacity, reversed_index;
}edge;
edge newedge(int a, int b, int c){
  return(edge){a,b,c};
}
#define pb(zpv, zvv) zpv.ptr = pushbackE(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
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

vece s[MAX_N];
int  b[MAX_N],next_b;
int  current_t,current_c;
int  R,C,t[MAX][MAX],r,c;

void add_edge(int x, int y, int c){
  pb(s[x], newedge(y, c, s[y].sz));
  pb(s[y], newedge(x, 0, s[x].sz-1));
}
bool dfs(int x){
  b[x]=next_b;
  for(int i=0; i<s[x].sz; i++){
    if(s[x].ptr[i].capacity>=current_c &&
      (s[x].ptr[i].dest==current_t ||
      (b[s[x].ptr[i].dest]<next_b && dfs(s[x].ptr[i].dest)))){
      s[x].ptr[i].capacity-=current_c;
      s[s[x].ptr[i].dest].ptr[s[x].ptr[i].reversed_index].capacity += current_c;
      return true;
    }
  }
  return false;
}
int max_flow(int ss, int t){
  int ans=0;
  current_t=t;
  current_c=MAX_C;
  while (current_c){
    next_b++;
    while(dfs(ss)){
      next_b++;
      ans+=current_c;
    }
    current_c>>=1;
  }
  return ans;
}
int main(){
	scanf("%d %d", &R, &C);
	for(int i=0;i<R;i++)
    for(int j=0;j<C;j++)
      scanf("%d",&t[i][j]);
	scanf("%d %d",&r,&c);
	int source= r*C+c,
      sink  = 2*R*C;
	for(int i=0;i<R;i++){
    for(int j=0;j<C;j++){
      add_edge(i*C+j,R*C+i*C+j,t[i][j]);
      if(i)add_edge(R*C+i*C+j,(i-1)*C+j,MAX_C);
      if(j)add_edge(R*C+i*C+j,i*C+j-1,MAX_C);
      if(i+1<R)add_edge(R*C+i*C+j,(i+1)*C+j,MAX_C);
      if(j+1<C)add_edge(R*C+i*C+j,i*C+j+1,MAX_C);
      if(!i||!j||i+1==R||j+1==C)add_edge(R*C+i*C+j,sink,MAX_C);
    }
  }
	printf("%d\n", max_flow(source, sink));
  return 0;
}
