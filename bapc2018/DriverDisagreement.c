#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>


void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
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
typedef struct{
  pair first;
  int second;
}trip;
trip newTrip(pair a, int b){
  trip rez;
  rez.first  = a;
  rez.second = b;
  return rez;
}


#if 1 //queueue
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

/////////////////
int*du_parent;
int*du_rank;

void init(int n){
  du_parent = calloc(n, sizeof(int)); //-1);
  fill(du_parent, n, -1);
  du_rank   = calloc(n, sizeof(int));
}
int find(int k){
  if (du_parent[k] == -1)
    return k;
  du_parent[k] = find(du_parent[k]);
  return du_parent[k];
}
void dunion(int a, int b){
  a = find(a);
  b = find(b);
  if (a == b)
    return;
  if (du_rank[a] < du_rank[b]){
    du_parent[b] = a;
  }
  else{
    du_parent[a] = b;
    if (du_rank[b] == du_rank[a])
      du_rank[b]++;
  }
}
typedef struct{
  int  left;
  int  right;
  bool tower;
}node;

int main(int taskD, char**bapc){
  int n, a, b;
  scanf("%d %d %d", &n, &a, &b);
  node graph[n];
  for(int i=0; i<n; i++){
    scanf("%d %d %d", &graph[i].left, &graph[i].right, &graph[i].tower);
  }
  Queue*work = newQueue();//trip
  init(n);
  push(work, newTrip(newPair(a, b), 0));
  while(!empty(work)){
    trip p = front(work); pop(work);
    if(find(p.first.first) == find(p.first.second))
      continue;
    int  d = p.second;
    node a = graph[p.first.first ];
    node b = graph[p.first.second];
    if(a.tower != b.tower){
      printf("%d\n", d);
      return 0;
    }
    dunion(p.first.first, p.first.second);
    push(work, newTrip(newPair(a.left,  b.left ), d+1));
    push(work, newTrip(newPair(a.right, b.right), d+1));
  }
  puts("indistinguishable");
  return 0;
}
