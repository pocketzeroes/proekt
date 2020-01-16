#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define swap(a,b) do{ __typeof(a) tp; tp = a; a = b; b = tp; }while(0)
void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
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

///////////////////////
int*label;
void DisjointSet(int n){
    label = calloc(n+7, sizeof(int));
    fill(label, n+7, -1);
}
int find(int x){
    if(label[x]<0)
        return x;
    label[x] = find(label[x]);
    return label[x];
}
bool join(int a, int b){
    int x = find(a);
    int y = find(b);
    if(x==y)
        return false;
    if(label[x] > label[y])
        swap(x, y);
    label[x] += label[y];
    label[y] = x;
    return true;
}
int getSize(int x){
    return-label[find(x)];
}

typedef struct{
    int u, v, c;
}Edge;
Edge newEdge(){
    return(Edge){0,0,0};
}
Edge input(){
    Edge r;
    scanf("%d %d %d", &r.u, &r.v, &r.c);
    return r;
}
int other(Edge e, int x){
    return e.u ^ e.v ^ x;
}
int cmpE(const void*pa, const void*pb){
    Edge*t=(Edge*)pa;
    Edge*e=(Edge*)pb;
    return(t->c < e->c)?-1:1;
}

enum{ MAX = 200200};
char*NO_ANSWER = "Poor girl";

Edge edges[MAX];
vec  adj  [MAX];
int  dist [MAX];
int n, m, alpha;

void loadGraph(){
    scanf("%d %d %d", &n, &m, &alpha);
    for(int i=1,_b=m; i<=_b; i++)
        edges[i]=input();
    qsort(edges+1, m, sizeof(Edge), cmpE);
    for(int i=1,_b=m; i<=_b; i++){
       pb(adj[edges[i].u], i);
       pb(adj[edges[i].v], i);
    }
}
int findEdge(){
    DisjointSet(n);
    for(int i=1,_b=m; i<=_b; i++)
        if(!join(edges[i].u, edges[i].v))
            return i;
    return -1;
}
int bfs(int block){
    int s = edges[block].u;
    int t = edges[block].v;
    memset(dist, -1, sizeof dist);
    Queue*q = newQueue();
    dist[s] = 0;
    push(q, s);
    while(!empty(q)){
        int u = front(q); pop(q);
        for(int z=0;z<adj[u].sz;z++){int it=adj[u].ptr[z];
            if(it != block && edges[it].c < edges[block].c){
                int v = other(edges[it], u);
                if(dist[v] < 0){
                    dist[v] = dist[u] + 1;
                    push(q, v);
                }
            }
        }
    }
    return dist[t];
}
void process(){
    int id = findEdge();
    if(id < 0){
        puts(NO_ANSWER);
        return;
    }
    int tmp = bfs(id);
    printf("%lld\n", 1LL*edges[id].c*edges[id].c+alpha*(tmp+1));
}
int main(){
    loadGraph();
    process();
    return 0;
}
