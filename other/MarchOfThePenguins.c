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
/////////////////////
enum{ MAXN = 100};

typedef struct{
  int penguins;
  int maxjump;
  int X, Y;
}Island;

double jump;
int totalPenguins;
Island*islands;
int N;
int dest;
int  flows  [MAXN][MAXN], iflows[MAXN];
bool canjump[MAXN][MAXN];
bool visit  [MAXN*2];

int augmentFlow(int src){
  if(src == dest)
    return 1;
  visit[src] = 1;
  if(src < N){
    if(!visit[src+N] && iflows[src] < islands[src].maxjump && augmentFlow(src+N)){
      iflows[src] ++;
      return 1;
    }
    for(int i=0;i<N;i++)
      if(canjump[i][src] && !visit[i+N] && flows[i][src] > 0 && augmentFlow(i+N)){
        flows[i][src]--;
        return 1;
      }
  }
  else{
    src -= N;
    if(!visit[src] && iflows[src] > 0 && augmentFlow(src)){
      iflows[src] --;
      return 1;
    }
    for(int i=0;i<N;i++)
      if(!visit[i] && canjump[src][i] && augmentFlow(i)){
        flows[src][i] ++;
        return 1;
      }
  }
  return 0;
}
int possible(int _dest){
  dest = _dest;
  int n = 0;
  memset(flows, 0, sizeof(flows));
  memset(iflows, 0, sizeof(iflows));
  memset(visit, 0, sizeof(visit));   
  for(int i=0;i<N;i++){
    int islandCount = islands[i].penguins;
    while(islandCount-- && augmentFlow(i)){
      n++;
      memset(visit, 0, sizeof(visit));
    }
    if(islandCount > 0) 
      break;
  }
  return n == totalPenguins;
}
void initJumps(){
  double d2 = jump * jump;
  for(int i=0;i<N;i++)
    for(int j=i;j<N;j++){
      int distance = (islands[i].X - islands[j].X) * (islands[i].X- islands[j].X) + (islands[i].Y- islands[j].Y) * (islands[i].Y - islands[j].Y);
      canjump[i][j] = canjump[j][i] = distance < d2;
    }
}
int main(){
  int runs=1;
//  scanf("%d", &runs);
  while(runs--){
    scanf("%d %lf", &N, &jump);
    islands = calloc(N, sizeof(Island));
    totalPenguins = 0;
    for(int i=0;i<N;i++){
      int X, Y, penguins, maxjump;
      scanf("%d %d %d %d", &X, &Y, &penguins, &maxjump);
      islands[i] = (Island){penguins, maxjump, X, Y};
      totalPenguins += penguins;
    }
    vec poss = newVec();
    initJumps();
    for(int i=0;i<N;i++)
      if(possible(i))
        poss.ptr = pushback(poss.ptr, &poss.sz, i);
    if(poss.sz == 0)
      printf("-1\n");
    else
      for(int i=0;i<poss.sz;i++){
        printf("%d", poss.ptr[i]);
        if(i == poss.sz-1)
          printf("\n");
        else
          printf(" ");
      }
  }
  return 0;
}
