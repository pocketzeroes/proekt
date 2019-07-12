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


const ll INF = LLONG_MAX / 10;
typedef struct{
  ll first;
  ll second;
}pair;
pair newPair(ll a, ll b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}
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
int compP(void*pb, void*pa){//rev
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}
#if 1
pair*mkPair(ll a, ll b){
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

int graph_sz;
ll Dijkstra(vecp*graph, int s, int t){
  int n = graph_sz;
  ll dists[n]; fill(dists, n, INF);
  dists[s] = 0;
  PriorityQueue*q = newPriorityQueue(compP);// of pair rev
  push(q, mkPair(0, s));
  bool closed[n]; memset(closed, 0, sizeof(closed));
  while(!empty(q)){
    pair*tq=top(q);
    ll  dist = tq->first;
    int node = tq->second;
    pop(q);
    if(closed[node])
      continue;
    closed[node] = true;
    dists[node] = dist;
    for(int z=0; z<graph[node].sz; z++){pair edge = graph[node].ptr[z];
      if(closed[edge.first] || dist + edge.second >= dists[edge.first])
        continue;
      dists[edge.first] = dist + edge.second;
      push(q, mkPair(dist + edge.second, edge.first));
    }
  }
  return dists[t];
}
void AddEdge(vecp*graph, int u, int v, ll w){
  graph[u].ptr = pushbackP(graph[u].ptr, &graph[u].sz, newPair(v, w));
}
int main(){
  int n, m, k1, k2;
  scanf("%d%d%d%d", &n, &m, &k1, &k2);
  int nmap[n][k1+1][k2+2];
  int next_id = 0;
  for(int i = 0; i < n; ++i)
    for(int j = 0; j <= k1; ++j)
      for(int k = 0; k <= k2; ++k)
        nmap[i][j][k] = next_id++;
  graph_sz=n*(k1+1)*(k2+1);
  vecp*graph = calloc(graph_sz, sizeof(vecp));
  for(int i = 0; i < m; ++i){
    int u, v, c;
    ll x;
    scanf("%d %d %lld %d", &u, &v, &x, &c);
    --u, --v;
    for(int j=0; j<=k1; ++j){
      for(int k=0; k<=k2; ++k){
        if(c == 0){
          AddEdge(graph, nmap[u][j][k], nmap[v][j][k], x);
          AddEdge(graph, nmap[v][j][k], nmap[u][j][k], x);
        }
        else if(c == 1 && j < k1){
          AddEdge(graph, nmap[u][j][k], nmap[v][j + 1][k], x);
          AddEdge(graph, nmap[v][j][k], nmap[u][j + 1][k], x);
        }
        else if(c == 2 && k < k2){
          AddEdge(graph, nmap[u][j][k], nmap[v][j][k + 1], x);
          AddEdge(graph, nmap[v][j][k], nmap[u][j][k + 1], x);
        }
      }
    }
  }
  int s, t;
  scanf("%d%d", &s, &t);
  --s, --t;
  ll ans = Dijkstra(graph, nmap[s][0][0], nmap[t][k1][k2]);
  if(ans == INF)
    ans = -1;
  printf("%lld\n", ans);
  return 0;
}
