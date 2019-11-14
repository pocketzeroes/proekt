#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)

char**newmat(int x, int y){
  char**rv = calloc(x, sizeof(char*));
  for(int i=0; i<x; i++)
    rv[i] = calloc(y, sizeof(char));
  return rv;
}
void freemat(char**m, int x){
  for(int i=0; i<x; i++)
    free(m[i]);
  free(m);
  m = NULL;
}
char**grid;
int r, c;

typedef struct{
  int q[4];
}quad;

quad newquad(int a, int b, int c, int d){
    quad rv;
    rv.q[0] = a;
    rv.q[1] = b;
    rv.q[2] = c;
    rv.q[3] = d;
    return rv;
}

typedef struct{
  quad first;
  int  second;
}pqi;
pqi newpqi(quad a, int b){
  return(pqi){a, b};
}


#if 1 //queueue
typedef pqi QueueElementType;
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



quad getStep(quad step, int dir){
    quad step2 = newquad(step.q[0], step.q[1], dir, 1),
         err   = newquad(-1, -1, -1, -1);
    if(dir == step.q[2]){
        if(step.q[3]>1)
            return err;
        step2.q[3] = 2;
    }
    switch(dir){
        case 0: step2.q[0]--; break;
        case 1: step2.q[1]++; break;
        case 2: step2.q[0]++; break;
        case 3: step2.q[1]--; break;
        default:return err;
    }
    if(step.q[0]<0 || 
       step.q[0]>=r || 
       step.q[1]<0 || 
       step.q[1]>=c || 
       step2.q[0]<0 || 
       step2.q[0]>=r || 
       step2.q[1]<0 || 
       step2.q[1]>=c ||
       (grid[step2.q[0]][step2.q[1]]=='B') ||
       (step.q[2]%2==step2.q[2]%2 && step.q[2]!=step2.q[2]))
        return err;
    return step2;
}
int main(){
    int T;
    scanf("%d", &T);
    for(int t=0; t<T; ++t){
        if(grid)freemat(grid, r);
        scanf("%d %d", &r, &c);
        grid = newmat(r, c);
        int sr, sc, er, ec;
        getchar();
        for(int i=0; i<r; ++i){
            for(int j=0; j<c; ++j){
                grid[i][j] = getchar();
                if(grid[i][j]=='R'){
                    sr = i;
                    sc = j;
                }
                if(grid[i][j]=='D'){
                    er = i;
                    ec = j;
                }
            }
            getchar();
        }
        bool visited[r][c][4][2]; clr(visited);
        Queue*qs = newQueue();// pqi of pqi{quad, int}
        quad state = newquad(sr, sc, -1, 1);
        push(qs, newpqi(state, 0));
        int steps = -1;
        while(size(qs)>0){
            pqi curr = front(qs); pop(qs);
            for(int i=0; i<4; ++i){
                quad step2 = getStep(curr.first, i);
                if(step2.q[0]>-1 && !visited[step2.q[0]][step2.q[1]][step2.q[2]][step2.q[3]]){
                    if(step2.q[0]==er && step2.q[1]==ec){
                        steps=curr.second+1; 
                        break;
                    }
                    push(qs, newpqi(step2, curr.second+1));
                    visited[step2.q[0]][step2.q[1]][step2.q[2]][step2.q[3]] = true;
                }
            }
            if(steps>0)
                break;
        }
        printf("%d\n", steps);
    }
    return 0;
}
