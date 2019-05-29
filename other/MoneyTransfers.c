#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;

ll INFINITI = 1LL<<50;

inline ll min(ll a, ll b){return a<b?a:b;}
inline ll max(ll a, ll b){return a>b?a:b;}
int in_nextInt(){
  int x;
  scanf("%d", &x);
  return x;
}
ll***newmat(int w, int x, int y){
  ll***rv = calloc(w, sizeof(ll**));
  for(int i=0; i<w; i++){
    rv[i] = calloc(x, sizeof(ll*));
    for(int j=0; j<x; j++)
      rv[i][j] = calloc(y, sizeof(ll));
  }
  return rv;
}
void fill(ll*arr, int sz, ll val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
//////////////////////

ll***bellmanFord(int N, int E, int start, int end, bool*is_ours, int*edges_a, int*edges_b, int*edges_cost);
ll findMaxCost(int N, ll*dist_ours, ll*dist_global);

int main(){
  int N     = in_nextInt();
  int E     = in_nextInt();
  int start = in_nextInt()-1;
  int end   = in_nextInt()-1;
  int i;
  int edges_a   [E]; memset(edges_a   , 0, sizeof(edges_a   ));
  int edges_b   [E]; memset(edges_b   , 0, sizeof(edges_b   ));
  int edges_cost[E]; memset(edges_cost, 0, sizeof(edges_cost));
  for(i = 0; i < E; i++){
    edges_a   [i] = in_nextInt()-1;
    edges_b   [i] = in_nextInt()-1;
    edges_cost[i] = in_nextInt();
  }
  int M = in_nextInt();
  bool is_ours[N]; memset(is_ours, 0, sizeof(is_ours));
  for(i = 0; i < M; i++)
    is_ours[in_nextInt()-1] = true;
  ll***dist = bellmanFord(N, E, start, end, is_ours, edges_a, edges_b, edges_cost);
  ll res = findMaxCost(N, dist[end][1], dist[end][0]);
  if (res == INFINITI)
    puts("Infinity");
  else if (res < 0)
    puts("Impossible");
  else
    printf("%lld\n", res);
  return 0;
}

ll findMaxCost(int N, ll*dist_ours, ll*dist_global){
  int i, j;
  for (i = 1; i < N && dist_ours[i] == INFINITI; i++)
    ;
  if (i == N)
    return -1;
  for (j = 1; j < N && dist_global[j] == INFINITI; j++)
    ;
  if (i < j || (i == j && dist_ours[i] < dist_global[j]))
    return INFINITI;
  ll res = -1, k, diff, ne;
  for ( ; i < N; i++) {
    if (dist_ours[i] < INFINITI && dist_global[i] > dist_ours[i]) {
      ll max_add = INFINITI;
      for (j = 1; j < i; j++) {
        if (dist_global[j] <= dist_ours[i]) {
          max_add = -1;
          break;
        }
        else if (dist_global[j] < INFINITI){
          diff = dist_global[j] - dist_ours[i];
          ne = i - j;
          k = diff / ne;
          if (diff % ne == 0)
            --k;
          max_add = min(max_add, k);
        }
      }
      if (max_add >= 0) {
        for (j = i+1; j < N; j++)
          if (dist_global[j] < dist_ours[i]){
            diff = dist_ours[i] - dist_global[j];
            ne = j - i;
            k = diff / ne;
            if (diff % ne == 0)
              ++k;
            if (max_add < k) {
              max_add = -1;
              break;
            }
          }
        res = max(res, max_add);
      }
    }
  }
  return res;
}

ll***bellmanFord(int N, int E, int start, int end, bool*is_ours, int*edges_a, int*edges_b, int*edges_cost){
  int i, ne;
  ll***dist = newmat(N, 2, N);
  for (i = 0; i < N; i++) {
    fill(dist[i][0], N, INFINITI);
    fill(dist[i][1], N, INFINITI);
  }
  dist[start][1][0] = 0;
  for (ne = 1; ne < N; ne++) {
    for (i = 0; i < E; i++) {
      if (is_ours[edges_a[i]] && is_ours[edges_b[i]]) {
        dist[edges_a[i]][1][ne] = min(dist[edges_a[i]][1][ne], dist[edges_b[i]][1][ne-1] + edges_cost[i]);
        dist[edges_b[i]][1][ne] = min(dist[edges_b[i]][1][ne], dist[edges_a[i]][1][ne-1] + edges_cost[i]);
      }
      dist[edges_a[i]][0][ne] = min(dist[edges_a[i]][0][ne], dist[edges_b[i]][0][ne-1] + edges_cost[i]);
      dist[edges_b[i]][0][ne] = min(dist[edges_b[i]][0][ne], dist[edges_a[i]][0][ne-1] + edges_cost[i]);
      if (!is_ours[edges_a[i]])
        dist[edges_a[i]][0][ne] = min(dist[edges_a[i]][0][ne], dist[edges_b[i]][1][ne-1] + edges_cost[i]);
      if (!is_ours[edges_b[i]])
        dist[edges_b[i]][0][ne] = min(dist[edges_b[i]][0][ne], dist[edges_a[i]][1][ne-1] + edges_cost[i]);
    }
  }
  return dist;
}

