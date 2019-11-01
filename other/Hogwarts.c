#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
#define pbq(zpv, zvv) zpv.ptr = pushbackQ(zpv.ptr, &zpv.sz, zvv)
#define pb(zpv, zvv) zpv.ptr = pushback(zpv.ptr, &zpv.sz, zvv)

typedef struct{
  int q[4];
}quad;
quad newquad(int a, int b, int c, int d){
  quad rez;
  rez.q[0]=a;
  rez.q[1]=b;
  rez.q[2]=c;
  rez.q[3]=d;
  return rez;
}

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
quad*pushbackQ(quad*array, int *size, quad value){
  quad*output = resizeArray(array, quad, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	quad*ptr;
	int sz;
}vecq;
vecq newVecQ(){
	vecq rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

int *pushback(int *array, int *size, int value) {
  int *output = resizeArray(array, int, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
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
////////////////////////////
int n;

int convert(int i, int j){
  return i * (n+1) + j;
}
int main(){
  scanf("%d", &n);
  vecq adj1 = newVecQ();// of quad
  vecq adj2 = newVecQ();// of quad
  pbq(adj1, newquad(0,0,0,0));
  pbq(adj2, newquad(0,0,0,0));
  for(int i=0; i<n; i++){
    quad v;
    for(int z=0;z<4;z++)
      scanf("%d", &v.q[z]);
    pbq(adj1, v);
  }
  for(int i=0; i<n; i++){
    quad v;
    for(int z=0;z<4;z++)
      scanf("%d", &v.q[z]);
    pbq(adj2, v);
  }
  vec adj[(n+1)*(n+1)]; clr(adj);
  for(int k = 0; k < 4; k++){
    for(int i = 0; i <= n; i++){
      for(int j = 0; j <= n; j++){
        int ni = adj1.ptr[i].q[k];
        int nj = adj2.ptr[j].q[k];
        int idx = convert(i,j);
        pb(adj[idx], convert(ni,nj));
      }
    }
  }
  bool vis[(n+1)*(n+1)]; clr(vis);
  Queue*q = newQueue();
  push(q, convert(1,1));
  while(!empty(q)){
    int curr = front(q); pop(q);
    if(vis[curr])
      continue;
    vis[curr] = true;
    for(int z=0;z<adj[curr].sz;z++){int next = adj[curr].ptr[z];
      push(q, next);
    }
  }
  bool sworks = false;
  bool works  = true;
  for(int i = 0; i <= n; i++)
    if(vis[convert(n,i)])
      sworks = true;
  for(int i=0; i<n; i++)
    if(vis[convert(n,i)])
      works = false;
  if(!sworks)
    puts("Impossible");
  else if(works)
    puts("Yes");
  else
    puts("No");
  return 0;
}
