#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

#if 1 //que
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

#define pb(zpv, zvv) zpv.ptr = pushback(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
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

 
enum{ MAXN = 1000000};
int N, in[MAXN], visited[MAXN];
vec graph[2][MAXN];
 
int main(){
  int tc=1;
  for(int z=0;z<tc;z++){
    scanf("%d", &N);
    if (!N) 
      break;
    for(int i = 0; i < N; ++i){
      graph[0][i].sz=0;
      graph[1][i].sz=0;
      visited[i] = 0;
    }
    for(int i = 0; i < N; ++i){
      scanf("%d", in+i);
      if(i+in[i] < N)
        pb(graph[0][i+in[i]], i);
      if(i-in[i] >= 0)
        pb(graph[1][i-in[i]], i);
    }
    Queue*q=newQueue();
    visited[0] = 1;
    push(q,0);
    while (!empty(q)) {
      int node = front(q);pop(q);
      int mid = node + in[node];
      if (mid < N) {
        for (int i = 0; i < graph[1][mid].sz; ++i){ int next = graph[1][mid].ptr[i];
          if (!visited[next]) {
            visited[next] = 1;
            push(q, next);
          }
        }
      }
      mid = node - in[node];
      if (mid >= 0) {
        for (int i = 0; i < graph[0][mid].sz; ++i){ int next = graph[0][mid].ptr[i];
          if(!visited[next]){
            visited[next] = 1;
            push(q, next);
          }
        }
      }
    }
    int result = N-1;
    while (!visited[result])
      --result;
    printf("%d\n", result);
  }
  return 0;
}
