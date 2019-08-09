#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#include<complex.h>

#define newpt __builtin_complex

typedef struct tri{
    int i, j, k, a2;
}tri;

int cmpT(void*a, void*b){
    tri*l=(tri*)a;
    tri*r=(tri*)b;
    tri lhs = *l;
    tri rhs = *r;
    return(lhs.a2 > rhs.a2 || (lhs.a2 == rhs.a2 && lhs.j > rhs.j))?-1:1;
}

#if 1
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
#endif
enum{ MAXN = 200000};

typedef complex double pt;

pt p[MAXN+1];

tri*newtri(int i, int j, int k){
    tri*rez=calloc(1, sizeof(tri));
    rez->i  = i;
    rez->j  = j;
    rez->k  = k;
    rez->a2 = fabs(cimag((p[k]-p[j])*conj(p[i]-p[j])));
    return rez;
}

int find(int i, int*uf){
    return uf[i] == i ? i : (uf[i] = find(uf[i], uf));
}
int main(){
    int n, m;
    int ufl[MAXN+1],
        ufr[MAXN+1];
    PriorityQueue*pq = newPriorityQueue(cmpT);//of tri
    scanf("%d %d", &n, &m);
    for(int i=0; i<=n; ++i){
        ufl[i] = ufr[i] = i;
        int x, y;
        scanf("%d %d", &x, &y);
        p[i] = newpt((double)x, (double)y);
        if(i >= 2)
            push(pq, newtri(i-2, i-1, i));
    }
    for(int i = n; i > m; --i){
        tri t;
        while(1){
            tri*tq = top(pq); t = *tq; pop(pq);
            if(ufl[t.i] == t.i && ufr[t.k] == t.k)
                break;
        }
        printf("%d\n", t.j);
        ufl[t.j] = t.i;
        if(t.i > 0)
            push(pq, newtri(find(t.i-1, ufl), t.i, t.k));
        ufr[t.j] = t.k;
        if(t.k < n)
            push(pq, newtri(t.i, t.k, find(t.k+1, ufr)));
    }
    return 0;
}
