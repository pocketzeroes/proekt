#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

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
    printf("\n**Error in newQueue: malloc failed _to allocate\n\n");
    exit(-1);
  }
  Q->Elements = (QueueElementType *)malloc(N * sizeof(QueueElementType));
  if (Q->Elements == NULL)
  {
    printf("\n**Error in newQueue: malloc failed _to allocate\n\n");
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
      printf("\n**Error in push: malloc failed _to allocate\n\n");
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

typedef long long ll;
enum{ N=(int)1e6+5  };
enum{ INF=0x3f3f3f3f};

typedef struct{
    ll t, cap, flow, next;
}node;
node e[N];
int head[N],cur[N],cnt;
int d[N];
int pro[220];

void init(){
    memset(head,-1,sizeof(head));
    cnt=0;
}
void add(int u,int v,ll cap){
    e[cnt]=(node){v,cap,0,head[u]};
    head[u]=cnt++;
    e[cnt]=(node){u,0,0,head[v]};
    head[v]=cnt++;
}
bool bfs(int s,int t){
    memset(d, 0, sizeof(d));
    Queue*q = newQueue();
    push(q, s);
    d[s]=1;
    while(!empty(q)){
        int u = front(q); pop(q);
        for(int i=head[u]; ~i; i=e[i].next){
            int v = e[i].t;
            if(d[v]==0&&e[i].cap-e[i].flow>0){
                d[v]=d[u]+1;
                push(q, v);
            }
        }
    }
    return d[t]>0;
}
ll dfs(int s, int t, ll minedge){
    if(s==t)
        return minedge;
    ll flow=0;
#define i cur[s]
    for(; ~i; i=e[i].next){
        int v = e[i].t;
        if(d[v]==d[s]+1 && e[i].cap-e[i].flow>0){
            ll temp = dfs(v, t, fmin(minedge-flow, e[i].cap-e[i].flow));
            e[i].flow  +=temp;
            e[i^1].flow-=temp;
            flow += temp;
            if(flow==minedge)
                return flow;
        }
    }
    if(flow==0)
        d[s]=0;
#undef i
    return flow;
}
ll dinic(int s, int t){
    ll maxflow=0;
    while(bfs(s,t)){
        memcpy(cur,head,sizeof(head));
        maxflow+=dfs(s,t,INF);
    }
    return maxflow;
}
int main(){
    int n, u, v, x, k;
    init();
    scanf("%d", &n);
    for(int i=1; i<=n; i++){
        scanf("%d %d %d", &u, &v, &k);
        pro[i] = u-v;
        while(k--){
            scanf("%d", &x);
            add(x, i, INF);
        }
    }
    ll sum=0;
    for(int i=1; i<=n; i++){
        if(pro[i]>0){
            add(0, i, pro[i]);
            sum += pro[i];
        }
        else if(pro[i]<0)
            add(i, n+1, -pro[i]);
    }
    int ans = dinic(0, n+1);
    printf("%lld\n", sum-ans);
    return 0;
}
