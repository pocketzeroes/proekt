#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define swap(a,b) do{ __typeof(a) tp; tp = a; a = b; b = tp; }while(0)

//typedef struct DijkstraHeap{
  int*hp;
  int*place;
  int size;
  char*visited;
  int*val;
  void mmalloc(int N){
    hp      = (int*)malloc(N*sizeof(int));
    place   = (int*)malloc(N*sizeof(int));
    visited = (char*)malloc(N*sizeof(char));
    val     = (int*)malloc(N*sizeof(int));
  }
  void mfree(){
    free(hp);
    free(place);
    free(visited);
    free(val);
  }
  void init(int N){
    int i;
    size = 0;
    for(i=(0);i<(N);i++){
      place[i]=-1;
    }
    for(i=(0);i<(N);i++){
      visited[i]=0;
    }
  }
  void up(int n){
    int m;
    while(n){
      m=(n-1)/2;
      if(val[hp[m]]<=val[hp[n]]){
        break;
      }
      swap(hp[m],hp[n]);
      swap(place[hp[m]],place[hp[n]]);
      n=m;
    }
  }
  void down(int n){
    int m;
    for(;;){
      m=2*n+1;
      if(m>=size){
        break;
      }
      if(m+1<size&&val[hp[m]]>val[hp[m+1]]){
        m++;
      }
      if(val[hp[m]]>=val[hp[n]]){
        break;
      }
      swap(hp[m],hp[n]);
      swap(place[hp[m]],place[hp[n]]);
      n=m;
    }
  }
  void change(int n, int v){
    if(visited[n]||(place[n]>=0&&val[n]<=v)){
      return;
    }
    val[n]=v;
    if(place[n]==-1){
      place[n]=size;
      hp[size++]=n;
      up(place[n]);
    }
    else{
      up(place[n]);
    }
  }
  int pop(void){
    int res=hp[0];
    place[res]=-1;
    size--;
    if(size){
      hp[0]=hp[size];
      place[hp[0]]=0;
      down(0);
    }
    visited[res]=1;
    return res;
  }
//};

int X;
int Y;
int A[100][100];
int dis[100][100];
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

int minCost(int**grid, int gridSz, int*grid0sz){
  int i, mask, sx, sy, sc, nx, ny, nc, d;
  int dm;
  X = gridSz;
  Y = grid0sz[0];
  for(i=0; i<X; i++){
    int j;
    for(j=0; j<Y; j++)
      A[i][j] = grid[i][j] - 1;
  }
  dm = Y;
  mmalloc(X*Y);
  init(X*Y);
  change(0,0);
  while(size){
    mask = pop();
    sx = mask / dm;
    sy = mask % dm;
    sc = val[mask];
    if(sx==X-1 && sy==Y-1)
      return sc;
    for(d=0; d<4; d++){
      nx = sx + dx[d];
      ny = sy + dy[d];
      if(A[sx][sy]==d)
        nc = sc +0;
      else
        nc = sc +1;
      if(nx < 0 || ny < 0 || nx >= X || ny >= Y)
        continue;
      change(nx*dm+ny, nc);
    }
  }
  return-1;
}
