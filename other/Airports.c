#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
enum{ MAXN = 502};
enum{ INF  =(int)1e9};
typedef struct{
  int first;
  int second;
  int third;
}trip;
trip newtrip(int a, int b, int c){
  return(trip){a,b,c};
}

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
#endif

//namespace maxflow{
typedef long long ll;
enum{ MAXV = 300005};
enum{ MAXE = 300005};
const ll oo =(ll)1e18;
int V, E;
int last[MAXV], dist[MAXV], curr[MAXV];
int next[MAXE], adj[MAXE];
ll  cap [MAXE];

void init(int n){
    V = n;
    E = 0;
    memset(last, -1, sizeof(last));
}
void edge(int x, int y, ll c1, ll c2){
    adj[E] = y; cap[E] = c1; next[E] = last[x]; last[x] = E++;
    adj[E] = x; cap[E] = c2; next[E] = last[y]; last[y] = E++;
}
ll Push(int x, int sink, ll flow){
    if (x == sink)
        return flow;
#define e curr[x]
    for(; e!=-1; e = next[e]){
        int y = adj[e];
        if(cap[e] && dist[x] + 1 == dist[y]){
            ll f;
            if(f = Push(y, sink, fmin(flow, cap[e])))
                return cap[e] -= f, cap[e ^ 1] += f, f;
        }
    }
#undef e
    return 0;
}
ll run(int src, int sink){
    ll ret = 0;
    while(1){
        for(int i = 0; i < V; ++i){
            curr[i] = last[i];
            dist[i] = -1;
        }
        Queue*q = newQueue();
        push(q, src);
        dist[src] = 0;
        while(!empty(q)){
            int x = front(q); pop(q);
            for(int e = last[x]; e != -1; e = next[e]){
                int y = adj[e];
                if(cap[e] && dist[y] == -1){
                    push(q, y);
                    dist[y] = dist[x] + 1;
                }
            }
        }
        if(dist[sink] == -1)
            break;
        ll f;
        while(f = Push(src, sink, oo))
            ret += f;
    }
    return ret;
}
//};
int n, m;
int inspection  [MAXN];
int direct[MAXN][MAXN];
int fast  [MAXN][MAXN];
int indegree    [MAXN];
int outdegree   [MAXN];

void floyd_warshall(){
    for (int k = 1; k <= n; ++k){
        for (int i = 1; i <= n; ++i){
            for (int j = 1; j <= n; ++j){
                fast[i][j] = fmin(fast[i][j], fast[i][k] + inspection[k] + fast[k][j]);
            }
        }
    }
}
bool can_make(trip a, trip b){
    int s1 = a.first ;
    int f1 = a.second;
    int t1 = a.third ;
    int s2 = b.first ;
    int t2 = b.third ;
    int time = t1 + direct[s1][f1] + inspection[f1] + fast[f1][s2] + (f1 == s2 ? 0 : inspection[s2]);
    return time <= t2;
}
int main(){
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i)
        scanf("%d", inspection + i);
    for (int i = 1; i <= n; ++i){
        for (int j = 1; j <= n; ++j){
            scanf("%d", &direct[i][j]);
            fast[i][j] = direct[i][j];
        }
    }
    floyd_warshall();
    trip flights[m];
    int s, f, t;
    for(int i = 0; i < m; ++i){
        scanf("%d %d %d", &s, &f, &t);
        flights[i] = newtrip(s, f, t);
    }
    int source = 2 * m + 1;
    int sink   = 2 * m + 2;
    memset(indegree,  0, sizeof(indegree) );
    memset(outdegree, 0, sizeof(outdegree));
    init(sink + 1);
    for (int i = 0; i < m; ++i){
        for (int j = 0; j < m; ++j){
            if (i != j && can_make(flights[i], flights[j])){
                edge(2 * i + 1, 2 * j + 2, 1, 0);
                ++outdegree[i];
                ++indegree[j];
            }
        }
    }
    for (int i = 0; i < m; ++i){
        if (outdegree[i] > 0)
            edge(source, 2 * i + 1, 1, 0);
        if (indegree[i] > 0)
            edge(2 * i + 2, sink, 1, 0);
    }
    printf("%lld\n", m - run(source, sink));
    return 0;
}
