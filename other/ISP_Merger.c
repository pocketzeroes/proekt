#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

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

////////////////////////////////////////
typedef struct{
    int s, e, c;
}component;
component*mkcomp(component c){
    component*rv=calloc(1, sizeof(component));
    *rv = c;
    return rv;
}
int cmpC(void*pa, void*pb){
    component*tva=(component*)pa;
    component*oth=(component*)pb;
    if(tva->c == 1 && tva->s == 1) return -1;
    if(oth->c == 1 && oth->s == 1) return 1;
    if(tva->c == oth->c)
        return(tva->e < oth->e)?-1:1;
    return(tva->c < oth->c)?-1:1;
}
enum{ MAXN = 100000};
int n, m, k, C[MAXN];
vec  G[MAXN];
bool V[MAXN];

void buildComponent(int u, component*comp){
    if (V[u])
        return;
    V[u] = true;
    comp->s++;
    comp->c += C[u];
    comp->e += G[u].sz;
    for(int z=0;z<G[u].sz;z++){int v = G[u].ptr[z];
        comp->c--;
        if(V[v])
            continue;
        buildComponent(v, comp);
    }
}
int main(){
    scanf("%d %d %d", &n, &m, &k);
    for(int i=0; i<n; i++)
        scanf("%d", &C[i]);
    for(int i=0; i<m; i++){
        int u, v;
        scanf("%d %d", &u, &v);
        pb(G[u], v);
        pb(G[v], u);
    }
    PriorityQueue*comps=newPriorityQueue(cmpC);//of component
    for(int i=0; i<n; i++){
        if(!V[i]){
            component comp = {};
            buildComponent(i, &comp);
            comp.e /= 2;
            comp.e -= comp.s-1;
            if (comp.s == 2 && comp.e == 0 && comp.c == 0 && (i+2 < n || size(comps) > 0)){
                k--;
                comp.s = 1;
                comp.c++;
                push(comps, mkcomp(comp));
                push(comps, mkcomp(comp));
                continue;
            }
            push(comps, mkcomp(comp));
        }
    }
    while(size(comps) > 1 && k > 0){
        component*tq=top(comps); component a = *tq; pop(comps);
                  tq=top(comps); component b = *tq; pop(comps);
        if(a.c > 0 && b.c > 0){
            a.c += b.c-2;
            a.e += b.e;
            a.s += b.s;
            push(comps, mkcomp(a));
            k--;
        }
        else if ((a.c > 0 && b.e > 0) || (a.e > 0 && b.c > 0)){
            a.c += b.c;
            a.e += b.e-1;
            a.s += b.s;
            push(comps, mkcomp(a));
            k -= 2;
        }
        else if (a.e > 0 && b.e > 0){
            a.c += b.c+2;
            a.e += b.e-2;
            a.s += b.s;
            push(comps, mkcomp(a));
            k -= 3;
        }
        else if (a.e > 0 || b.e > 0){
            a.c += b.c;
            a.e += b.e-2;
            a.s += b.s;
            push(comps, mkcomp(a));
            k -= 4;
        }
        else
            break;
    }
    if(size(comps) == 1 && k >= 0)
        puts("yes");
    else
        puts("no");
    return 0;
}
