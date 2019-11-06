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
    int v, w;
}edge;
edge newedge(int v, int w){
    return(edge){v,w};
}
edge*mkedge(int v, int w){
    edge*rv=calloc(1, sizeof(edge));
    rv->v=v;
    rv->w=w;
    return rv;
}
int cmpE(void*a, void*b){
    edge*l=(edge*)a;
    edge*r=(edge*)b;
    return(l->w > r->w)?-1:1;
}
#define pbe(zpv, zvv) zpv.ptr = pushbackE(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
edge*pushbackE(edge*array, int *size, edge value){
  edge*output = resizeArray(array, edge, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
    edge*ptr;
    int sz;
}vece;
vece newVecE(){
    vece rez;
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


////////////////////////////////////

int main(){
    int n, m, olsenwalk, larsenwalk;
    scanf("%d %d", &n, &m);
    vece G[n]; clr(G);
    int u,k,w;
    while(m--){
        scanf("%d %d %d", &u, &k, &w);
        pbe(G[u], newedge(k,w));
        pbe(G[k], newedge(u,w));
    }
    PriorityQueue*pq = newPriorityQueue(cmpE);// of edge
    bool v[n]; clr(v);
    push(pq, mkedge(0,0));
    while(!empty(pq)){
        edge*tq = top(pq);
        u = tq->v; 
        w = tq->w; pop(pq);
        if(u == n-1){
            olsenwalk = w;
            break;
        }
        if(v[u])
            continue;
        v[u] = true;
        for(int z=0;z<G[u].sz;z++){edge e = G[u].ptr[z];
            if(!v[e.v])
                push(pq, mkedge(e.v, w+e.w));
        }
    }
    int olsentravel = fmax(0, (olsenwalk-1)/12) * 12 + olsenwalk;
    delPriorityQueue(&pq, free); pq = newPriorityQueue(cmpE);
    clr(v);
    push(pq, mkedge(0,0));
    while(!empty(pq)){
        edge*tq=top(pq);
        u = tq->v;
        w = tq->w; pop(pq);
        if(u == n-1){
            larsenwalk = w;
            break;
        }
        if(v[u])
            continue;
        v[u] = true;
        for(int z=0;z<G[u].sz;z++){edge e = G[u].ptr[z];
            if(e.w <= 12){
                int alt = -1;
                if((w % 12) + e.w <= 12)
                    alt = w + e.w;
                else
                    alt = w + 12 - (w % 12) + e.w;
                push(pq, mkedge(e.v, alt));
            }
        }
    }
    int larsentravel = fmax(0, (larsenwalk - 1) / 12) * 12 + larsenwalk;
    printf("%d\n", larsentravel-olsentravel);
    return 0;
}
