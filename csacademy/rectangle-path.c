#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>



typedef struct pair{
    int first;
    int second;
}pair;
pair newPair(int a, int b){
    pair rez;
    rez.first =a;
    rez.second=b;
    return rez;
}

typedef pair QueueElementType;
typedef struct Queue
{
  QueueElementType  *Elements;
  int  Front;
  int  Back;
  int  NumElements;
  int  Capacity;
} Queue;
Queue *CreateQueue(int N);
void   DeleteQueue(Queue *Q);
int    isEmptyQueue(Queue *Q);
int    Enqueue(Queue *Q, QueueElementType e);
QueueElementType Dequeue(Queue *Q);

Queue *CreateQueue(int N)
{
  Queue *Q;
  if (N < 1)
  {
    printf("\n**Error in CreateQueue invalid parameter N (%d)\n\n", N);
    return NULL;
  }
  Q = (Queue *)malloc(sizeof(Queue));
  if (Q == NULL)
  {
    printf("\n**Error in CreateQueue: malloc failed to allocate\n\n");
    exit(-1);
  }
  Q->Elements = (QueueElementType *)malloc(N * sizeof(QueueElementType));
  if (Q->Elements == NULL)
  {
    printf("\n**Error in CreateQueue: malloc failed to allocate\n\n");
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
int isEmptyQueue(Queue *Q)
{
  return Q->NumElements == 0;
}
int Enqueue(Queue *Q, QueueElementType e)
{
  if (Q->NumElements == Q->Capacity)  
  {
    int N = 2 * Q->Capacity;
    QueueElementType *newE = (QueueElementType *)malloc(N * sizeof(QueueElementType));
    if (newE == NULL)
    {
      printf("\n**Error in Enqueue: malloc failed to allocate\n\n");
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
QueueElementType Dequeue(Queue *Q)
{
  if (isEmptyQueue(Q))  
  {
    printf("\n**Error in Dequeue: Q is empty?!\n\n");
    exit(-1);
  }
  QueueElementType e = Q->Elements[Q->Front];
  Q->Front++;
  if (Q->Front >= Q->Capacity)  
    Q->Front = 0;
  Q->NumElements--;
  return e;
}
QueueElementType Front(Queue *Q)
{
  if (isEmptyQueue(Q))  
  {
    printf("\n**Error in Dequeue: Q is empty?!\n\n");
    exit(-1);
  }
  QueueElementType e = Q->Elements[Q->Front];
  return e;
}


////
enum{ kMaxN =(int) 1e3 + 5};

int el  [kMaxN][kMaxN];
int sum [kMaxN][kMaxN];
int best[kMaxN][kMaxN];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i += 1) {
        for (int j = 1; j <= m; j += 1) {
            scanf("%d", &el[i][j]);
        }
    }
    int h, w;
    scanf("%d %d", &h , &w);
    int sx, sy;
    scanf("%d %d", &sx, &sy);
    int fx, fy;
    scanf("%d %d", &fx, &fy);
    for (int i = n; i; i -= 1) {
        for (int j = m; j; j -= 1) {
            sum[i][j] = sum[i + 1][j] + sum[i][j + 1] - sum[i + 1][j + 1] + el[i][j];
        }
    }
    int RectangleSum(int x, int y){ return sum[x][y] + sum[x + h][y + w] - sum[x + h][y] - sum[x][y + w];}
    for (int i = 0; i <= n + 1; i += 1) {
        for (int j = 0; j <= m + 1; j += 1) {
            el  [i][j] = 1;
            best[i][j] =(int) 1e9;
        }
    }
    for (int i = 1; i + h - 1 <= n; i += 1) {
        for (int j = 1; j + w - 1 <= m; j += 1) {
            el[i][j] = RectangleSum(i, j);
            if (el[i][j]) {
                el[i][j] = 1;
            }
        }
    }
    Queue* bfs_q = CreateQueue(1000);
    Enqueue(bfs_q, newPair(sx, sy));
    best[sx][sy] = 0;
    while (bfs_q->NumElements > 0 ) {
        pair ff = Front(bfs_q);
        int x = ff.first;
        int y = ff.second;
        Dequeue(bfs_q);
        const int dx[4] = {+1, -1, 0, 0};
        const int dy[4] = {0, 0, +1, -1};
        for (int d = 0; d < 4; d += 1) {
            int nx = x + dx[d];
            int ny = y + dy[d];
            if (el[nx][ny]) {
                continue;
            }
            if (1 + best[x][y] < best[nx][ny]) {
                best[nx][ny] = 1 + best[x][y];
                Enqueue(bfs_q, newPair(nx, ny));
            }
        }
    }
    if (best[fx][fy] ==(int) 1e9) {
        puts("-1");
    } 
    else {
        printf("%d\n", best[fx][fy] );
    }
    return 0;
}




















































