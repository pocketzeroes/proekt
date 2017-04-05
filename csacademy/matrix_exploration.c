#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

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


//
typedef  long long     ll   ;

int const N = 100 * 1000 + 16;
int inf = 1000 * 1000 * 1000;
int dist[1024][1024];
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
ll accumulate(int*arr,int sz){
  ll sum=0;
  for(int i=0;i<sz;i++)
    sum+=arr[i];
  return sum;
}

int main(){
  char*w=NULL;
  size_t len;
  int n, m, k;
  scanf("%d %d %d", &n, &m, &k);
  getchar();
  for(int i = 0; i < n; ++i) {
    getline(&w, &len, stdin);
    for(int j = 0; j < m; ++j)
      dist[i][j] = (w[j] == '#') ? 0 : inf;
    free(w);
    w=NULL;
  }
  for(int i = 0; i < k; ++i) {
    int x, y;
    scanf("%d %d",&x,&y);
    getchar();
    Queue*q=CreateQueue(512);
    dist[x-1][y-1] = 0;
    Enqueue(q,newPair(x-1, y-1));
    while( q->NumElements > 0 ){
      pair cur = Dequeue(q);
      x = cur.first;
      y = cur.second;
      for(int i = 0; i < 4; ++i) {
        int x2 = x + dx[i];
        int y2 = y + dy[i];
        if(0 > x2 || x2 >= n ||
           0 > y2 || y2 >= m ||
           dist[x2][y2] <= dist[x][y] + 1)
             continue;
        dist[x2][y2] = dist[x][y] + 1;
        Enqueue(q,newPair(x2, y2));
      }
    }
  }

  ll ans = 0;
  for(int i = 0; i < n; ++i)
    ans += accumulate(dist[i], m);
  printf("%lld", ans);
}










