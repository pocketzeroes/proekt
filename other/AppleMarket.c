#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

typedef long long ll;
void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}

enum{ MAX_K  = 100000};
enum{ MAX_NM = 50    };
enum{ LOG    = 6     };
enum{ PW     = MAX_NM};
enum{MAXV = 4 * PW * PW + MAX_K + 2};
enum{MAXE = MAX_NM * MAX_NM * (1 + (LOG + 1) * (LOG + 1)) + MAX_K * (1 + 4 * (LOG + 2))};

//typedef struct MaxFlow{
  int cap   [MAXE << 1],
      flow  [MAXE << 1],
      limit [MAXV     ];
  int last  [MAXV     ],
      to    [MAXE << 1],
      next  [MAXE << 1];
  int prev  [MAXV     ],
      cur   [MAXV     ],
      height[MAXV     ],
      cnt   [MAXV  + 1];
  int edgecnt,
      vertices;
  void resetflow(){
    fill(flow, edgecnt, 0);
  }
  void init(){
    memset(last, -1, sizeof(last));
    vertices = edgecnt = 0;
  }
  void _addedge(int a, int b, int c){
    flow[edgecnt] = 0;
    to  [edgecnt] = b;
    cap [edgecnt] = c;
    next[edgecnt] = last[a];
    if (last[a] == -1)
      vertices++;
    last[a] = edgecnt++;
    assert(vertices <= (int) MAXV);
    assert(edgecnt <= (int) 2 * MAXE);
  }
  void add_edge(int start, int end, int capacity, bool directed){
    _addedge(start, end, capacity);
    _addedge(end, start, directed ? 0 : capacity);
  }
  ll go(int source, int sink){
    const int INF = INT_MAX;
    ll maxflow = 0;
    memset(prev  , -1, sizeof(prev)  );
    memset(cur   , -1, sizeof(cur)   );
    memset(height,  0, sizeof(height));
    memset(cnt   ,  0, sizeof(cnt)   );
    fill(limit, MAXV, 0);
    cnt[0]    = vertices;
    int at    = source, e = -1;
    limit[at] = INF;
    while (height[source] < vertices){
      for (e = cur[at]; e > -1; e = next[e])
        if (flow[e] < cap[e] && height[to[e]] + 1 == height[at])
          break;
      if (e > -1){
        cur[at] = prev[to[e]] = e;
        limit[to[e]] = min(limit[at], cap[e] - flow[e]);
        at = to[e];
        if (at == sink)
          for (maxflow += limit[sink]; at != source; at = to[prev[at] ^ 1])
            flow[prev[at]] += limit[sink], flow[prev[at] ^ 1] -= limit[sink];
      }
      else {
        if (--cnt[height[at]] == 0)
          break;
        height[at] = vertices;
        for (e = last[at]; e > -1; e = next[e])
          if (flow[e] < cap[e] && height[to[e]] + 1 < height[at])
            height[at] = height[to[e]] + 1, cur[at] = e;
        cnt[height[at]]++;
        if (at != source)
          at = to[prev[at] ^ 1];
      }
    }
    return maxflow;
  }
//}
//MaxFlow net;

int cost   [MAX_NM][MAX_NM];
int tree_id[2 * PW][2 * PW];

int next_node() {
  static int next_num = 0;
  return next_num++;
}
void update(const int vert, int x, int c1, int c2, int v){
  for (int l = c1 + PW, r = c2 + PW + 1; l < r; l >>= 1, r >>= 1){
    if (l & 1)
      add_edge(vert, tree_id[x][l++], v, 1);
    if (r & 1)
      add_edge(vert, tree_id[x][--r], v, 1);
  }
}
int main(){
  int N, M, K;
  scanf("%d %d %d", &N, &M, &K);
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < M; ++j)
      scanf("%d", &cost[i][j]);
  int src  = next_node(),
      sink = next_node();
  init();
  for (int i = 1; i < 2 * PW; ++i)
    for (int j = 1; j < 2 * PW; ++j)
      tree_id[i][j] = next_node();
  for (int x = PW; x < PW + N; ++x)
    for (int y = PW; y < PW + M; ++y) {
      add_edge(tree_id[x][y], sink, cost[x - PW][y - PW], 1);
      for (int i = x; i > 0; i >>= 1)
        for (int j = y; j > 0; j >>= 1)
          if(i!=x || j!=y)
            add_edge(tree_id[i][j], tree_id[x][y], cost[x - PW][y - PW], 1);
    }
  for (int k = 0, r1, r2, c1, c2, v; k < K; ++k) {
    scanf("%d %d %d %d %d", &r1, &r2, &c1, &c2, &v);
    --r1, --r2, --c1, --c2;
    const int vert = next_node();
    add_edge(src, vert, v, 1);
    for (int l = r1 + PW, r = r2 + PW + 1; l < r; l >>= 1, r >>= 1) {
      if (l & 1)
        update(vert, l++, c1, c2, v);
      if (r & 1)
        update(vert, --r, c1, c2, v);
    }
  }
  const ll res = go(src, sink);
  printf("%lld\n", res);
  return 0;
}
