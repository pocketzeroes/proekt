#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

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

void fill(int*arr,int sz, int val){
  for(int i=0;i<sz;i++)
    arr[i]=val;
}
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
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
//////////////////
int MAX=1<<25;
int n;

void bfs(vec*graph, int*start, int len, int*dists){
  fill(dists, n, MAX);
  Queue*q = newQueue();
  for(int z=0;z<len;z++){int s = start[z];
    push(q, s);
    dists[s]=0;
  }
  while(!empty(q)){
    int cur = front(q);
    for(int z=0;z<graph[cur].sz;z++){int next = graph[cur].ptr[z];
      if(dists[next]==MAX){
         dists[next] = dists[cur]+1;
         push(q, next);
      }
    }
    pop(q);
  }
}
void read_vector(int*v, int s){
  int in;
  for(int i=0; i<s; i++){
    scanf("%d", &in);
    in--;
    v[i] = in;
  }
}
void rd_vec(vec*v, int s){
  int in;
  for(int i=0; i<s; i++){
    scanf("%d", &in);
    in--;
    v->ptr = pushback(v->ptr, &v->sz, in);
  }
}
int main(){
  int m, k;
  scanf("%d %d %d", &n, &m, &k);
  int ores [m]; read_vector(ores , m);
  int coals[k]; read_vector(coals, k);
  vec graph    [n]; memset(graph    , 0, sizeof(graph    ));
  vec rev_graph[n]; memset(rev_graph, 0, sizeof(rev_graph));
  for(int i=0; i<n; i++){
    int a;
    scanf("%d", &a);
    rd_vec(&graph[i], a);
    for(int j=0; j<a; j++){
      int idx = graph[i].ptr[j];
      rev_graph[idx].ptr = pushback(rev_graph[idx].ptr, &rev_graph[idx].sz, i);
    }
  }
  int dist_root[n];
  int dist_ore [n];
  int dist_coal[n];
  int dummy[5]={0};
  bfs(graph,    dummy,  1, dist_root);
  bfs(rev_graph, ores,  m, dist_ore );
  bfs(rev_graph, coals, k, dist_coal);
  int best = MAX;
  for(int i=0; i<n; i++)
    best = min(best, dist_root[i] + dist_ore[i] + dist_coal[i]);
  if(best>=MAX)
    puts("impossible");
  else
    printf("%d\n", best);
}


















































