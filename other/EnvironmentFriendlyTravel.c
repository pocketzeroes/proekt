#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
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
#endif/////////
enum{ MAXN = 1005};
enum{ MAXB = 105 };
int N, B;
int dist[MAXN][MAXB];

typedef struct{
  int pos, fst, snd;
}trip;
trip newtrip(int a, int b, int c){
  return(trip){a,b,c};
}
#define pbt(zpv, zvv) zpv.ptr = pushbackT(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
trip*pushbackT(trip*array, int *size, trip value){
  trip*output = resizeArray(array, trip, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
  trip*ptr;
  int sz;
}vect;
vect newVecT(){
  vect rez;
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
}
vect gph[MAXN];
typedef struct{
  int first, second;
}pair;
pair newpair(int a, int b){
  return(pair){a,b};
}
#define pbp(zpv, zvv) zpv.ptr = pushbackP(zpv.ptr, &zpv.sz, zvv)
pair*pushbackP(pair*array, int *size, pair value){
  pair*output = resizeArray(array, pair, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	pair*ptr;
	int sz;
}vecp;
vecp newVecP(){
	vecp rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}


typedef struct{
  int pos ,
      fst ,
      dist;
}node;
node*mknode(int a, int b, int c){
  node*rv=calloc(1, sizeof(node));
  rv->pos =a;
  rv->fst =b;
  rv->dist=c;
  return rv;
}
int cmpN(void*pa, void*pb){
  node*t=(node*)pa;
  node*n=(node*)pb;
  return(t->dist > n->dist)?-1:1;
}

void solve(){
  memset(dist, 0x3f, sizeof(dist));
  PriorityQueue*pq = newPriorityQueue(cmpN);//node
  void enq(int x, int y, int z){
    if(y > B)
      return;
    if(dist[x][y] > z){
      dist[x][y] = z;
      push(pq, mknode(x, y, z));
    }
  }
  enq(0, 0, 0);
  while(size(pq)){
    node*tq=top(pq); node x = *tq; pop(pq);
    if(x.pos ==  1){
      printf("%d\n", x.dist);
      return;
    }
    for(int z=0;z<gph[x.pos].sz;z++){trip i=gph[x.pos].ptr[z];
      enq(i.pos, x.fst + i.fst, x.dist + i.snd);
    }
  }
  puts("-1");
}
int main(){
  pair  a[MAXN];
  int T,C[MAXN];
  for(int i=0; i<2; i++)
    scanf("%d %d", &a[i].first, &a[i].second);
  scanf("%d", &B);
  scanf("%d", &C[0]);
  scanf("%d", &T);
  for(int i=1; i<=T; i++)
    scanf("%d", &C[i]);
  scanf("%d", &N);
  vecp aux[N+2]; clr(aux);
  for(int i=1; i<=N+1; i++)
    pbp(aux[0], newpair(i, 0));
  for(int i=2; i<=N+1; i++)
    pbp(aux[i], newpair(1, 0));
  for(int i=2; i<=N+1; i++){
    scanf("%d %d", &a[i].first, &a[i].second);
    int q;
    scanf("%d", &q);
    while(q--){
      int x, y;
      scanf("%d %d", &x, &y);
      pbp(aux[i], newpair(x+2, y));
    }
  }
  N += 2;
  for(int i=0; i<N; i++){
    for(int z=0;z<aux[i].sz;z++){pair j=aux[i].ptr[z];
      int p = j.first;
      int q = j.second;
      int k = (int)ceil(hypot(a[i].first-a[p].first, a[i].second-a[p].second)-1e-9);
      pbt(gph[i], newtrip(p, k, k*C[q]));
      pbt(gph[p], newtrip(i, k, k*C[q]));
    }
  }
  solve();
  return 0;
}
