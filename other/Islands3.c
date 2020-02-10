#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef struct{
  int first, second;
}pair;
pair newpair(int a, int b){
  return(pair){a,b};
}
#if 1 //que
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
#define GET(x) scanf("%d", &x)
#define GED(x) scanf("%lf", &x)
typedef long long ll;

int r, c;
char pic    [55][55];
bool visited[55][55];

void bfs(int r0, int c0){
  Queue*q = newQueue();//of pair
  push(q, newpair(r0, c0));
  visited[r0][c0] = true;
  while(!empty(q)){
    pair cur = front(q); pop(q);
    int i = cur.first,
        j = cur.second;
    if(i > 0 && (pic[i - 1][j] == 'L' || pic[i - 1][j] == 'C') && !visited[i - 1][j]){
      push(q, newpair(i - 1, j));
      visited[i - 1][j] = true;
    }
    if(j > 0 && (pic[i][j - 1] == 'L' || pic[i][j - 1] == 'C') && !visited[i][j - 1]){
      push(q, newpair(i, j - 1));
      visited[i][j - 1] = true;
    }
    if(i < r - 1 && (pic[i + 1][j] == 'L' || pic[i + 1][j] == 'C') && !visited[i + 1][j]){
      push(q, newpair(i + 1, j));
      visited[i + 1][j] = true;
    }
    if(j < c - 1 && (pic[i][j + 1] == 'L' || pic[i][j + 1] == 'C') && !visited[i][j + 1]){
      push(q, newpair(i, j + 1));
      visited[i][j + 1] = true;
    }
  }
}
int main(){
  while(GET(r) > 0){
    GET(c);
    for(int i = 0; i < r; ++i)
      scanf("%s", pic[i]);
    memset(visited, false, sizeof(visited));
    int comp = 0;
    for(int i = 0; i < r; ++i){
      for(int j = 0; j < c; ++j){
        if(!visited[i][j] && pic[i][j] == 'L'){
          ++comp;
          bfs(i, j);
        }
      }
    }
    printf("%d\n", comp);
  }
  return 0;
}
