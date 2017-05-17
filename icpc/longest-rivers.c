#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
typedef long long ll;
#ifndef _MSC_VER
ll min(ll a, ll b) { return a<b ? a : b; }
ll max(ll a, ll b) { return a>b ? a : b; }
#else
  #define strdup _strdup
#endif

typedef struct pair {
  ll  first;
  int second;
}pair;
pair*newPair(ll a, int b) {
  pair*rez = malloc(sizeof(pair));
  rez->first = a;
  rez->second = b;
  return rez;
}
pair newPair2(ll a, int b) {
  pair rez;
  rez.first = a;
  rez.second = b;
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

int coompP(void*pa, void*pb)
{
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  ll diff;
  diff = a->first - b->first;  if (diff != 0) return(int) diff;
  return a->second - b->second;
}
int cmpP(const void*pa, const void*pb) {
  return coompP((void*)pa, (void*)pb);
}


#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
  int *output = resizeArray(array, int, *size + 1);
  output[(*size)++] = value;
  return output;
}
pair*pushbackP(pair*array, int *size, pair value) {
  pair*output = resizeArray(array, pair, *size + 1);
  output[(*size)++] = value;
  return output;
}


typedef struct vecS {
  int*ptr;
  int sz;
}vec;
vec newVec() {
  vec rez;// = malloc(sizeof(vec));
  rez.ptr = NULL;
  rez.sz = 0;
  return rez;
}

/////


char buff[100000];
int main() {
  int N, M;
  scanf("%d %d", &N, &M);
  do {
    char* rname[N];
    vec ce[M + 1]; memset(ce, 0, sizeof(ce));
    ll cmin[M + 1]; for (int i = 0; i<M + 1; i++)cmin[i] = (ll)1e18;
    ll rret[N];
    int rc[N];
    int rd[N];
    int cn[M + 1];
    int cc[M + 1];
    int cd[M + 1];
    PriorityQueue*event = newPriorityQueue(coompP);
    for (int i = 0; i < N; i++) {
      scanf("%s %d %d", &buff, &rc[i], &rd[i]);
      rname[i] = strdup(buff);
      int idx = rc[i];
      ce[idx].ptr = pushback(ce[idx].ptr, &ce[idx].sz, ~i);
      cn[idx]++;
      push(event, newPair(-rd[i], rc[i]));
    }
    for (int i = 1; i <= M; i++) {
      scanf("%d %d", &cc[i], &cd[i]);
      int idx = cc[i];
      ce[idx].ptr = pushback(ce[idx].ptr, &ce[idx].sz, i);
      cn[idx]++;
    }
    pair* q = NULL; int  qSz = 0;
    pair*rq = NULL; int rqSz = 0;
    q = pushbackP(q, &qSz, newPair2(0, 0));
    while (qSz>0) {
      int x = q[qSz - 1].second;
      ll d = q[qSz - 1].first;
      qSz--;
      for (int i = 0; i < ce[x].sz; i++) {
        if (ce[x].ptr[i] < 0)
          rq = pushbackP(rq, &rqSz, newPair2(d + rd[~ce[x].ptr[i]], ~ce[x].ptr[i]));
        else
          q = pushbackP(q, &qSz, newPair2(d + cd[ce[x].ptr[i]], ce[x].ptr[i]));
      }
    }
    qsort(rq, rqSz, sizeof(pair), cmpP);
    int smaller = 0;
    for (int i = 0; i < N; i++){
      pair*top_event = top(event);
      while(size(event) && -top_event->first <= rq[i].first){
        ll d = -top_event->first;
        int x = top_event->second;
        pop(event);
        cmin[x] = min(cmin[x], d);
        cn[x]--;
        if (cn[x] > 0 || x == 0)
          smaller++;
        else
          push(event, newPair(-cmin[x] - cd[x], cc[x]));
        top_event = top(event);
      }
      rret[rq[i].second] = N - smaller + 1;
    }
    for (int i = 0; i < N; i++)
      printf("%s %lld\n", rname[i], rret[i]);
  } while (0);
}


























