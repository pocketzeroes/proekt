#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
int**newmat(int x, int y){
  int**rv = calloc(x, sizeof(int*));
  for(int i=0;i<x;i++)
    rv[i] = calloc(y, sizeof(int));
  return rv;
}

typedef struct{
  int first;
  int second;
}pair;
pair newPair(int a, int b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}

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


int**colorBorder(int**grid, int gridSz, int*grid0sz, int r0, int c0, int color, int*rsz, int**r0sz){
  int n = gridSz;
  int m = grid0sz[0];
  Queue*q = newQueue();
  int dr[4] = { 1, 0, -1, 0 };
  int dc[4] = { 0, 1, 0, -1 };
  push(q, newPair(r0, c0));
  bool that[n][m]; memset(that, 0, sizeof(that));
  that[r0][c0] = true;
  while(!empty(q)){
    pair cur = front(q); pop(q);
    int r = cur.first,
        c = cur.second;
    for(int k = 0;k < 4;k++){
      int nr = r + dr[k], nc = c + dc[k];
      if(nr >= 0 && nr < n && nc >= 0 && nc < m && grid[nr][nc] == grid[r][c]){
        if(!that[nr][nc]){
          that[nr][nc] = true;
          push(q, newPair(nr, nc));
        }
      }
    }
  }
  int**ret = newmat(n, m);
  for(int i = 0; i < n; i++){
    for(int j = 0; j < m; j++){
      if(!that[i][j])
        ret[i][j] = grid[i][j];
      else{
        int r = i, c = j;
        int s = 0;
        for(int k = 0; k < 4; k++){
          int nr = r + dr[k], nc = c + dc[k];
          if(nr >= 0 && nr < n && nc >= 0 && nc < m && grid[nr][nc] == grid[r][c])
            s++;
        }
        if(s != 4)
          ret[i][j] = color;
        else
          ret[i][j] = grid[i][j];
      }
    }
  }
  int*cols = calloc(n, sizeof(int));
  fill(cols, n, m);
 *r0sz = cols;
 *rsz = n;
  return ret;
}
// int main(){
//   return 0;
// }


