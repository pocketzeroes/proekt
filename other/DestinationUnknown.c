#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}
int cmp(const void * a, const void * b){
  return ( *(int*)a - *(int*)b );
}


enum{ N   = 2001      };
enum{ inf = 0x7fffffff};
int T[N], Len[N][N];
bool Seen[N];
int DisS[N], DisG[N], DisH[N];

void dijkstra (int n, int start, int Dis[]){
  int i, j;
  for (i = 1; i <= n; i++){
    Seen[i] = false;
    Dis[i] = inf;
  }
  Dis[start] = 0;
  while (true){
    i = -1;
    for (j = 1; j <= n; j++)
      if (!Seen[j] && Dis[j] < inf && (i == -1 || Dis[j] < Dis[i]))
        i = j;
    if (i == -1)
      return;
    Seen[i] = true;
    for (j = 1; j <= n; j++)
      if (Len[i][j] >= 0)
        Dis[j] = min(Dis[j], Dis[i] + Len[i][j]);
  }
}
int main(){
  int cases, casenr, n, m, t, s, g, h, i, a, b, d, x;
  bool first;
  scanf("%d\n", &cases);
  for (casenr = 1; casenr <= cases; casenr++){
    scanf("%d %d %d\n%d %d %d\n", &n, &m, &t, &s, &g, &h);
    memset(Len, -1, sizeof(Len));
    for (i = 0; i < m; i++){
      scanf("%d %d %d\n", &a, &b, &d);
      if (a == b){
        fprintf(stderr, "Error in testcase %d: ", casenr);
        fprintf(stderr, "there is a road from vertex %d to itself!\n", a);
      }
      if (Len[a][b] >= 0){
        fprintf(stderr, "Error in testcase %d: ", casenr);
        fprintf(stderr, "there is a second road between vertices %d and %d!\n", a, b);
      }
      Len[a][b] = Len[b][a] = d;
    }
    for (i = 0; i < t; i++)
      scanf("%d\n", &T[i]);
    qsort(T, t, sizeof(int), cmp);
    dijkstra(n, s, DisS);
    dijkstra(n, g, DisG);
    dijkstra(n, h, DisH);
    if (DisG[h] != Len[g][h]){
      fprintf(stderr, "Error in testcase %d: ", casenr);
      fprintf(stderr, "the road between g and h is not the shortest path!\n");
    }
    first = true;
    for (i = 0; i < t; i++){
      x = T[i];
      if (DisS[x] == DisS[g] + Len[g][h] + DisH[x] || DisS[x] == DisS[h] + Len[h][g] + DisG[x]){
        if (!first)
          printf(" ");
        first = false;
        printf("%d", x);
      }
    }
    if (first)
      printf("No possible destinations!");
    printf("\n");
  }
  return 0;
}
