#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
typedef struct{
    int first;
    int second;
}pair;
pair newpair(int a, int b){
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

typedef struct{
    int first;
    int second;
    int third;
}trip;
trip*mktrip(int a, int b, int c){
    trip*rv = calloc(1, sizeof(trip));
    rv->first =a;
    rv->second=b;
    rv->third =c;
    return rv;
}
int compT(void*pa, void*pb){
    trip*lhs=(trip*)pa;
    trip*rhs=(trip*)pb;
    if(lhs->second == rhs->second)
        return(lhs->third < rhs->third)?-1:1;
    else
        return(lhs->second > rhs->second)?-1:1;
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

vecp*edges;
int* packs;
int  V;
int  shortest;
int  package_sum;

void Graph(){
    scanf("%d", &V);
    edges       = calloc(V+1, sizeof(vecp));
    packs       = calloc(V+1, sizeof(int));
    shortest    = 2147483647;
    package_sum = 0;
}
void dGraph(){
    free(edges);
    free(packs);
}
void read_packages(){
    for(int i = 1; i <= V; i++)
        scanf("%d", packs + i);
}
void read_edges(){
    int E;
    scanf("%d",&E);
    while(E--){
        int a, b, d;
        scanf("%d %d %d", &a, &b, &d);
        pbp(edges[a], newpair(b, d));
        pbp(edges[b], newpair(a, d));
    }
}
bool possible(){
    return shortest != 2147483647;
}
void search(){
    PriorityQueue*pq=newPriorityQueue(compT);//of trip
    push(pq, mktrip(1, 0, packs[1]));
    bool visited[V+1]; clr(visited);
    while(!empty(pq)){
        trip*tq=top(pq); trip current = *tq; pop(pq);
        if(current.first == V){
            shortest    = current.second;
            package_sum = current.third;
            break;
        }
        if(visited[current.first])
            continue;
        visited[current.first] = true;
        for(int z=0; z<edges[current.first].sz; z++){pair it = edges[current.first].ptr[z];
            if(!visited[it.first])
                push(pq, mktrip(it.first, current.second+it.second, current.third+packs[it.first]));
        }
    }
}
int main(){
    Graph();
    read_packages();
    read_edges();
    search();
    if(possible())
        printf("%d %d\n", shortest, package_sum);
    else
        printf("impossible\n");
    return 0;
}
