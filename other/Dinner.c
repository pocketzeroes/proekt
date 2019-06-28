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
typedef struct{
  int first;
  int second;
}pair;
pair newPair(int a, int b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
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
///////////////////////////////////
int n, maxp;
vec G[600][2];

bool go(int v, int*part, int*sz){
  while(v <= n && part[v] != -1)
    ++v;
  if (v > n)
    return true;
  int npart[600], nsz[2];
  for (int p = 0; p < 2; ++p){
    Queue*Q = newQueue();//of pair
    memcpy(npart+1, part+1, sizeof(int)*n);
    nsz[0] = sz[0];
    nsz[1] = sz[1];
    push(Q, newPair(v, p));
    bool ok = true;
    while (ok && !empty(Q)){
      int w = front(Q).first,
          p = front(Q).second;
      pop(Q);
      if(npart[w] != -1 && npart[w] == p)
        continue;
      else if(npart[w] != -1 || nsz[p] == maxp)
        ok = false;
      else{
        npart[w] = p;
        ++nsz[p];
        for(int z=0; z<G[w][p].sz; z++){int it = G[w][p].ptr[z];
          push(Q, newPair(it, 1-p));
        }
      }
    }
    if(ok && go(v+1, npart, nsz))
      return true;
  }
  return false;
}
bool cansplit() {
  int part[600], sz[2];
  memset(part, -1, sizeof(part));
  sz[0] = sz[1] = 0;
  return go(1, part, sz);
}
int main(){
  int c, meet[600][600];
  scanf("%d %d", &n, &c);
  maxp = 2*n/3;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      meet[i][j] = 2008;
  for (int i = 0; i < c; ++i){
    int a, b, y;
    scanf("%d %d %d", &a, &b, &y);
    meet[a][b] = meet[b][a] = y;
  }
  for (c = 1948; c <= 2008; ++c){
    for (int i = 1; i <= n; ++i){
      G[i][0].sz=0;
      G[i][1].sz=0;
      for(int j = 1; j <= n; ++j)
        if(i != j)
          G[i][meet[i][j]<c].ptr = pushback(G[i][meet[i][j]<c].ptr, &G[i][meet[i][j]<c].sz, j);
    }
    if(cansplit())
      break;
  }
  if(c <= 2008)
    printf("%d\n", c);
  else
    puts("Impossible");
  return 0;
}
