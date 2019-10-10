#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;

#if 1 //queueue
typedef int QueueElementType;
typedef struct Queue
{
  QueueElementType  *Elements;
  int  Front;
  int  Back;
  int  NumElements;
  int  Capacity;
} Queue;
Queue *newQueue();
void   DeleteQueue(Queue *Q);
int    empty(Queue *Q);
int    push(Queue *Q, QueueElementType e);
QueueElementType pop(Queue *Q);
int    isElementInQueue(Queue *Q, QueueElementType e);

Queue *newQueue()
{
  int N=1024;
  Queue *Q;
  if (N < 1)
  {
    printf("\n**Error in newQueue invalid parameter N (%d)\n\n", N);
    return NULL;
  }
  Q = (Queue *)malloc(sizeof(Queue));
  if (Q == NULL)
  {
    printf("\n**Error in newQueue: malloc failed to allocate\n\n");
    exit(-1);
  }
  Q->Elements = (QueueElementType *)malloc(N * sizeof(QueueElementType));
  if (Q->Elements == NULL)
  {
    printf("\n**Error in newQueue: malloc failed to allocate\n\n");
    exit(-1);
  }
  Q->Front = 0;  
  Q->Back = -1;  
  Q->NumElements = 0;
  Q->Capacity = N;
  return Q;
}
void DeleteQueue(Queue *Q)
{
  free(Q->Elements);
  free(Q);
}
int empty(Queue *Q)
{
  return Q->NumElements == 0;
}
int size(Queue *Q)
{
  return Q->NumElements;
}
int push(Queue *Q, QueueElementType e)
{
  if (Q->NumElements == Q->Capacity)  
  {
    int N = 2 * Q->Capacity;
    QueueElementType *newE = (QueueElementType *)malloc(N * sizeof(QueueElementType));
    if (newE == NULL)
    {
      printf("\n**Error in push: malloc failed to allocate\n\n");
      exit(-1);
    }
    int  i = Q->Front;
    int  j = 0;
    int  n;
    for (n = 0; n < Q->NumElements; ++n)
    {
      newE[j] = Q->Elements[i];
      ++j;
      ++i;
      if (i >= Q->Capacity)
        i = 0;
    }
    free(Q->Elements);
    Q->Front = 0;
    Q->Back = j - 1;
    Q->Elements = newE;
    Q->Capacity = N;
  }
  Q->Back++;
  if (Q->Back >= Q->Capacity) 
    Q->Back = 0;
  Q->Elements[Q->Back] = e;  
  Q->NumElements++;
  return 1;  
}
QueueElementType pop(Queue *Q)
{
  if (empty(Q))  
  {
    printf("\n**Error in pop: Q is empty?!\n\n");
    exit(-1);
  }
  QueueElementType e = Q->Elements[Q->Front];
  Q->Front++;
  if (Q->Front >= Q->Capacity)  
    Q->Front = 0;
  Q->NumElements--;
  return e;
}
QueueElementType front(Queue *Q)
{
  if (empty(Q))  
  {
    printf("\n**Error in pop: Q is empty?!\n\n");
    exit(-1);
  }
  QueueElementType e = Q->Elements[Q->Front];
  return e;
}
int isElementInQueue(Queue *Q, QueueElementType e)
{
  int  i = Q->Front;
  int  count;
  for (count = 0; count < Q->NumElements; ++count)
  {
    if (Q->Elements[i] == e)  
      return 1;  
    ++i;
    if (i == Q->Capacity)  
      i = 0;
  }
  return 0;
}
#endif

enum{ MAXN = 30};
enum{ MAXC = 26};
enum{ MAXCOST = 100000};
enum{ INF = 1000000000};
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};
enum{ MAXNODE = MAXN * MAXN * 2 + 1};
enum{ MAXEDGE = MAXN * MAXN * 5 * 2};
int head[MAXNODE], vtx[MAXEDGE], nextEdge[MAXEDGE], capacity[MAXEDGE], totalEdge;
int source, sink, sign;
ll flow;
int dist[MAXNODE], pre[MAXNODE];
int n, m, c;
char mat[MAXN][MAXN + 1];
int cost[MAXC];

void addEdge(int a, int b, int c){
    vtx[totalEdge] = b;
    capacity[totalEdge] = c;
    nextEdge[totalEdge] = head[a];
    head[a] = totalEdge;
    ++ totalEdge;
    vtx[totalEdge] = a;
    capacity[totalEdge] = 0;
    nextEdge[totalEdge] = head[b];
    head[b] = totalEdge;
    ++ totalEdge;
}
bool bfs(){
    for (int i = 0; i <= sink; ++ i) {
        dist[i] = INF;
    }
    Queue*q=newQueue();
    push(q, source);
    dist[source] = 0;
    while(size(q)){
        int u = front(q); pop(q);
        for(int p = head[u]; p != -1; p = nextEdge[p]){
            int v = vtx[p];
            if(capacity[p] > 0 && dist[u] + 1 < dist[v]){
                dist[v] = dist[u] + 1;
                if (v == sink)
                    return true;
                push(q, v);
            }
        }
    }
    return false;
}
void dinic(int u){
    if (u == sink){
        int delta = INF;
        for (int v = sink, p; v != source; v = vtx[p]) {
            p = pre[v];
            delta = fmin(delta, capacity[p]);
            p ^= 1;
        }
        for (int v = sink, p; v != source; v = vtx[p]) {
            p = pre[v];
            capacity[p] -= delta;
            if (capacity[p] == 0)
                sign = vtx[p ^ 1];
            p ^= 1;
            capacity[p] += delta;
        }
        flow += delta;
        return;
    }
    for (int p = head[u]; p != -1; p = nextEdge[p]) {
        int v = vtx[p];
        if (capacity[p] > 0 && dist[u] + 1 == dist[v]) {
            pre[v] = p;
            dinic(v);
            if (dist[sign] < dist[u])
                return;
            sign = sink;
        }
    }
    dist[u] = INF;
}
int main(){
    assert(scanf("%d%d%d", &n, &m, &c) == 3);
    assert(1 <= n && n <= MAXN);
    assert(1 <= m && m <= MAXN);
    assert(1 <= c && c <= MAXC);
    for (int i = 0; i < m; ++ i) {
        assert(scanf("%s", mat[i]) == 1);
        assert(strlen(mat[i]) == n);
    }
    for (int i = 0; i < c; ++ i) {
        assert(scanf("%d", &cost[i]) == 1);
        assert(1 <= cost[i] && cost[i] <= MAXCOST);
    }
    memset(head, -1, sizeof(head));
    totalEdge = 0;
    source = -1, sink = n * m * 2;
    for (int i = 0; i < m; ++ i) {
        for (int j = 0; j < n; ++ j) {
            if (mat[i][j] == 'B') {
                assert(source == -1);
                source = i * n + j + n * m;
            }
            else if (mat[i][j] == '.') {
                addEdge(i * n + j, i * n + j + n * m, INF);
            }
            else {
                assert('a' <= mat[i][j] <= 'a' + c);
                addEdge(i * n + j, i * n + j + n * m, cost[mat[i][j] - 'a']);
            }
            for (int k = 0; k < 4; ++ k) {
                int x = i + dx[k], y = j + dy[k];
                if (x >= 0 && y >= 0 && x < m && y < n) {
                    addEdge(i * n + j + n * m, x * n + y, INF);
                }
                else {
                    addEdge(i * n + j + n * m, sink, INF);
                }
            }
        }
    }
    assert(source != -1);
    flow = 0;
    while (bfs() && flow < INF) {
        dinic(source);
    }
    if (flow < INF){
        printf("%d\n", flow);
    }
    else {
        puts("-1");
    }
    return 0;
}
