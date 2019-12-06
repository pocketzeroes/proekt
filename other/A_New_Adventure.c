#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
char buff[100000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}
typedef struct{
  int first, second;
}pair;

#if 1 //queueue
typedef pair QueueElementType;
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

enum{Nmax =(int) 1e5 + 112};
int n, m, ans = -1, d[Nmax];
char*s[Nmax];
Queue*qu;//of pair

int id(int u, int v){
    return u * m + v;
}
void bfs(){
    memset(d, -1, sizeof(d));
    push(qu, (pair){0, 0});
    d[0] = 0;
    while(size(qu)){
        pair u = front(qu); pop(qu);
        if(u.first == n - 1){
            ans = d[id(u.first, u.second)] + 1;
            return;
        }
        if(s[u.first][(u.second - 1 + m) % m] == '.' && s[u.first][(u.second - 2 + m) % m] == '.' && d[id(u.first, (u.second - 2 + m) % m)] == -1){
            d[id(u.first, (u.second - 2 + m) % m)] = d[id(u.first, u.second)] + 1;
            push(qu, (pair){u.first, (u.second - 2 + m) % m});
        }
        if(u.first > 0 && s[u.first - 1][(u.second - 1 + m) % m] == '.' && s[u.first - 1][u.second] == '.' && d[id(u.first - 1, (u.second - 1 + m) % m)] == -1){
            d[id(u.first - 1, (u.second - 1 + m) % m)] = d[id(u.first, u.second)] + 1;
            push(qu, (pair){u.first - 1, (u.second - 1 + m) % m});
        }
        if(s[u.first + 1][(u.second - 1 + m) % m] == '.' && s[u.first + 1][u.second] == '.' && d[id(u.first + 1, (u.second - 1 + m) % m)] == -1){
            d[id(u.first + 1, (u.second - 1 + m) % m)] = d[id(u.first, u.second)] + 1;
            push(qu, (pair){u.first + 1, (u.second - 1 + m) % m});
        }
        if(s[u.first][(u.second - 1 + m) % m] == '.' && d[id(u.first, (u.second - 1 + m) % m)] == -1){
            d[id(u.first, (u.second - 1 + m) % m)] = d[id(u.first, u.second)] + 1;
            push(qu, (pair){u.first, (u.second - 1 + m) % m});
        }
    }
}
int main(){
    qu=newQueue();//of pair
    scanf("%d %d", &n, &m);
    for(int i=0; i<n; ++i)
        s[i] = getstr();
    bfs();
    printf("%d\n", ans);
    return 0;
}
