#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))

enum{ Nmax = 30};
enum{ M = 1 + Nmax + Nmax*(Nmax-1)/2 + 1};
int adj[M][M], deg[M];
int cap[M][M], rsd[M][M];
int q[M], prev[M];


bool bfs (int source, int sink){
  memset(prev, -1, sizeof(prev));
  int cur, last = 1, from, i, next;
  q[0] = source;
  prev[source] = source;
  for (cur = 0; cur < last; cur++){
    from = q[cur];
    for (i = deg[from] - 1; i >= 0; i--)
      if (prev[next = adj[from][i]] < 0 && rsd[from][next]){
        prev[next] = from;
        q[last++] = next;
        if (next == sink)
          return true;
      }
  }
  return false;
}
int maxflow (int source, int sink, int n){
  int bot, node, flow = 0;
  memcpy(rsd, cap, sizeof(rsd));
  while (bfs(source, sink)){
    bot = 0x7fffffff;
    for (node = sink; node != source; node = prev[node])
      bot = min(bot, rsd[prev[node]][node]);
    for (node = sink; node != source; node = prev[node]){
      rsd[prev[node]][node] -= bot;
      rsd[node][prev[node]] += bot;
    }
    flow += bot;
  }
  return flow;
}
int main(){
  int cases, casenr, n, i, j, m, finalscore, gamesleft, pointsleft;
  int Points[Nmax];
  char Table[Nmax][Nmax+1];
  bool Pos[Nmax], first;
  scanf("%d\n", &cases);
  for (casenr = 1; casenr <= cases; casenr++){ 
    scanf("%d\n", &n);
    for (i = 0; i < n; i++)
      scanf("%s\n", Table[i]);
    memset(deg, 0, sizeof(deg));
    memset(cap, 0, sizeof(cap));
    for (i = 0; i < n; i++){
      adj[0][i] = i+1;
      adj[i+1][0] = 0;
      deg[i+1] = 1;
    }
    deg[0] = n;
    m = n+1; 
    pointsleft = 0;
    for (i = 1; i < n; i++)
      for (j = 0; j < i; j++)
        if (Table[i][j] == '.'){
          adj[i+1][deg[i+1]++] = adj[j+1][deg[j+1]++] = m;
          adj[m][0] = i+1;
          adj[m][1] = j+1;
          cap[i+1][m] = cap[j+1][m] = 2;
          m++;
          pointsleft += 2;
        }
    m++;
    for (i = n+1; i < m-1; i++){
      adj[i][2] = m-1;
      deg[i] = 3;
      cap[i][m-1] = 2;
    }
    memset(Points, 0, n*sizeof(int));
    for (i = 0; i < n; i++)
      for (j = 0; j < n; j++)
        Points[i] += (Table[i][j] == '1' ? 2 : Table[i][j] == 'd' ? 1 : 0);
    for (i = 0; i < n; i++){
      Pos[i] = true;
      gamesleft = 0;
      for (j = 0; j < n; j++)
        if (Table[i][j] == '.')
          gamesleft++;
      finalscore = Points[i] + 2 * gamesleft;
      for (j = 0; j < n; j++)
        if ((cap[0][j+1] = finalscore - Points[j]) < 0)
          Pos[i] = false;
      if (!Pos[i])
        continue;
      Pos[i] = (maxflow(0, m-1, m) == pointsleft);
    }
    first = true;
    for (i = 0; i < n; i++)
      if (Pos[i]){
        if (!first)
          printf(" ");
        first = false;
        printf("%d", i+1);
      }
    printf("\n");
  }
  return 0;
}
