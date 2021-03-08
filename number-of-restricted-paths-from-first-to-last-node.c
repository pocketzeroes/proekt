#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

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
void*top(PriorityQueue*h){
  if(h == NULL || h->used == 0){
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

enum{P=1000000007};
typedef struct{
    int d,i;
}node;
node t;
int cmpN(void*pa, void*pb){
    node*x=(node*)pa;
    node*y=(node*)pb;
    return(x->d > y->d)?-1:1;
}
node*mknode(int a, int b){
    node*rv=calloc(1, sizeof(node));
    rv->d = a;
    rv->i = b;
    return rv;
}
int m,h[20005],ne[80005],p[80005],w[80005],d[20005],f[20005],a[20005];

int countRestrictedPaths(int n, int**edges, int edgesSz, int*e0sz){
    PriorityQueue*H=newPriorityQueue(cmpN);//of node
    memset(h,0,sizeof(h));
    m=0;
    for(int z=0;z<edgesSz;z++){int*e=edges[z];
        p[++m]=e[1];
        ne[m]=h[e[0]];
        w[m]=e[2];
        h[e[0]]=m;
        p[++m]=e[0];
        ne[m]=h[e[1]];
        w[m]=e[2];
        h[e[1]]=m;
    }
    memset(d,127,sizeof(d));
    int N=0,i,j;
    d[t.i=n]=t.d=0;
    push(H, mknode(t.d, t.i));
    while(!empty(H)){
        node*tq=top(H);
        t = *tq;
        pop(H);
        if(t.d!=d[t.i])
          continue;
        a[++N]=i=t.i;
        for(j=h[i];j;j=ne[j])
            if(d[p[j]]>d[i]+w[j]){
                d[t.i=p[j]]=t.d=d[i]+w[j];
                push(H, mknode(t.d, t.i));
            }
    }
    memset(f,0,sizeof(f));
    for(i=f[a[1]]=1;i<=n;i++)
      for(j=h[a[i]];j;j=ne[j])
        if(d[p[j]]>d[a[i]]){
          f[p[j]]+=f[a[i]];
          if(f[p[j]]>=P)
            f[p[j]]-=P;
        }
    return f[1];
}
