#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;

typedef struct{
  ll  first;
  int second;
}pli;
pli*mkpli(ll a, int b){
  pli*rv = calloc(1, sizeof(pli));
  rv->first =a;
  rv->second=b;
  return rv;
}
int cmpP(void*pb, void*pa){//rev
  pli*a=(pli*)pa;
  pli*b=(pli*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}

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

#if 1 // p_q
#ifndef __HEAP_H_GUARD__
#define __HEAP_H_GUARD__
#define HEAP_STARTING_SIZE 256
struct heap_st;
typedef struct heap_st PriorityQueue;
PriorityQueue* newPriorityQueue(signed(*)(void*, void*));
int   push(PriorityQueue*, void*);
void* top(PriorityQueue*);
void* pop(PriorityQueue*);
void delPriorityQueue(PriorityQueue**, void(*)(void*));
#endif
struct heap_st {
  void** info;
  signed(*compareFunction)(void*, void*);
  unsigned used;
  unsigned currentSize;
};
PriorityQueue* newPriorityQueue(signed(*compareFunction)(void*, void*)) {
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
int  push(PriorityQueue* h, void* data) {
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
void*top(PriorityQueue*h) {
  if (h == NULL || h->used == 0) {
    return NULL;
  }
  return h->info[0];
}
void*pop(PriorityQueue*h) {
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
int size(PriorityQueue*h) {
  return h->used;
}
bool empty(PriorityQueue*h){
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
int    qempty(Queue *Q);
int    qpush(Queue *Q, QueueElementType e);
QueueElementType qpop(Queue *Q);

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
int qempty(Queue *Q)
{
  return Q->NumElements == 0;
}
int qsize(Queue *Q)
{
  return Q->NumElements;
}
int qpush(Queue *Q, QueueElementType e)
{
  if (Q->NumElements == Q->Capacity)
  {
    int N = 2 * Q->Capacity;
    QueueElementType *newE = (QueueElementType *)malloc(N * sizeof(QueueElementType));
    if (newE == NULL)
    {
      printf("\n**Error in qpush: malloc failed _to allocate\n\n");
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
QueueElementType qpop(Queue *Q)
{
  if (qempty(Q))
  {
    printf("\n**Error in qpop: Q is qempty?!\n\n");
    exit(-1);
  }
  QueueElementType e = Q->Elements[Q->Front];
  Q->Front++;
  if (Q->Front >= Q->Capacity)
    Q->Front = 0;
  Q->NumElements--;
  return e;
}
QueueElementType qfront(Queue *Q)
{
  if (qempty(Q))
  {
    printf("\n**Error in qpop: Q is qempty?!\n\n");
    exit(-1);
  }
  QueueElementType e = Q->Elements[Q->Front];
  return e;
}
#endif


//////////////////////////////////////////

ll d[309][309], dr[309][309], inf = 1e18;
int rc[309];
vec rcp[309], rct[309], sv[309];
Queue*sq;


void bfs(int sn){
    while(!qempty(sq))
        qpop(sq);
    qpush(sq, sn);
    while(!qempty(sq)){
        int hn = qfront(sq); qpop(sq);
        for(int i=0; i<sv[hn].sz; i++){int tn = sv[hn].ptr[i];
            if(d[sn][hn] + 1 < d[sn][tn]){
                d[sn][tn] = d[sn][hn] + 1;
                qpush(sq, tn);
            }
        }
    }
}
int main(){
    PriorityQueue*q = newPriorityQueue(cmpP);//of pli rev
    sq = newQueue();
    int tc;
    scanf("%d", &tc);
    for(int ti = 0; ti < tc; ti++){
        int n, m, s, r;
        scanf("%d %d %d %d", &n, &m, &s, &r);
        for(int i=1; i<=n; i++){
            for(int j=1; j<=n; j++){
                if(i == j)
                    d[i][j] = 0;
                else
                    d[i][j] = inf;
            }
            for(int j=1; j<=s; j++)
                dr[i][j] = inf;
            sv[i].sz=0;
        }
        for(int i=1; i<=s; i++)
            rct[i].sz=0;
        for(int i=0; i<m; i++){
            int a, b;
            scanf("%d %d", &a, &b);
            pb(sv[a], b);
            pb(sv[b], a);
        }
        for(int i=1; i<=n; i++)
            bfs(i);
        while(!empty(q))
            pop(q);
        for(int i=1; i<=n; i++){
            int k;
            scanf("%d", &k);
            for(int j=0; j<k; j++){
                int a;
                scanf("%d", &a);
                dr[i][a] = 0;
                push(q, mkpli(0LL, (i - 1) * s + a));
            }
        }
        for(int i=0; i<r; i++){
            int k;
            scanf("%d", &k);
            rcp[i].sz=0;
            for(int j=0; j<k; j++){
                int a;
                scanf("%d", &a);
                pb(rct[a], i);
                pb(rcp[i], a);
            }
            scanf("%d", &rc[i]);
        }
        while(!empty(q)){
            pli*tq=top(q);
            ll  hc = tq->first;
            int hl = tq->second; pop(q);
            int hn = (hl - 1) / s + 1, hr = hl - (hn - 1) * s;
            if(hc != dr[hn][hr])
                continue;
            for(int i=1; i<=n; i++){
                if(hn == i)
                    continue;
                if(dr[hn][hr] + d[hn][i] < dr[i][hr]){
                   dr[i][hr] = dr[hn][hr] + d[hn][i];
                   push(q, mkpli(dr[i][hr], (i - 1) * s + hr));
                }
            }
            for(int i=0; i<rct[hr].sz; i++){
                ll ks = 0;
                int ri = rct[hr].ptr[i];
                for(int j=0; j<rcp[ri].sz; j++)
                    ks += dr[hn][rcp[ri].ptr[j]];
                if(ks < dr[hn][rc[ri]]){
                    dr[hn][rc[ri]] = ks;
                    push(q, mkpli(ks, (hn - 1) * s + rc[ri]));
                }
            }
        }
        ll mn = inf;
        for(int i=1; i<=n; i++)
            mn = fminl(mn, dr[i][1]);
        if(mn >= 1000000000000LL)
           mn = -1;
        printf("Case #%d: %lld\n", ti+1, mn);
    }
    return 0;
}
