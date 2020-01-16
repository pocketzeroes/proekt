#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define swap(a,b) do{ __typeof(a) tp; tp = a; a = b; b = tp; }while(0)
typedef struct{
  int first, second;
}pair;
pair newpair(int a, int b){
  return(pair){a,b};
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
/////////////////////////////////
enum{ MAXN=20  + 3};
enum{ MAXM=400 + 3};
int N, M, s, t;
int g[MAXN][MAXN],deg[MAXN];
double mat[MAXN*MAXN][MAXN*MAXN];
bool v[MAXN][MAXN];

Queue*q;

static inline int getnum(int x, int y){
    return (x - 1) * N + y;
}
void gauss(int n){
    for(int i=1; i<=n; ++i){
        for(int j=i+1; j<=n; ++j)
            if(fabs(mat[j][i]) > fabs(mat[i][i]))
                for(int k=1; k<=n+1; ++k)
                    swap(mat[j][k], mat[i][k]);
        
        double tmp=mat[i][i];
        for(int j=1; j<= n+1; ++j)
            mat[i][j]/=tmp;
        for(int j=1; j<=n; ++j){
            if(i==j)
                continue;
            double tmp=mat[j][i];
            for(int k=i; k<=n+1; ++k)
                mat[j][k] -= tmp*mat[i][k];
        }
    }
}
int main(){
    q = newQueue();
    scanf("%d %d", &N, &M);
    for(int i=1; i<=M; ++i){
        int u, v;
        scanf("%d %d", &u, &v);
        ++u, ++v;
        g[u][v] = g[v][u] = 1;
        ++deg[u], ++deg[v];
    }
    scanf("%d %d", &s, &t);
    ++s, ++t;
    for(int i=1; i<=N ;++i){
        v[i][i] = 1;
        push(q, newpair(i,i));
    }
    while(!empty(q)){
        int x, y;
        x = front(q).first;
        y = front(q).second; pop(q);
        for(int i=1; i<=N; ++i)
            for(int j=1; j<=N; ++j)
                if(g[x][i] && g[y][j] && !v[i][j]){
                    v[i][j] = 1;
                    push(q, newpair(i,j));
                }
    }
    if(v[s][t] == 0){
        puts("never meet");
        return 0;
    }
    for(int i=1; i<=N; ++i)
        for(int j=1; j<=N; ++j){
            if(i==j||v[i][j]==0){
                mat[getnum(i,j)][getnum(i,j)]=1;
                continue;
            }
            mat[getnum(i,j)][getnum(i,j)] = deg[i]*deg[j];
            mat[getnum(i,j)][N*N+1]       = deg[i]*deg[j];
            for(int x=1; x<=N; ++x)
                for(int y=1; y<=N; ++y)
                    if(g[i][x]&&g[j][y])
                        mat[getnum(i,j)][getnum(x,y)] = -1;
        }
    gauss(N*N);
    double rv = mat[getnum(s, t)][N*N+1];

    printf("%.11lf\n", rv);
    return 0;
}
