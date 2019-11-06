#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ N=2000};
bool vis[N],flag;
typedef struct{
    int val,siz;
}Node;
typedef struct{
    int row,col;
}Map;

#if 1 //queueue
typedef Node QueueElementType;
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

Map edge[N];
int mmap[47][47];
int ans=0,n;
int downdir[6][2]={-1,0,-1,1,0,-1,0,1,1,-1,1,0};
int middledir[6][2]={-1,-1,-1,0,0,-1,0,1,-1,-1,1,0};
int updir[6][2]={-1,-1,-1,0,0,-1,0,1,1,0,1,1};
int linemax[47];

inline int cul(int x){
    return x*x*x;
}
void init(int r){
    int m=cul(r)-cul(r-1);
    for(int i=1;i<=m;i++)
        vis[i]=false;
    int i=1,ant=0,row=1,col=1;
    int n1=r,flag1=0;
    while(i<=m){
        while(ant>=r){
            linemax[row]=col-1;
            row++;
            col=1;
            ant=0;
            if(!flag1)
                r++;
            else
                r--;
            if(r==2*n1-1)
                flag1=1;
        }
        edge[i].row=row;
        edge[i].col=col;
        mmap[row][col]=i;
        col++;
        ant++;
        i++;
    }
    linemax[row]=col-1;
}
void bfs(int a, int b, int r){
    Node p;
    p.val=a;
    p.siz=0;
    int row,col;
    Queue*q = newQueue();//of Node
    if(!vis[a])
        push(q, p);
    vis[a]=true;
    while(!empty(q)){
        Node top = front(q); pop(q);
        int val=top.val,
            siz=top.siz;
        if(val==b){
            if(siz<=n)
                flag=true;
            ans=siz;
            return;
        }
        if(edge[val].row<r){
            for(int i=0;i<6;i++){
                row=edge[val].row+updir[i][0];
                col=edge[val].col+updir[i][1];
                if(row<1||i>2*r-1||col<1||col>linemax[row]) 
                    continue;
                int nowval=mmap[row][col];
                if(!vis[nowval]){
                    p.siz=siz+1;
                    p.val=nowval;
                    push(q, p);
                    vis[nowval]=true;
                }
            }
        }
        else if(edge[val].row==r){
            for(int i=0;i<6;i++){
                row=edge[val].row+middledir[i][0];
                col=edge[val].col+middledir[i][1];
                if(row<1||i>2*r-1||col<1||col>linemax[row]) 
                    continue;
                int nowval=mmap[row][col];
                if(!vis[nowval]){
                    p.siz=siz+1;
                    p.val=nowval;
                    push(q, p);
                    vis[nowval]=true;
                }
            }
        }
        else{
            for(int i=0;i<6;i++){
                row=edge[val].row+downdir[i][0];
                col=edge[val].col+downdir[i][1];
                if(row<1||i>2*r-1||col<1||col>linemax[row]) 
                    continue;
                int nowval=mmap[row][col];
                if(!vis[nowval]){
                    p.siz=siz+1;
                    p.val=nowval;
                    push(q, p);
                    vis[nowval]=true;
                }
            }
        }
    }
}
int main(){
    int r,a,b,x,siz;
    flag=false;
    scanf("%d%d%d%d%d",&r,&n,&a,&b,&x);
    init(r);
    while(x--){
        scanf("%d",&siz);
        vis[siz]=true;
    }
    bfs(a,b,r);
    if(flag)
        printf("%d\n",ans);
    else
        puts("No");
    return 0;
}
