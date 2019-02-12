#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

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
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
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
void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
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
int   push(PriorityQueue*, void*);
void* top(PriorityQueue*);
void* pop(PriorityQueue*);
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
int coompP(void*pa, void*pb){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first == b->first)
    return(a->second < b->second)?-1:1;
  return(a->first < b->first)?-1:1;
}
#endif
////////////////////////
enum{ maxn =(int) 1e5 };
enum{ INF  =(int) 21e8};
int N, M, S, T;
int indeg[maxn + maxn];
vecp E[maxn + maxn];

int run(){
  int d[N+N];
  fill(d, N+N, INF);
  for(int i=0; i!=N; ++i)
    d[i+i] = -INF;
  PriorityQueue*pq = newPriorityQueue(coompP);//pair
  push(pq, mkPair(-(d[T + T] = 0), T + T));
  push(pq, mkPair(-(d[T+1+T] = 0), T+1+T));
  while(!empty(pq)){
    pair*cur = top(pq); pop(pq);
    if(-cur->first != d[cur->second])
      continue;
    if(cur->second == S + S)
      return -cur->first;
    if(cur->second & 1){
      for(int z=0;z<E[cur->second].sz;z++){pair nxt = E[cur->second].ptr[z];
        int alt = nxt.second - cur->first;
        if(alt > d[nxt.first])
          d[nxt.first] = alt;
        if(--indeg[nxt.first] == 0)
          push(pq, mkPair(-d[nxt.first], nxt.first));
      }
    }
    else{
      for(int z=0;z<E[cur->second].sz;z++){pair nxt = E[cur->second].ptr[z];
        int alt = nxt.second - cur->first;
        if(alt < d[nxt.first]){
          d[nxt.first] = alt;
          push(pq, mkPair(-alt, nxt.first));
        }
      }
    }
  }
  return INF;
}
int main(int taskH, char**bapc){
  scanf("%d %d %d %d", &N, &M, &S, &T);
  for(int i=0; i!=M; ++i){
    int u, v, t;
    scanf("%d %d %d", &v, &u, &t);
    E[u+u].ptr = pushbackP(E[u+u].ptr, &E[u+u].sz, newPair(v + v + 1, t));
    indeg[v+1+v]++;
    E[u+u+1].ptr = pushbackP(E[u+u+1].ptr, &E[u+u+1].sz, newPair(v + v, t));
    indeg[v + v]++;
  }
  int answer = run();
  if(answer == INF)
    puts("infinity");
  else
    printf("%d\n", answer);
  return 0;
}
