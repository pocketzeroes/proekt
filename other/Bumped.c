#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
ll min(ll a, ll b){return a<b?a:b;}
ll max(ll a, ll b){return a>b?a:b;}

void fill(ll*arr, int sz, ll val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}

int gsz;
typedef struct{
  int to;
  ll  w;
}edge;
edge newedge(int a, ll b){
  edge rez;
  rez.to = a;
  rez.w  = b;
  return rez;
}
int cmpE(const void*pa, const void*pb){
  edge*t=(edge*)pa;
  edge*o=(edge*)pb;
  return(t->w > o->w)?-1:1;
}
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


int compE(void*pa, void*pb){
  edge*t=(edge*)pa;
  edge*o=(edge*)pb;
  return(t->w > o->w)?-1:1;
}
#if 1
edge*mkEdge(int a, ll b){
  edge*rez = malloc(sizeof(edge));
  rez->to = a;
  rez->w  = b;
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
#endif
///////////////////////
const ll inf = 1000000LL * 10000000LL;

ll*dijkstra(vece*g, int start){
  int n = gsz;
  ll*d = calloc(n, sizeof(ll)); fill(d, n, inf);
  d[start] = 0;
  PriorityQueue*q = newPriorityQueue(compE);//of edge
  push(q, mkEdge(start, 0));
  while(!empty(q)){
    edge*tq=top(q);
    int node = tq->to;
    ll  dist = tq->w ; pop(q);
    if(dist > d[node])
      continue;
    for(int i=0; i<g[node].sz; i++){
      int to = g[node].ptr[i].to;
      ll w_extra = g[node].ptr[i].w;
      if(dist + w_extra < d[to]){
        d[to] = dist + w_extra;
        push(q, mkEdge(to, d[to]));
      }
    }
  }
  return d;
}
void solve(){
  int n, m, f, s, t;
  scanf("%d%d%d%d%d", &n, &m, &f, &s, &t);
  vece g[n]; memset(g, 0, sizeof(g));
  gsz = n;
  for(int i=0; i<m; i++){
    int u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    g[u].ptr = pushbackE(g[u].ptr, &g[u].sz, newedge(v, w));
    g[v].ptr = pushbackE(g[v].ptr, &g[v].sz, newedge(u, w));
  }
  ll*dist_s = dijkstra(g, s);
  ll*dist_t = dijkstra(g, t);
  ll best = dist_s[t];
  for(int i=0; i<f; i++){
    int u, v;
    scanf("%d%d", &u, &v);
    best = min(best, dist_s[u] + dist_t[v]);
  }
  printf("%lld\n", best);
}
int main(){
  solve();
  return 0;
}
