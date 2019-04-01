#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;

void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
void fillb(bool*arr, int sz, bool val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}

enum{ MAXN1 = 50000 };
enum{ MAXN2 = 50000 };
enum{ MAXM  = 150000};
int n1, n2, edges, last[MAXN1], previous[MAXM], head[MAXM];
int matching[MAXN2], dist[MAXN1], Q[MAXN1];
bool used[MAXN1], vis[MAXN1];

void init(int _n1, int _n2){
  n1 = _n1;
  n2 = _n2;
  edges = 0;
  fill(last, n1, -1);
}
void addEdge(int u, int v){
  head[edges] = v;
  previous[edges] = last[u];
  last[u] = edges++;
}
void bfs(){
  fill(dist, n1, -1);
  int sizeQ = 0;
  for (int u = 0; u < n1; ++u) {
    if (!used[u]) {
      Q[sizeQ++] = u;
      dist[u] = 0;
    }
  }
  for (int i = 0; i < sizeQ; i++) {
    int u1 = Q[i];
    for (int e = last[u1]; e >= 0; e = previous[e]) {
      int u2 = matching[head[e]];
      if (u2 >= 0 && dist[u2] < 0) {
        dist[u2] = dist[u1] + 1;
        Q[sizeQ++] = u2;
      }
    }
  }
}
bool dfs(int u1){
  vis[u1] = true;
  for (int e = last[u1]; e >= 0; e = previous[e]) {
    int v = head[e];
    int u2 = matching[v];
    if (u2 < 0 || !vis[u2] && dist[u2] == dist[u1] + 1 && dfs(u2)) {
      matching[v] = u1;
      used[u1] = true;
      return true;
    }
  }
  return false;
}
int maxMatching(){
  fillb(used, n1, false);
  fill(matching, n2, -1);
  for(int res = 0;;){
    bfs();
    fillb(vis, n1, false);
    int f = 0;
    for(int u = 0; u < n1; ++u)
      if(!used[u] && dfs(u))
        ++f;
    if(!f)
      return res;
    res += f;
  }
}
int main(){
  ll answer = 0;
  int n;
  scanf("%d", &n);
  ll tutorsx  [n]; memset(tutorsx  , 0, sizeof(tutorsx  ));
  ll tutorsy  [n]; memset(tutorsy  , 0, sizeof(tutorsy  ));
  ll studentsx[n]; memset(studentsx, 0, sizeof(studentsx));
  ll studentsy[n]; memset(studentsy, 0, sizeof(studentsy));
  for(int i=0; i<n; i++)
    scanf("%lld %lld", &studentsx[i], &studentsy[i]);
  for(int i=0; i<n; i++)
    scanf("%lld %lld", &tutorsx[i], &tutorsy[i]);
  ll distances[n][n];
  for(int i=0; i<n; i++)
    for(int j=0; j<n; j++)
      distances[i][j] = abs(tutorsx[i] - studentsx[j]) + 
                        abs(tutorsy[i] - studentsy[j]);
  ll low = 0, high = 10000000000, mid;
  while(high - low > 2){
    init(n, n);
    mid = (low + high) / 2;
    for(int i = 0; i < n; i++)
      for(int j = 0; j < n; j++)
        if(distances[i][j] <= mid)
          addEdge(i, j);
    if(maxMatching() == n)
      high = mid + 1;
    else if(maxMatching() < n)
      low = mid + 1;
  }
  init(n, n);
  for(int i = 0; i < n; i++)
      for(int j = 0; j < n; j++)
        if(distances[i][j] <= low)
          addEdge(i, j);
  if(maxMatching() == n)
    answer = low;
  else
    answer = low + 1;
  printf("%lld\n", answer);
  return 0;
}
