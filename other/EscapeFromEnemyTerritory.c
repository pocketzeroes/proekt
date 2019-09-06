#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

int**newmat(int x, int y){
  int**rv = calloc(x, sizeof(int*));
  for(int i=0;i<x;i++)
    rv[i] = calloc(y, sizeof(int));
  return rv;
}
void freemat(int**m, int x){
  for(int i=0; i<x; i++)
    free(m[i]);
  free(m);
  m = NULL;
}

#define return1 assert(!"Error");
const int infty = 999999;
const int dx[4] = { 1, 0,-1, 0 };
const int dy[4] = { 0, 1, 0,-1 };
enum{ maxn = 10000};
enum{ maxs = 1000 };
int N, X, Y;
int pos[maxn+2][2];
int sep[maxs+1][maxs+1];
int best[maxs+1][maxs+1][2];
int min(int a, int b) { if ( a<b ) return a; return b; }

void bfs_fillsep(){
  int**que=newmat((maxs+1)*(maxs+1),2);

  int first, end;
  int x, y, x1, y1, d;
  for(x=0; x<X; x++)
    for(y=0; y<Y; y++)
      sep[x][y] = infty;
  first = 0;
  for(end=0; end<N; end++) {
    x = que[end][0] = pos[end+2][0];
    y = que[end][1] = pos[end+2][1];
    sep[x][y] = 0;
  }
  while ( first<end ) {
    x = que[first][0];
    y = que[first][1];
    first++;
    for(d=0; d<4; d++) {
      x1 = x+dx[d];
      y1 = y+dy[d];
      if ( x1<0 || x1>=X || y1<0 || y1>=Y )
        continue;
      if ( sep[x][y]+1<sep[x1][y1] ) {
        sep[x1][y1] = sep[x][y]+1;
        que[end][0] = x1;
        que[end][1] = y1;
        end++;
      }
    }
  }
  freemat(que, (maxs+1)*(maxs+1));
}
int bfs_minsepdist(int trysep){
  int**dist = newmat(maxs, maxs);
  int**que  = newmat(maxs*maxs, 2);
  int first, end;
  int x, y, x1, y1, d;
  for(x=0; x<X; x++)
    for(y=0; y<Y; y++)
      dist[x][y] = infty;
  first = 0;
  end = 1;
  x = que[0][0] = pos[0][0];
  y = que[0][1] = pos[0][1];
  dist[x][y] = 0;
  if ( sep[x][y]<trysep )
    return infty;
  while ( first<end ) {
    x = que[first][0];
    y = que[first][1];
    first++;
    for(d=0; d<4; d++) {
      x1 = x+dx[d];
      y1 = y+dy[d];
      if ( x1<0 || x1>=X || y1<0 || y1>=Y )
        continue;
      if ( sep[x1][y1]>=trysep && dist[x][y]+1<dist[x1][y1] ) {
        dist[x1][y1] = dist[x][y]+1;
        que[end][0] = x1;
        que[end][1] = y1;
        end++;
      }
    }
  }
  int rv = dist[pos[1][0]][pos[1][1]];
  freemat(dist, maxs);
  freemat(que , maxs*maxs);
  return rv;
}
int main(){
  int run, nruns;
  int i, j;
  int x, y;
  int sepmin, sepmid, sepmax;
  nruns = 1;
  for(run=1; run<=nruns; run++) {
    scanf("%d %d %d", &N, &X, &Y);
    if ( N<1 || N>maxn )
      return1;
    if ( X<1 || X>maxs )
      return1;
    if( Y<1 || Y>maxs)
      return1;
    for(i=0; i<N+2; i++){
      scanf("%d %d", &pos[i][0], &pos[i][1]);
      if( pos[i][0]<0 || pos[i][0]>X || pos[i][1]<0 || pos[i][1]>Y)
        return1;
    }
    for(i=0; i<N+2; i++)
      for(j=0; j<i; j++)
        if(pos[i][0]==pos[j][0] && pos[i][1]==pos[j][1])
          return1;
    bfs_fillsep();
    sepmin = 0;
    sepmax = 2*maxs;
    while(sepmin<sepmax){
      sepmid = (sepmin+sepmax+1)/2;
      if(bfs_minsepdist(sepmid)<infty)
        sepmin = sepmid;
      else
        sepmax = sepmid-1;
    }
    printf("%d %d\n", sepmin, bfs_minsepdist(sepmin));
  }
  return 0;
}
