#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
#define pb(zpv, zvv) zpv.ptr = pushbackD(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
double *pushbackD(double *array, int *size, double value) {
  double *output = resizeArray(array, double, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
  double*ptr;
  int sz;
}vecd;
vecd newVecD(){
  vecd rez;
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
}
////////////////////////////////////
typedef struct{//Visit
  int    node;
  double cost;
}Visit;
Visit*mkVisit(int i, double d){
  Visit*rv=calloc(1, sizeof(Visit));
  rv->node=i;
  rv->cost=d;
  return rv;
}
int compV(void*pa, void*pb){
  Visit*this =(Visit*)pa;
  Visit*other=(Visit*)pb;
  return(this->cost > other->cost)?-1:1;
}
#if 1 // pq
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

int main(){
  int n, e, p;
  scanf("%d %d %d", &n, &e, &p);
  vecd xs=newVecD();
  vecd ys=newVecD();
  for(int i=0; i<n; i++){
    double x, y;
    scanf("%lf %lf", &x, &y);
    pb(xs, x);
    pb(ys, y);
  }
  double adj[n*n];
  for(int i=0; i<n; i++)
    for(int j=0; j<n; j++)
      adj[i*n + j] = sqrt( (xs.ptr[i]-xs.ptr[j])*(xs.ptr[i]-xs.ptr[j]) + (ys.ptr[i]-ys.ptr[j])*(ys.ptr[i]-ys.ptr[j]) );
  for(int i=0; i<p; i++){
    int a, b;
    scanf("%d%d", &a, &b);
    a--, b--;
    adj[a*n + b] = 0;
    adj[b*n + a] = 0;
  }
  bool visited[n]; clr(visited);
  PriorityQueue*q=newPriorityQueue(compV);// of Visit
  for(int i=0; i<e; i++){
    push(q, mkVisit(i, 0.0));
  }
  double tot = 0.;
  while(!empty(q)){
    Visit*tq=top(q); Visit next = *tq; pop(q);
    if(visited[next.node])
      continue;
    visited[next.node] = true;
    tot += next.cost;
    for(int i=0; i<n; i++){
      if(visited[i])
        continue;
      push(q, mkVisit(i, adj[next.node*n+i]));
    }
  }
  printf("%.30lf\n", tot);
  return 0;
}
