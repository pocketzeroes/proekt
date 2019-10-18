#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;

#define pb(zpv, zvv) zpv.ptr = pushback(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
int gcd(int x,int y){
    if (x%y==0) 
        return y;
    else
        return gcd(y,x%y);
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

void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}


typedef struct{
    int v, u;
    ll  cap, flow;
}Edge;
Edge newEdge(int v, int u, ll c, ll f){
    return(Edge){v,u,c,f};
}

#define pbe(zpv, zvv) zpv.ptr = pushbackE(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
Edge*pushbackE(Edge*array, int *size, Edge value){
  Edge*output = resizeArray(array, Edge, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
    Edge*ptr;
    int sz;
}vece;
vece newVecE(){
    vece rez;
    rez.ptr = NULL;
    rez.sz  = 0;
    return rez;
}

enum{ maxn = 1000};
int n;
int a[maxn+1];

#define flow_inf 1e18
vece edges;
vec*adj;
int m;
int s, t;
int*level;
int*gptr;
Queue*q;

void Dinic(int _n, int _s, int _t){
    n = _n;
    s = _s;
    t = _t;
    m = 0;
    q = newQueue();
    adj  =calloc(n, sizeof(vec));
    level=calloc(n, sizeof(int));
    gptr =calloc(n, sizeof(int));
}
void add_edge(int v, int u, ll cap){
    pbe(edges, newEdge(v, u, cap,0));
    pbe(edges, newEdge(u, v, 0, 0 ));
    pb(adj[v], m);
    pb(adj[u], m+1);
    m += 2;
}
bool bfs(){
    while(!empty(q)){
        int v = front(q); pop(q);
        for(int z=0;z<adj[v].sz;z++){int id = adj[v].ptr[z];
            if(edges.ptr[id].cap - 
               edges.ptr[id].flow < 1)
                continue;
            if(level[edges.ptr[id].u] != -1)
                continue;
            level[edges.ptr[id].u] = level[v] + 1;
            push(q, edges.ptr[id].u);
        }
    }
    return level[t] != -1;
}
ll dfs(int v, ll pushed){
    if(pushed == 0)
        return 0;
    if(v == t)
        return pushed;
#define cid gptr[v]
    for(; cid < adj[v].sz; cid++){
        int id = adj[v].ptr[cid];
        int u = edges.ptr[id].u;
        if(level[v] + 1 != level[u] || edges.ptr[id].cap - edges.ptr[id].flow < 1)
            continue;
        ll tr = dfs(u, fminl(pushed, edges.ptr[id].cap - edges.ptr[id].flow));
        if(tr == 0)
            continue;
        edges.ptr[id  ].flow += tr;
        edges.ptr[id^1].flow -= tr;
        return tr;
    }
    #undef cid
    return 0;
}
ll flow(){
    ll f = 0;
    while(1){
        fill(level, n, -1);
        level[s] = 0;
        push(q, s);
        if(!bfs())
            break;
        memset(gptr, 0, n*sizeof(int));
        ll pushed;
        while(pushed = dfs(s, flow_inf))
            f += pushed;
    }
    return f;
}

int main(){
    scanf("%d", &n);
    int mini = 1;
    int maxi = 1;
    for(int i=1; i<=n; i++){
        scanf("%d", &a[i]);
        if(a[i]<a[mini])
            mini = i;
        if(a[i]>a[maxi])
            maxi = i;
    }
    Dinic(n, mini-1, maxi-1);
    for(int i=1; i<=n; i++){
        for(int j=i+1; j<=n; j++){
            int f=gcd(a[i],a[j]);
            if(f>1){
                add_edge(i-1, j-1, f);
                add_edge(j-1, i-1, f);
            }
        }
    }
    printf("%lld\n", flow());
    return 0;
}
