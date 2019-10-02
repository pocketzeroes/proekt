#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
typedef double dbl;
void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
int in_nextInt(){
  int xx;
  scanf("%d", &xx);
  return xx;
}
dbl in_nextDouble(){
  dbl xx;
  scanf("%lf", &xx);
  return xx;
}
dbl**newmat(int x, int y){
  dbl**rv = calloc(x, sizeof(dbl*));
  for(int i=0;i<x;i++)
    rv[i] = calloc(y, sizeof(dbl));
  return rv;
}
//////////////////////

int _N;
enum{INF = 1 << 29};
int*eadj;
int*eprev;
int*elast;
int*now;
int eidx;
dbl*flow;
dbl*capa;
int*level;

void MaxFlow(int pN, int M){
  _N = pN;
  eadj   = calloc(2*M, sizeof(int));
  eprev  = calloc(2*M, sizeof(int));
  elast  = calloc(_N , sizeof(int)); fill(elast, _N, -1);
  flow   = calloc(2*M, sizeof(dbl));
  capa   = calloc(2*M, sizeof(dbl));
  now    = calloc(_N , sizeof(int));
  level  = calloc(_N , sizeof(int));
  eidx   = 0;
}
void add_edge(int a, int b, dbl c){
  eadj[eidx] = b; flow[eidx] = 0; capa[eidx] = c; eprev[eidx] = elast[a]; elast[a] = eidx++;
  eadj[eidx] = a; flow[eidx] = c; capa[eidx] = c; eprev[eidx] = elast[b]; elast[b] = eidx++;
}

bool bfs(int source, int sink){
  fill(level, _N, -1);
  int front = 0, back = 0;
  int queue[_N]; clr(queue);
  level[source] = 0;
  queue[back++] = source;
  while(front < back && level[sink] == -1){
    int node = queue[front++];
    for(int e = elast[node]; e != -1; e = eprev[e]){
      int to = eadj[e];
      if(level[to] == -1 && flow[e] < capa[e]){
        level[to] = level[node] + 1;
        queue[back++] = to;
      }
    }
  }
  return level[sink] != -1;
}
dbl dfs(int cur, dbl curflow, int goal){
  if(cur == goal)
    return curflow;
  for(int e = now[cur]; e != -1; now[cur] = e = eprev[e]){
    if(level[eadj[e]] > level[cur] && flow[e] < capa[e]){
      dbl res = dfs(eadj[e], fmin(curflow, capa[e] - flow[e]), goal);
      if(res > 0){
        flow[e] += res;
        flow[e ^ 1] -= res;
        return res;
      }
    }
  }
  return 0;
}
dbl dinic(int source, int sink){
  dbl res, flow = 0;
  while(bfs(source, sink)){
    memcpy(now, elast, _N*sizeof(int));
    while((res = dfs(source, INF, sink)) > 0)
      flow += res;
  }
  return flow;
}

///////////////////////////////////

int N, M, W, H;
dbl*v;
dbl*x;
dbl*height;
dbl*uc;
dbl**mx;
dbl**us;
dbl maxHeight, minHeight;

bool possible(dbl lowerbound){
  MaxFlow(N+M+2,2*N+2*M+N*M);
  int s = N+M+1,
      t = N+M;
  for(int i=0; i<M; i++)
    add_edge(s, i, v[i] - uc[i]);
  for(int i=0; i<M; i++)
    for(int j=0; j<N; j++)
      add_edge(i, j + M, mx[j][i] - us[j][i]);
  dbl total = 0;
  for(int j=0; j<N; j++){
    if(height[j] > lowerbound)
      continue;
    dbl demand = (lowerbound - height[j]) * (x[j+1] - x[j]);
    total += demand;
    add_edge(j + M, t, demand);
  }
  bool rv=dinic(s,t) + 1e-6 >= total;
  free(eadj ); free(eprev); free(elast); free(flow ); free(capa ); free(now  ); free(level);
  return rv;
}
int main(){
  N = in_nextInt();
  M = in_nextInt();
  W = in_nextInt();
  H = in_nextInt();
  v = calloc(M, sizeof(dbl));
  for(int i=0; i<M; i++)
    v[i] = in_nextDouble();
  x = calloc(N+1, sizeof(dbl));
  for(int i=1; i<N; i++)
    x[i] = in_nextDouble();
  x[N] = W;
  dbl mn[N][M];
  for(int i=0; i<N; i++)
    for(int j=0; j<M; j++)
      mn[i][j] = in_nextDouble();
  mx = newmat(N, M);//of dbl
  for(int i=0; i<N; i++)
    for(int j=0; j<M; j++)
      mx[i][j] = in_nextDouble();
  height = calloc(N, sizeof(dbl));
  uc     = calloc(M, sizeof(dbl));
  us     = newmat(N, M);//of dbl
  for(int i=0; i<N; i++){
    for(int j=0; j<M; j++){
      height[i] += mn[i][j] / (x[i+1] - x[i]);
      uc[j]     += mn[i][j];
      us[i][j]  += mn[i][j];
    }
  }
  maxHeight = 0;
  minHeight = H;
  for(int i=0; i<N; i++){
    minHeight = fmin(minHeight, height[i]);
    maxHeight = fmax(maxHeight, height[i]);
  }
  dbl lo = minHeight,
      hi = maxHeight;
  for(int iter=0; iter<100; iter++){
    dbl mid = (lo+hi) / 2.;
    if(possible(mid))
      lo = mid;
    else
      hi = mid;
  }
  printf("%.3f\n", maxHeight - lo);
  return 0;
}
