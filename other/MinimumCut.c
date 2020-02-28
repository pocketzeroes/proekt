#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
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
#if 1//stk
#include <stddef.h>
#define check_pointer(p) if (!p) {puts("Out of memory."); exit(EXIT_FAILURE);}
#define MINIMUM_SIZE  1
#define GROWTH_FACTOR 2
typedef int T;
typedef struct
{
    T *bottom;
    T *top;
    T *allocated_top;
}
stack;
stack * new(void)
{
  stack *s = malloc(sizeof(stack));
  check_pointer(s);
  s->bottom = malloc(MINIMUM_SIZE * sizeof(T));
  check_pointer(s->bottom);
  s->top = s->bottom - 1;
  s->allocated_top = s->bottom + MINIMUM_SIZE - 1;
  return s;
}
void destroy(stack *s)
{
  free(s->bottom);
  free(s);
}
bool sempty(stack *s)
{
    return s->top < s->bottom ? true : false;
}
void spush(stack *s, T x)
{
    if (s->top == s->allocated_top)
    {
        ptrdiff_t qtty = s->top - s->bottom + 1;
        ptrdiff_t new_qtty = GROWTH_FACTOR * qtty;
        s->bottom = realloc(s->bottom, new_qtty * sizeof(T));
        check_pointer(s->bottom);
        s->top = s->bottom + qtty - 1;
        s->allocated_top = s->bottom + new_qtty - 1;
    }
    *(++s->top) = x;
}
T spop(stack *s)
{
    return *(s->top--);
}
T stop(stack *s)
{
    return *(s->top);
}
#endif

enum{N = 505};
int n, m, s, t, u, v, w;
ll g[N][N], rg[N][N], f[N], max_flow, path_flow;
int p[N];

ll bfs(int s, int t){
    bool visited[n]; clr(visited);
    visited[s] = true;
    Queue*q=newQueue();
    push(q, s);
    p[s] = -1;
    f[s] = INT_MAX;
    while(!empty(q)){
        int u = front(q); pop(q);
        for(int v=0; v<n; v++){
            if(visited[v]==false && rg[u][v] > 0){
                push(q, v);
                p[v] = u;
                visited[v] = true;
                f[v] = fminl(f[u], rg[u][v]);
            }
        }
    }
    return(visited[t]?f[t]:0);
}
void MinCut(int s, int t){
    while(path_flow = bfs(s, t)){
        for(v=t; v != s; v=p[v]){
            u = p[v];
            rg[u][v] -= path_flow;
            rg[v][u] += path_flow;
        }
    }
    int total = 0;
    stack*ss=new();
    spush(ss, s);
    bool marked[n]; clr(marked);
    while(!sempty(ss)){
        int i = stop(ss); spop(ss);
        marked[i] = true;
        total++;
        for(int j=0;j<n;j++)
            if(rg[i][j] > 0 && !marked[j]){
                marked[j] = true;
                spush(ss, j);
            }
    }
    printf("%d\n", total);
    for(int i=0;i<n;i++)
        if(marked[i])
            printf("%d\n", i);
}
int main(){
    scanf("%d %d %d %d", &n, &m, &s, &t);
    memset(g ,0,sizeof( g));
    memset(rg,0,sizeof(rg));
    for(int i=0; i<m; i++){
        scanf("%d %d %d", &u, &v, &w);
        g[u][v] = rg[u][v] = w;
    }
    MinCut(s, t);
    return 0;
}
