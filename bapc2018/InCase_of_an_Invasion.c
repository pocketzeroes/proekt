#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;

void fill(ll*arr, int sz, ll val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
typedef struct{
  int v;
  ll  weight;
}Edge;
Edge newEdge(int a, ll b){
  Edge rez;
  rez.v      = a;
  rez.weight = b;
  return rez;
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
Edge*pushbackE(Edge*array, int *size, Edge value){
  Edge*output = resizeArray(array, Edge, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	Edge*ptr;
	int sz;
}vece;
vece newVecE(){
	vece rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

typedef struct{
  ll  d;
  int v;
}pair;
#if 1
pair*mkPair(ll a, int b){
  pair*rez = malloc(sizeof(pair));
  rez->d = a;
  rez->v = b;
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
  return(a->d < b->d)?1:-1;
}
#endif




int edges_sz;

ll*dijkstra(vece*edges, int s){
  ll*dist=calloc(edges_sz, sizeof(ll));
  fill(dist, edges_sz, (ll)1e18);
  PriorityQueue*pq = newPriorityQueue(coompP);
  dist[s] = 0;
  push(pq, mkPair(0, s));
  while(!empty(pq)){
    pair*topq = top(pq);
    ll  d = topq->d;
    int u = topq->v;
    pop(pq);
    if(d == dist[u]){
      for(int z=0; z<edges[u].sz; z++){Edge e = edges[u].ptr[z];
        if(dist[e.v] > d + e.weight){
          dist[e.v] = d + e.weight;
          push(pq, mkPair(d+e.weight, e.v));
        }
      }
    }
  }
  return dist;
}
int main(int taskI, char**bapc){
  int n, m, s;
  scanf("%d %d %d", &n, &m, &s);
  edges_sz = n;
  vece g[n]; memset(g, 0, sizeof(g));
  ll  cs[n];
  for(int i=0; i<n; i++){
    scanf("%lld", &cs[i]);
  }
  while(m--){
    int u, v, w;
    scanf("%d %d %d", &u, &v, &w);
    --u, --v;
    g[u].ptr = pushbackE(g[u].ptr, &g[u].sz, newEdge(v, w));
    g[v].ptr = pushbackE(g[v].ptr, &g[v].sz, newEdge(u, w));
  }
  Edge as[s];
  for(int i=0;i<s;i++){
    scanf("%d %lld", &as[i].v, &as[i].weight);
    --as[i].v;
  }
  ll*dists[s];
  for(int i=0; i<s; ++i)
    dists[i] = dijkstra(g, as[i].v);
  ll l = 0, h =(ll) 1e18;
  while(l < h){
    ll m = (l+h)/2;
    ll cover[1<<s]; memset(cover, 0, sizeof(cover));
    for(int j=0; j<n; ++j){
      int mask = 0;
      for(int i=0; i<s; ++i)
        if(dists[i][j] <= m)
          mask |= 1<<i;
      cover[mask] += cs[j];
    }
    for(int m=0; m<1<<s; ++m){
      ll total_cover = 0;
      for(int m2=0; m2<1<<s; ++m2)
        if((m|m2) == m)
          total_cover += cover[m2];
      ll cap = 0;
      for(int i=0; i<s; ++i)
        if(m & (1<<i))
          cap += as[i].weight;
      if(cap < total_cover)
        goto bad;
    }
    h = m;
    continue;
  bad:
    l = m + 1;
  }
  printf("%lld\n", l);
  return 0;
}

