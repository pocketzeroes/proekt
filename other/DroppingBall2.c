#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
#define dfill(arr, sz1, sz2, val)do{     \
  for(int i=0; i<sz1; i++)               \
    for(int j=0; j<sz2; j++)             \
      arr[i][j] = val;                   \
}while(0)
char buff[100000];
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

typedef long long ll;
ll inf =(ll) 1e18;


typedef struct{
  ll a[55][55];
  int sz;
}mat;

mat newmat(int x){
  mat rez;
  dfill(rez.a, x, x, -inf);
  rez.sz = x;
  return rez;
}

mat mul(mat a, mat b){
  int n = a.sz;
  mat c = newmat(n);
  for(int i=0; i<n; ++i)
    for(int j=0; j<n; ++j)
      for(int k=0; k<n; ++k)
        c.a[i][j] = fmaxl(c.a[i][j], a.a[i][k] + b.a[k][j]);
  return c;
}
mat power(mat a, int k){
  k--;
  mat res = a;
  while(k){
    if(k&1)
      res = mul(res, a);
    a = mul(a, a), k >>= 1;
  }
  return res;
}

int main(){
  int r, c, k;
  scanf("%d %d %d", &r, &c, &k);
  char*d[r];
  for(int z=0;z<r;z++)
    d[z] = getstr();
  int aa[c];
  for(int z=0;z<c;z++)
    scanf("%d", &aa[z]);
  ll cost[c+1][c+1]; dfill(cost,c+1,c+1, -inf);
  bool end[r][c];
  for(int i = 0; i < r; ++i){
    for(int j = 0; j < c; ++j){
      if(j == 0 && d[i][j] == 'L')
        end[i][j] = true;
      if(j > 0 && d[i][j] == '?' || d[i][j] == 'L'){
        if(d[i][j - 1] == 'R' || d[i][j - 1] == '?')
          end[i][j] = end[i][j - 1] = true;
      }
      if(j == c - 1 && d[i][j] == 'R')
        end[i][j] = true;
      if(d[i][j] == 'X')
        end[i][j] = true;
    }
  }
  void bfs(int x, int y, ll*a){
    bool mark[r][c]; clr(mark);
    mark[x][y] = true;
    Queue*q = newQueue();
    push(q, x),
    push(q, y);
    while(size(q)){
      int x = front(q); pop(q);
      int y = front(q); pop(q);
      if(end[x][y])
        a[c] = 0;
      if(d[x][y] == '.'){
        if(x + 1 < r && !mark[x + 1][y])
          mark[x + 1][y] = true, push(q, x + 1), push(q, y);
      }
      if(d[x][y] == '?'){
        if(y - 1 >= 0 && !mark[x][y - 1])
          mark[x][y - 1] = true, push(q, x), push(q, y - 1);
        if(y + 1 < c && !mark[x][y + 1])
          mark[x][y + 1] = true, push(q, x), push(q, y + 1);
      }
      if(d[x][y] == 'L'){
        if(y - 1 >= 0 && !mark[x][y - 1])
          mark[x][y - 1] = true, push(q, x), push(q, y - 1);
      }
      if(d[x][y] == 'R'){
        if(y + 1 < c && !mark[x][y + 1])
          mark[x][y + 1] = true, push(q, x), push(q, y + 1);
      }
    }
    for(int i = 0; i < c; ++i)
      if(mark[r - 1][i] && d[r - 1][i] == '.')
        a[i] = aa[i];
  };
  for(int i=0; i<c; ++i)
    bfs(0, i, cost[i]);
  cost[c][c] = 0;
  c++;
  mat A = newmat(c);
  for(int i=0; i<c; ++i)
    for(int j=0; j<c; ++j)
      A.a[i][j] = cost[i][j];
  A = power(A, k);
  ll ans = 0;
  for(int i=0; i<c; ++i)
    for(int j=0; j<c; ++j)
      ans = fmaxl(ans, A.a[i][j]);
  printf("%lld\n", ans);
  return 0;
}
