#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

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
vec newVec(){
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
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
/////////////////////
enum{ K = 302};

typedef struct{
  int from;
  int to;
  int flow;
}Edge;
Edge newEdge(int a, int b, int c){
  Edge rez;
  rez.from  = a;
  rez.to    = b;
  rez.flow  = c;
  return rez;
}
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

vec adj[K * K];
vece elist;
int ptr [K * K];
int dist[K * K];
int k, n, m;
int source, sink;

int getVertex(int a, int b){
  return a * k + b;
}
void addEdge(int from, int to, int flow){
  adj[from].ptr = pushback(adj[from].ptr, &adj[from].sz, elist.sz);
  elist.ptr = pushbackE(elist.ptr, &elist.sz, newEdge(from, to, flow));
  adj[to].ptr = pushback(adj[to].ptr, &adj[to].sz, elist.sz);
  elist.ptr = pushbackE(elist.ptr, &elist.sz, newEdge(to, from, 0));
}
void init(){
  scanf("%d %d %d", &n, &k, &m);
  source = getVertex(n-1, k-1) + 1;
  sink = source+1;
  for(int i = 0 ; i < k ; i++)
    addEdge(source, getVertex(i, i), 1);
  for(int i = 0 ; i < k ; i++)
    addEdge(getVertex(n-1, i), sink, 1e9);
  for(int i = 0 ; i < m ; i++) {
    int u, v;
    scanf("%d %d", &u, &v);
    u--, v--;
    for(int j = 0 ; j < k ; j++) {
      int nj = (j + 1) % k;
      addEdge(getVertex(u, j), getVertex(v, nj), 1);
    }
  }
}
bool bfs(){
  for(int i = 0 ; i <= sink ; i++)
    dist[i] = -1;
  Queue*q = newQueue();
  push(q, source);
  dist[source] = 0;
  while(!empty(q)){
    int now = front(q);
    pop(q);
    for(int z=0; z<adj[now].sz; z++){int idx = adj[now].ptr[z];
      Edge e = elist.ptr[idx];
      if(e.flow > 0 && dist[e.to] == -1){
        dist[e.to] = dist[now] + 1;
        push(q, e.to);
      }
    }
  }
  return dist[sink] != -1;
}
int augment(int now, int f){
  if(now == sink)
    return f;
#define i ptr[now]
  for(; i<adj[now].sz; i++){
    int idx = adj[now].ptr[i];
    Edge e = elist.ptr[idx];
    if(e.flow > 0 && dist[e.to] == dist[now] + 1){
      int res = augment(e.to, min(f, e.flow));
      if (res > 0){
        elist.ptr[idx  ].flow -= res;
        elist.ptr[idx^1].flow += res;
        return res;
      }
    }
  }
#undef i
  return 0;
}
int maxFlow(){
  int ret = 0;
  while (bfs()){
    for(int i = 0 ; i <= sink; i++)
      ptr[i] = 0;
    int f = augment(source, 1e9);
    while(f > 0){
      ret += f;
      f = augment(source, 1e9);
    }
  }
  return ret;
}
int main(){
  init();
  printf("%d\n", maxFlow());
  return 0;
}
