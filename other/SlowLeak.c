#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define inf ((ll)1e15)
typedef long long ll;

typedef struct{
  ll first;
  ll second;
}pair;
pair newpair(ll a, ll b){
  return(pair){a,b};
}
#define pbp(zpv, zvv) zpv.ptr = pushbackP(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
pair*pushbackP(pair*array, ll *size, pair value){
  pair*output = resizeArray(array, pair, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	pair*ptr;
	ll sz;
}vecp;
vecp newVecP(){
	vecp rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

signed compP(void*pb, void*pa){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}
pair*mkpair(ll a, ll b){
  pair*rez = malloc(sizeof(pair));
  rez->first  = a;
  rez->second = b;
  return rez;
}
#if 1 // pq
#ifndef __HEAP_H_GUARD__
#define __HEAP_H_GUARD__
#define HEAP_STARTING_SIZE 256
struct heap_st;
typedef struct heap_st PriorityQueue;
PriorityQueue* newPriorityQueue(signed(*)(void*, void*));
ll   push(PriorityQueue*, void*);
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
ll  push(PriorityQueue* h, void* data) {
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
ll size(PriorityQueue*h) {
  return h->used;
}
bool empty(PriorityQueue*h){
  return h->used==0;
}
#endif
///////////////////////////////////////////////////
enum{ maxn = 505};

ll   n, m, k;
ll   wow;
ll   good[maxn];
ll   dis [maxn][maxn];
vecp way [maxn];
ll   ans [maxn];

int main(){
    PriorityQueue*q = newPriorityQueue(compP);
    scanf("%lld %lld %lld %lld", &n, &m, &k, &wow);
    good[1] = good[n] = 1;
    for(ll i=1;i<=k;i++){
        ll x;
        scanf("%d",&x);
        good[x] = 1;
    }
    for(ll u=1;u<=n;u++)
        for(ll v=1;v<=n;v++)
            dis[u][v] = inf;
    for(ll i=1;i<=m;i++){
        ll u, v, val;
        scanf("%lld %lld %lld", &u, &v, &val);
        dis[u][v] = fminl(dis[u][v], val);
        dis[v][u] = fminl(dis[v][u], val);
    }
    for(ll k=1;k<=n;k++)
        for(ll u=1;u<=n;u++)
            for(ll v=1;v<=n;v++)
                dis[u][v] = fminl(dis[u][v], dis[u][k] + dis[k][v]);
    for(ll u=1;u<=n;u++){
        if(!good[u]) 
            continue;
        for(ll v=1;v<=n;v++){
            if(!good[v]) 
                continue;
            if(dis[u][v]<=wow)
                pbp(way[u], newpair(v,dis[u][v]));
        }
    }
    for(ll u=1;u<=n;u++)
        ans[u] = inf;
    ans[1] = 0;
    push(q, mkpair(0,1));
    while(!empty(q)){
        pair*tq=top(q); pair tmp = *tq; pop(q);
        ll u   =  tmp.second;
        ll val = -tmp.first;
        if(ans[u] != val)
            continue;
        for(int z=0;z<way[u].sz;z++){pair nxt = way[u].ptr[z];
            ll v   = nxt.first;
            ll len = nxt.second;
            if(ans[v] > ans[u] + len){
                ans[v] = ans[u] + len;
                push(q, mkpair(-ans[v], v));
            }
        }
    }
    if(ans[n] == inf)
        printf("stuck");
    else
        printf("%lld", ans[n]);
    return 0;
}
