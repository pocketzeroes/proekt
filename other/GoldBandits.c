#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int max(int a,int b){return a>b?a:b;}

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
vec newVec(){
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

typedef struct{
  int first;
  int second;
}pair;
int compP(void*pb, void*pa){//rev
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}
#if 1
pair*mkPair(int a, int b){
  pair*rez = malloc(sizeof(pair));
  rez->first  = a;
  rez->second = b;
  return rez;
}
#ifndef __HEAP_H_GUARD__
#define __HEAP_H_GUARD__
#define HEAP_STARTING_SIZE 256
struct heap_st;
typedef struct heap_st PriorityQueue;
PriorityQueue* newPriorityQueue(int(*)(void*, void*));
int   pushq(PriorityQueue*, void*);
void* topq(PriorityQueue*);
void* popq(PriorityQueue*);
void delPriorityQueue(PriorityQueue**, void(*)(void*));
#endif
struct heap_st {
  void** info;
  int(*compareFunction)(void*, void*);
  unsigned used;
  unsigned currentSize;
};
PriorityQueue* newPriorityQueue(int(*compareFunction)(void*, void*)) {
  PriorityQueue* newHeap = (PriorityQueue*)malloc(sizeof(PriorityQueue));
  if (newHeap == NULL) {
    return NULL;
  }
  newHeap->info = (void**)malloc(HEAP_STARTING_SIZE * sizeof(void*));
  if (newHeap->info == NULL) {
    free(newHeap);
    return NULL;
  }
  newHeap->used = 0;
  newHeap->currentSize = HEAP_STARTING_SIZE;
  newHeap->compareFunction = compareFunction;
  return newHeap;
}
int  pushq(PriorityQueue* h, void* data) {
  if (h == NULL) {
    return 0;
  }
  if (h->used == 0) {
    h->info[0] = data;
    h->used = 1;
    return 1;
  }
  if (h->used == h->currentSize) {
    unsigned newSize = h->currentSize * 2;
    void** newIndexes = (void**)realloc(h->info, newSize * sizeof(PriorityQueue));
    if (newIndexes == NULL) {
      return 0;
    }
    h->info = newIndexes;
    h->currentSize = newSize;
  }
  h->info[h->used] = data;
  unsigned index, parentIndex;
  index = h->used;
  do {
    parentIndex = (index - 1) / 2;
    if (h->compareFunction(data, h->info[parentIndex]) > 0) {
      h->info[index] = h->info[parentIndex];
      h->info[parentIndex] = data;
      index = parentIndex;
    }
    else {
      break;
    }
  } while (parentIndex != 0);
  h->used++;
  return 1;
}
void*topq(PriorityQueue*h) {
  if (h == NULL || h->used == 0) {
    return NULL;
  }
  return h->info[0];
}
void*popq(PriorityQueue*h) {
  if (h == NULL || h->used == 0) {
    return NULL;
  }
  void* toRet = h->info[0];
  if (h->used == 1) {
    h->info[0] = NULL;
    h->used--;
    return toRet;
  }
  h->used--;
  h->info[0] = h->info[h->used];
  h->info[h->used] = NULL;
  unsigned left, right, current = 0, index;
  do {
    index = current;
    left = (current * 2) + 1;
    right = (current * 2) + 2;
    if (left < h->used && h->compareFunction(h->info[left], h->info[current]) > 0) {
      if (right < h->used && h->compareFunction(h->info[right], h->info[current]) > 0 &&
        h->compareFunction(h->info[right], h->info[left]) > 0) {
        current = right;
      }
      else {
        current = left;
      }
    }
    else if (right < h->used && h->compareFunction(h->info[right], h->info[current]) > 0) {
      current = right;
    }
    if (current != index) {
      void* swap = h->info[current];
      h->info[current] = h->info[index];
      h->info[index] = swap;
    }
  } while (index != current);
  return toRet;
}
void delPriorityQueue(PriorityQueue** h, void(*freeFunction)(void*)) {
  if (h == NULL || *h == NULL) {
    return;
  }
  if (freeFunction != NULL) {
    unsigned i;
    for (i = 0; i < (*h)->used; ++i) {
      freeFunction((*h)->info[i]);
    }
  }
  free((*h)->info);
  free((*h));
  *h = NULL;
}
int sizeq(PriorityQueue*h) {
  return h->used;
}
bool emptypq(PriorityQueue*h){
  return h->used==0;
}
#endif

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
int    emptyq(Queue *Q);
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
int emptyq(Queue *Q)
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
  if (emptyq(Q))  
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
  if (emptyq(Q))  
  {
    printf("\n**Error in pop: Q is empty?!\n\n");
    exit(-1);
  }
  QueueElementType e = Q->Elements[Q->Front];
  return e;
}
#endif

#define X first
#define Y second

enum{ maxn =      36};
enum{ oo   =(int)1e9};

int n,m;
int g[maxn+1];
vec V[maxn+1];
int dis[3][maxn+1];
Queue*Q;
bool busy[maxn+1];
bool lock[maxn+1];
int lose[maxn+1];
int sum,res;
PriorityQueue*H;//of pair rev

void bfs(){
    for (int i=1; i<=2; i++){
        for (int j=1; j<=n; j++)
            dis[i][j] = oo;
        dis[i][i] = 0;
        push(Q, i);
        do{
            int p = front(Q); pop(Q);
            for(int z=0; z<V[p].sz; z++){int it = V[p].ptr[z];
                int q = it;
                if (dis[i][q] > dis[i][p] + 1){
                    dis[i][q] = dis[i][p] + 1;
                    push(Q, q);
                }
            }
        }
        while(!emptyq(Q));
    }
}
void check(){
    while(!emptypq(H))
        popq(H);
    for(int i=1; i<=n; i++)
        lose[i] = oo;
    lose[2] = 0;
    pushq(H, mkPair(0,2));
    do{
        pair*tmp = topq(H);
        int tmpX=tmp->X;
        int tmpY=tmp->Y;
        popq(H);
        if(lose[tmpY] < tmpX)
            continue;
        int p=tmpY;
        for(int z=0; z<V[p].sz; z++){int it = V[p].ptr[z];
            int q = it;
            int cost = 0;
            if(busy[q])
                cost = g[q];
            if(lose[q]>lose[p]+cost){
                lose[q] = lose[p]+cost;
                pushq(H, mkPair(lose[p]+cost,q));
            }
        }
    }
    while(!emptypq(H));
    res = max(res, sum-lose[1]);
    if(res == 5317){
        printf("%d ", busy[1]);
        for(int i=1; i<=n; i++)
            if(busy[i]) 
                printf("%d ", i);
        puts("");
    }
}
void quay(int x){
    if (x==2){
        check();
        return;
    }
    for(int z=0; z<V[x].sz; z++){int it = V[x].ptr[z];
        int y=it;
        if (dis[1][y]+dis[2][y]==dis[1][2] && dis[1][y]>dis[1][x]){
            busy[y] = true;
            sum+=g[y];
            quay(y);
            sum-=g[y];
            busy[y] = false;
        }
    }
}
int main(){
    Q = newQueue();
    H = newPriorityQueue(compP);
    while(scanf("%d %d", &n, &m)==2 && n!=0){
        for(int i=1; i<=n; i++)
            V[i].sz=0;
        g[1] = 0;
        g[2] = 0;
        for(int i=3; i<=n; i++)
            scanf("%d", &g[i]);
        for(int i=1; i<=m; i++){
            int a, b;
            scanf("%d %d", &a, &b);
            V[a].ptr = pushback(V[a].ptr, &V[a].sz, b);
            V[b].ptr = pushback(V[b].ptr, &V[b].sz, a);
        }
        bfs();
        memset(busy, false, sizeof(busy));
        sum = 0;
        res = 0;
        busy[1] = true;
        quay(1);
        printf("%d\n", res);
    }
    return 0;
}
