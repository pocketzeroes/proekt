#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef struct{
  int first;
  int second;
  int third;
}trip;
trip newtrip(int a, int b, int c){
  return(trip){a,b,c};
}

#if 1 //que
typedef trip QueueElementType;
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

char world[140][64][64];
int  dist [140][64][64];

int main(){
    memset(world,'#',sizeof world);
    memset(dist,-1,sizeof dist);
    int n,m;
    scanf(" %d %d",&n,&m);
    int sr,sc,tr,tc;
    scanf(" (%d %d) (%d %d)",&sr,&sc,&tr,&tc);
    for (int i=1; i<=n; i++){
        scanf(" %s",&world[0][i][1]);
        world[0][i][m+1]='#';
        for (int j=1; j<120; j++)
            for (int k=1; k<=m; k++)
                world[j][i][k]=world[0][i][k];
    }
    for (int i=140; i--;)
        for (int j=64; j--;)
            for (int k=64; k--;)
                world[i][j][k]=(world[i][j][k]=='#'?0x10:0x00);
    int masters;
    scanf(" %d",&masters);
    for (int i=0; i<masters; i++){
        int steps;
        scanf(" %d",&steps);
        int patrol = fmax(1,steps*2-2);
        for (int j=0; j<steps; j++){
            int r,c;
            scanf(" (%d %d)",&r,&c);
            for (int k=0; k<120; k+=patrol){
                world[k+j][r][c]=world[k+patrol-j][r][c]=0x0F;
            }
        }
    }
    for (int t=0; t<120; t++){
        for (int i=0; i<n; i++){
            for (int j=1; j<=m; j++) if (world[t][i][j]<=0x0F) world[t][i][j]|=world[t][i][j-1]&1;
            for (int j=m; j>=1; j--) if (world[t][i][j]<=0x0F) world[t][i][j]|=world[t][i][j+1]&2;
        }
        for (int i=0; i<m; i++){
            for (int j=1; j<=n; j++) if (world[t][j][i]<=0x0F) world[t][j][i]|=world[t][j-1][i]&4;
            for (int j=n; j>=1; j--) if (world[t][j][i]<=0x0F) world[t][j][i]|=world[t][j+1][i]&8;
        }
    }
    for (int i=120; i--;)
        world[i][tr][tc]=0;
    Queue*todo = newQueue();//of trip
    push(todo, newtrip(0,sr,sc));
    dist[0][sr][sc]=0;
    int res=-1;
    while(!empty(todo)){
        trip trc=front(todo);
        int t = trc.first,
            r = trc.second,
            c = trc.third; pop(todo);
        if(r==tr && c==tc){
            res=dist[t][r][c];
            break;
        }
        int nt=(t+1)%120;
        for(int dr=-1; dr<=+1; ++dr)
            for(int dc=-1; dc<=+1; ++dc)
                if(world[nt][r+dr][c+dc]==0 && (dr==0 || dc==0) && !~dist[nt][r+dr][c+dc])
                    dist[nt][r+dr][c+dc] = dist[t][r][c]+1, push(todo, newtrip(nt,r+dr,c+dc));
    }
    if(~res)
        printf("%d\n",res);
    else
        puts("IMPOSSIBLE");
    return 0;
}
