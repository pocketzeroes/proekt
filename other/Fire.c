#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

#define dfill(arr, sz1, sz2, val)do{     \
  for(int i=0; i<sz1; i++)               \
    for(int j=0; j<sz2; j++)             \
      arr[i][j] = val;                   \
}while(0)

char buff[1000000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
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

const int dy[4] = { 1,-1, 0, 0 };
const int dx[4] = { 0, 0,-1, 1 };

int main (){
  int runs;
  scanf("%d", &runs);
  while(runs--){
    int Y,X;
    scanf("%d %d", &X, &Y);
    char*m[Y];
    for (int y=0; y<Y; y++)
      m[y]=getstr();
    int dist[Y][X]; dfill(dist, Y, X, -1);
    Queue*q = newQueue();
    for(int y=0; y<Y; y++)
      for(int x=0; x<X; x++)
        if (m[y][x]=='@') {
          push(q, 0);
          push(q, y);
          push(q, x);
          dist[y][x] = 0;
        }
    for (int y=0; y<Y; y++)
      for (int x=0; x<X; x++)
        if (m[y][x]=='*') {
          push(q, 1);
          push(q, y);
          push(q, x);
        }
    int res = -1;
    while (!empty(q)){
      int t = front(q); pop(q);
      int y = front(q); pop(q);
      int x = front(q); pop(q);
      if (t==0 && m[y][x]=='*') 
        continue;
      if (t==0 && (y==0 || y==Y-1 || x==0 || x==X-1)) {
        res = dist[y][x]+1;
        break;
      }
      for (int d=0; d<4; d++) {
        int ny = y + dy[d];
        int nx = x + dx[d];
        if (ny<0 || ny>=Y || nx<0 || nx>=X) 
          continue;
        if (m[ny][nx]=='#' || m[ny][nx]=='*') 
          continue;
        if (t==0 && dist[ny][nx]==-1) {
          dist[ny][nx] = dist[y][x] + 1;
          push(q, 0);
          push(q, ny);
          push(q, nx);
        }
        if (t==1) {
          m[ny][nx] = '*';
          push(q, 1);
          push(q, ny);
          push(q, nx);
        }
      }
    }
    if (res == -1)
      puts("IMPOSSIBLE");
    else
      printf("%d\n", res);
  }
  return 0;
}
