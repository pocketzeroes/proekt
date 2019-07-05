#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;

void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
void filll(ll*arr, int sz, ll val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value){
  int *output = resizeArray(array, int, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	int*ptr;
	int sz;
}vec;
vec newVec(){
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

typedef struct{
  ll  first;
  int second;
}pair;
pair newPair(ll a, int b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}
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
int compP(void*pb, void*pa){//rev
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}
#if 1
pair*mkPair(ll a, int b){
  pair*rez = malloc(sizeof(pair));
  rez->first  = a;
  rez->second = b;
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
////////////////////////////////////
const ll INF = 1ll<<61;
int*parent;
int*uni;
vec*h;


void clear(int u, int last){
  while(true) {
    assert(u>=0);
    u=parent[u];
    if (u==last)
      break;
    uni[u]=false;
  }
}
void articulation(int u, int last){
  static bool first=true;
  for(int z=0;z<h[u].sz;z++){int it=h[u].ptr[z];
    if(parent[it]==u)
      continue;
    if(parent[it] != -1){
      clear(it, last);
      uni[u] = false;
    }
    else{
      parent[it] = u;
      uni[it] = first;
      articulation(it, uni[u] ? u : last);
    }
    first = false;
  }
}
int gn;
void dijkstra(vecp*g, int s){
  int n = gn;
  ll distance[n]; filll(distance, n, INF);
  h = calloc(n, sizeof(vec));
  PriorityQueue*q=newPriorityQueue(compP);//rev
  distance[s]=0;
  push(q, mkPair(0,s));
  while(!empty(q)){
    pair*tq=top(q);
    ll  d = tq->first;
    int u = tq->second; pop(q);
    for(int z=0;z<g[u].sz;z++){pair it = g[u].ptr[z];
      ll d2 = d+it.first;
      int v = it.second;
      if(distance[v]==d2)
        h[v].ptr = pushback(h[v].ptr, &h[v].sz, u);
      else if(distance[v]>d2){
        h[v].sz=0;
        h[v].ptr = pushback(h[v].ptr, &h[v].sz, u);
        distance[v] = d2;
        push(q, mkPair(d2,v));
      }
    }
  }
}
int main(){
  int n,m;
  scanf("%d %d", &n, &m);
  gn=n;
  vecp g[n]; memset(g, 0, sizeof(g));
  for(int i=0; i<m; ++i){
    int u, v, w;
    scanf("%d %d %d", &u, &v, &w);
    g[u].ptr = pushbackP(g[u].ptr, &g[u].sz, newPair(w,v));
  }
  int s, t;
  scanf("%d %d", &s, &t);
  dijkstra(g, s);
  parent = calloc(n, sizeof(int)); fill(parent, n, -1);
  uni    = calloc(n, sizeof(int));
  uni[t] = true;
  articulation(t, -1);
  bool first = true;
  for(int i=0; i<n; ++i){
    if(uni[i]){
      if(!first)
        printf(" ");
      first = false;
      printf("%d", i);
    }
  }
  puts("");
  return 0;
}
