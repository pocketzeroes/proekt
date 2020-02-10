#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int read(){
  int xx;
  scanf("%d", &xx);
  return xx;
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
#define fill(arr, sz, val)do{     \
  for(int i=0; i<sz; i++)         \
    arr[i] = val;                 \
}while(0)

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

//////////////////////////////////
enum{ MAXN = 35};
int N, A[MAXN][MAXN];

#define MAXN 70
int N, mate[MAXN], dist[MAXN], pathDist;
vec adj[MAXN], typeA;
bool color[MAXN];

void addEdge(int v, int w){
    pb(adj[v], w);
    pb(adj[w], v);
}
bool hasPath(){
    Queue*q = newQueue();
    for(int z=0;z<typeA.sz;z++){int v = typeA.ptr[z];
        if(mate[v] == -1){
            dist[v] = 0;
            push(q, v);
        }
        else
            dist[v] = INT_MAX;
    }
    pathDist = INT_MAX;
    while(!empty(q)){
        int v = front(q); pop(q);
        for(int z=0;z<adj[v].sz;z++){int w = adj[v].ptr[z];
            if(mate[w] == -1){
                if(pathDist == INT_MAX)
                   pathDist = dist[v] + 1;
            }
            else if(dist[mate[w]] == INT_MAX){
                dist[mate[w]] = dist[v] + 1;
                if(pathDist == INT_MAX)
                    push(q, mate[w]);
            }
        }
    }
    return pathDist != INT_MAX;
}
bool dfs(int v){
    for(int z=0;z<adj[v].sz;z++){int w = adj[v].ptr[z];
        if(mate[w] == -1){
            if(pathDist == dist[v] + 1){
                mate[w] = v;
                mate[v] = w;
                return true;
            }
        }
        else if(dist[mate[w]] == dist[v] + 1){
            if(dfs(mate[w])){
                mate[w] = v;
                mate[v] = w;
                return true;
            }
        }
    }
    dist[v] = INT_MAX;
    return false;
}
void init(){
    fill(mate , MAXN, -1);
    fill(color, MAXN, false);
}
void clear(){
    for(int i = 0; i < MAXN; i++)
        adj[i].sz=0;
    typeA.sz=0;
}
int solve(){
    int ret = 0;
    for(int v = 0; v < MAXN; v++)
        if (color[v])
           pb(typeA, v);
    while(hasPath())
        for(int z=0;z<typeA.sz;z++){int v = typeA.ptr[z];
            if(mate[v] == -1 && dfs(v))
                ret++;
        }
    return ret;
}

int main(){
    N = read();
    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++)
            A[i][j] = read();
    int lo = 1,
        hi = 1e6 + 5,
        mid;
    while(lo <= hi){
        mid = lo + (hi - lo) / 2;
        init();
        for(int i=0; i<N; i++)
            color[i] = true;
        for(int i=0; i<N; i++)
            for(int j=0; j<N; j++)
                if(A[i][j] >= mid)
                    addEdge(i, j + N);
        if(solve() == N)
            lo = mid + 1;
        else
            hi = mid - 1;
        clear();
    }
    printf("%d\n", hi);
    return 0;
}
