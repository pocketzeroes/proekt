#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
enum{INF = 20000000};
void fill(int*arr,int sz, int val){
  for(int i=0;i<sz;i++)
    arr[i]=val;
}

typedef struct{
  int to, weight;
}edge;
edge newedge(int a, int b){
  return(edge){a,b};
}
edge*mkedge(int a, int b){
  edge*rv=calloc(1, sizeof(edge));
  rv->to     = a;
  rv->weight = b;
  return rv;
}
int cmpE(void*a,void*b){
  edge*t=(edge*)a;
  edge*e=(edge*)b;
  return(t->weight > e->weight)?-1:1;
}
typedef struct{
  edge first, second;
}pair;
pair newpair(edge a, edge b){
  return(pair){a,b};
}
#define pbp(zpv, zvv) zpv.ptr = pushbackP(zpv.ptr, &zpv.sz, zvv)
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
///////////////////////////
int f(int t0, int P, int dist){
  if(P == 0){
    if(t0 >= dist)
      return t0-dist;
    else
      return INF;
  }
  if(t0 >= dist)
    return(t0-dist);
  int t =(dist-t0+P-1)/P;
  return t0+t*P-dist;
}
int n,m,qq,s,u,v,w;
int t0,P,d;

int main(){
  while(scanf("%d %d %d %d", &n, &m, &qq, &s) && n){
    vecp adjlist[n]; clr(adjlist);//pair{edge,edge}
    for(int i=0; i<m; i++){
      scanf("%d %d %d %d %d", &u, &v, &t0, &P, &d);
      pbp(adjlist[u], newpair(newedge(v, t0), newedge(P, d)));
    }
    int*dist = calloc(n+1, sizeof(int)); fill(dist, n+1, INF);
    PriorityQueue*q = newPriorityQueue(cmpE);//of edge
    push(q, mkedge(s, 0));
    dist[s] = 0;
    while(!empty(q)){
      edge*tq=top(q);
      int u = tq->to; pop(q);
      for(int i=0; i<adjlist[u].sz; i++){
        v  = adjlist[u].ptr[i].first.to;
        t0 = adjlist[u].ptr[i].first.weight;
        P  = adjlist[u].ptr[i].second.to;
        d  = adjlist[u].ptr[i].second.weight;
        w  = f(t0, P, dist[u]) + d;
        if(dist[u] + w < dist[v]){
          dist[v] = dist[u] + w;
          push(q, mkedge(v, dist[v]));
        }
      }
    }
    for(int i=0; i<qq; i++){
      scanf("%d", &u);
      if(dist[u] == INF)
        puts("Impossible");
      else
        printf("%d\n", dist[u]);
    }
    puts("");
  }
  return 0;
}
