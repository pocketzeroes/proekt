#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}

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
///////////////////////////////////
enum{ N = 102};
char Map[N][N];
int dx[4] = {0,0,-1,1};
int dy[4] = {-1,1,0,0};
int Dis0[N][N], Dis1[N][N], Dis2[N][N];
Queue*BFS[2];//of pair


void shortestdis (int sx, int sy, int h, int w, int D[][N]){
  int d, t, x, y, x2, y2, i;
  pair p;
  memset(D, -1, N*N*sizeof(int));
  BFS[0] = newQueue();
  BFS[1] = newQueue();
  push(BFS[0], newPair(sx,sy));
  D[sy][sx] = d = 0;
  t = 0;
  while(!empty(BFS[0]) || !empty(BFS[1])){
    if(empty(BFS[t])){
      d++;
      t = 1-t;
    }
    p = front(BFS[t]); pop(BFS[t]);
    x = p.first;
    y = p.second;
    for (i = 0; i < 4; i++){
      x2 = x + dx[i];
      y2 = y + dy[i];
      if (x2 >= 0 && x2 < w && y2 >= 0 && y2 < h && Map[y2][x2] != '*' && D[y2][x2] == -1){
        D[y2][x2] = d;
        push(BFS[Map[y2][x2]=='#'?1-t:t], newPair(x2,y2));
      }
    }
  }
}
int main(){
  int cases, casenr, h, w, x, y, p1x, p1y, p2x, p2y, dis;
  scanf("%d\n", &cases);
  for (casenr = 1; casenr <= cases; casenr++){ 
    scanf("%d %d\n", &h, &w);
    for (y = 1; y <= h; y++)
      scanf("%s\n", Map[y]+1);
    for (x = 0; x <= w+1; x++)
      Map[0][x] = Map[h+1][x] = '.';
    for (y = 0; y <= h+1; y++)
      Map[y][0] = Map[y][w+1] = '.';
    p1x = p1y = p2x = p2y = 0;
    for (x = 1; x <= w; x++)
      for (y = 1; y <= h; y++)
        if (Map[y][x] == '$'){
          if (p1x == 0){
            p1x = x;
            p1y = y;
          }
          else{
            p2x = x;
            p2y = y;
          }
        }
    shortestdis(0, 0, h+2, w+2, Dis0);
    shortestdis(p1x, p1y, h+2, w+2, Dis1);
    shortestdis(p2x, p2y, h+2, w+2, Dis2);
    dis = Dis0[0][0] + Dis1[0][0] + Dis2[0][0];
    for (x = 1; x <= w; x++)
      for (y = 1; y <= h; y++)
        if (Dis0[y][x] >= 0)
          dis = min(dis, (Map[y][x] == '#' ? 1 : 0) + Dis0[y][x] + Dis1[y][x] + Dis2[y][x]);
    printf("%d\n", dis);
  }
  return 0;
}
