#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
double min(double a, double b){return a<b?a:b;}

enum{ N=15+2};
const double eps=1e-5;
double d[1<<N][N],inq[1<<N][N],bi[1<<N],dis[N][N];
double x[N],y[N],s[N];
double m;
int n;

double DIS(int a,int b){
    return sqrt(pow(x[a]-x[b],2)+pow(y[a]-y[b],2));
}
void pre(){
    for(int S=0; S<(1<<n); ++S)
        bi[S]=pow(m,__builtin_popcount(S));
    for(int i=0; i<n; ++i)
        for(int j=0; j<n; ++j)
            dis[i][j]=DIS(i,j);
}
typedef struct{
    int S,pos;
}node;
node newnode(int a, int b){
    return(node){a,b};
}

#if 1 //que
typedef node QueueElementType;
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

bool solve(double v){
    memset(d,100,sizeof d);
    memset(inq,0,sizeof inq);
    Queue*q = newQueue();//of node
    push(q, newnode(0,0));
    memset(d[0],0,sizeof d[0]);
    while(!empty(q)){
        int S   = front(q).S;
        int pos = front(q).pos; pop(q);
        inq[S][pos]=0;
        for(int i=0;i<n;++i){
            if(!(S&(1<<i))){
                int S2=S^(1<<i);
                double tmp;
                if(!S)
                    tmp=sqrt(pow(x[i],2)+pow(y[i],2))/v;
                else
                    tmp=d[S][pos]+dis[pos][i]/(v*bi[S]);
                if(tmp<=s[i]){
                    d[S2][i]=min(d[S2][i],tmp);
                    if(!inq[S2][i]){
                        inq[S2][i]=1;
                        push(q, newnode(S2,i));
                    }
                }
            }
        }
    }
    double ans=1e11;
    for(int i=0;i<n;++i)
        ans=min(ans,d[(1<<n)-1][i]);
    return ans<1e10;
}
int main(){
    scanf("%d",&n);
    for(int i=0; i<n; ++i)
        scanf("%lf%lf%lf",&x[i],&y[i],&s[i]);
    scanf("%lf",&m);
    pre();
    double l=0,r=99999999;
    for(int i=0;i<50;++i){
        double mid=(l+r)/2.0;
        if(solve(mid))
            r=mid;
        else
            l=mid;
    }
    printf("%f\n",l);
    return 0;
}
