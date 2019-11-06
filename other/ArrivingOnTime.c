#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;

enum{ MAXN = 100005};
int n, m, s;
typedef struct{
    int dest;
    ll t0, p, d;
}tram;
tram newtram(int i, ll t, ll p, ll d){
    return(tram){i, t, p, d};
}
#define pb(zpv, zvv) zpv.ptr = pushbackT(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
tram*pushbackT(tram*array, int *size, tram value){
   tram*output = resizeArray(array, tram, *size + 1);
   output[(*size)++] = value;
   return output;
}
typedef struct{
   tram*ptr;
   int sz;
}vect;
vect newVecT() {
   vect rez;
   rez.ptr = NULL;
   rez.sz  = 0;
   return rez;
}
vect graph[MAXN];//of tram
ll dist[MAXN];

typedef struct{
  ll  first;
  int second;
}pli;
pli*mkpli(ll a, int b){
  pli*rv=calloc(1, sizeof(pli));
  rv->first  = a;
  rv->second = b;
  return rv;
}
int cmpP(void*pb, void*pa){//rev
  pli*a = (pli*)pa;
  pli*b = (pli*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
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
#endif///////////////////////////////////////////



ll dijkstra(ll init_dist){
    memset(dist, -1, sizeof(dist));
    dist[0] = init_dist;
    PriorityQueue*pq = newPriorityQueue(cmpP);//of pli rev
    push(pq, mkpli(init_dist, 0));
    while(!empty(pq)){
        pli*tq = top(pq);
        ll cur_dist = tq->first;
        int u       = tq->second; pop(pq);
        if(dist[u] != cur_dist)
            continue;
        for(int z=0;z<graph[u].sz;z++){tram t = graph[u].ptr[z];
            ll k = fmaxl(0LL, cur_dist - t.t0) / t.p;
            ll leave_time = t.t0 + k * t.p;
            while(leave_time < cur_dist)
                leave_time += t.p;
            ll dest_time = leave_time + t.d;
            if(dist[t.dest] == -1 || dest_time < dist[t.dest]){
                dist[t.dest] = dest_time;
                push(pq, mkpli(dest_time, t.dest));
            }
        }
    }
    return dist[n - 1];
}
int main(){
    scanf("%d %d %d", &n, &m, &s);
    int u, v, t0, p, d;
    for(int i=0; i<m; ++i){
        scanf("%d %d %d %d %d", &u, &v, &t0, &p, &d);
        pb(graph[u], newtram(v, t0, p, d));
    }
    ll min_time = dijkstra(0);
    if(min_time == -1 || min_time > s){
        puts("impossible");
        return 0;
    }
    ll lo = 0;
    ll hi = s + 1;
    while(lo + 1 < hi){
        ll mid = lo + (hi - lo) / 2;
        if(dijkstra(mid) <= s)
            lo = mid;
        else
            hi = mid;
    }
    printf("%lld\n", lo);
    return 0;
}
