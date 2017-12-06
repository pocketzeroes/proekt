#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>


#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}

typedef struct vecS {
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;// = malloc(sizeof(vec));
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
    assert(!"error in pop -1\n");
    exit(0);
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
    printf("-1\n");
    exit(0);
  }
  QueueElementType e = Q->Elements[Q->Front];
  return e;
}
int isElementInQueue(Queue *Q, QueueElementType e)
{
  int  i = Q->Front;
  int  count;
  for (count = 0; count < Q->NumElements; ++count)
  {
    if (Q->Elements[i] == e)  
      return 1;  
    ++i;
    if (i == Q->Capacity)  
      i = 0;
  }
  return 0;
}

#endif

enum{ ONE = 200005    };
enum{ INF = 2147483640};

vec A[ONE];
int minn = INF;
int n, m, k;
int next[ONE], first[ONE], go[ONE], Input[ONE], tot;
Queue*q;
int p[ONE];



int get(){
    int x;
    scanf("%d", &x);
    return x;
}
void Add(int u, int v){
    Input[v]++, next[++tot] = first[u], first[u] = tot, go[tot] = v;
}
void Deal(){
        int now = 0;
        for(int i = 1; i <= k; i++) 
            if(!Input[i] && i != minn)
                push(q, i);
        for(int i = 1; i <= k; i++)
            if(!Input[i] && i == minn)
                push(q, i);
        if(front(q) == minn){
            printf("-1");
            exit(0);
        }
        while(!empty(q)){
            int u = front(q); pop(q);
            p[u] = ++now;
            for(int e = first[u]; e; e = next[e]){
                int v = go[e];
                if(--Input[v] == 0) 
                    push(q, v);
            }
        }
        if(now != k) {
            printf("-1"); 
            exit(0);
        }
        for(int i = 1; i <= k; i++)
            printf("%d ", p[i] - 1);
}
int main(){
    q = newQueue();
    n = get(), k = get(), m = get();
    for(int i = 1; i <= n; i++){
        A[i].ptr = pushback(A[i].ptr, &A[i].sz, -1);
        for(int j = 1; j <= m; j++)
            A[i].ptr = pushback(A[i].ptr, &A[i].sz, get() + 1);
    }
    minn = A[1].ptr[1];
    for(int i = 1; i < n; i++)
        for(int j = 1; j <= m; j++)
            if(A[i].ptr[j] != A[i + 1].ptr[j] || j == m){
                Add(A[i].ptr[j], A[i + 1].ptr[j]); 
                break;
            }
    Deal();
}


