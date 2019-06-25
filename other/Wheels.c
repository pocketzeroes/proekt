#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

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
//////////////////////
typedef long long ll;

int gcd(int a, int b){
    if (a<b)
        return gcd(b,a);
    if (b==0)
        return a;
    return gcd(b,a%b);
}
ll sq(int x){
    return x*(ll)x;
}
int main(){
    int TT;
    scanf("%d", &TT);
    while(TT--){
        int n;
        scanf("%d", &n);
        int X     [n];
        int Y     [n];
        int R     [n];
        int moving[n]; memset(moving, 0, sizeof(moving));
        for(int i=0; i<n; i++)
            scanf("%d %d %d", &X[i], &Y[i], &R[i]);
        Queue*Q = newQueue();
        push(Q, 0);
        moving[0] = 1;
        while(!empty(Q)){
            int u = front(Q); pop(Q);
            for(int i=0; i<n; i++){
                if (moving[i]==0 && sq(X[i]-X[u])+sq(Y[i]-Y[u])==sq(R[i]+R[u])){
                    moving[i] = -moving[u];
                    push(Q, i);
                }
            }
        }
        for(int i=0; i<n; i++){
            if (moving[i]==0)
                puts("not moving");
            else{
                int d = gcd(R[0],R[i]);
                printf("%d", R[0]/d);
                if(R[i]>d)
                    printf("/%d", R[i]/d);
                puts(moving[i]==1 ? " clockwise" : " counterclockwise");
            }
        }
    }
    return 0;
}
