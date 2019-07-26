#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

#if 1 //que
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

enum{ INF = 1000000000};
enum{ NN  = 505       };

int cases, caseno;
int n, m, adj[NN][NN], deg[NN], d[NN], pr[NN];

int bfs(int s){
  Queue*q = newQueue();
  int res = INF;
  for (int i = 0; i < n; i++)
    d[i] = INF;
  d[s] = 0;
  pr[s] = -1;
  push(q, s);
  while(!empty(q)){
    int u = front(q); pop(q);
    for (int i = 0; i < deg[u]; i++){
      int v = adj[u][i];
      if (v != pr[u]){
        if (d[v] == INF){
          d[v] = d[u] + 1;
          pr[v] = u;
          push(q, v);
        }
        else{
          res = min(res, d[v] + d[u] + 1);
          if(res == 3)
            return 3;
        }
      }
    }
  }
  return res;
}
int main(){
  cases=1;
  while (cases--) {
    scanf("%d %d", &n, &m);
    memset(deg, 0, sizeof(deg));
    for(int i=0; i<m; i++){
      int u, v;
      scanf("%d %d", &u, &v);
      adj[u][deg[u]++] = v;
      adj[v][deg[v]++] = u;
    }
    int res = INF;
    for (int u = 0; u < n && res != 3; u++)
      res = min(res, bfs(u));
//    printf("Case %d: ", ++caseno);
    if (res == INF)
      puts("impossible");
    else
      printf("%d\n", res);
  }
  return 0;
}
