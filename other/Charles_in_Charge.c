#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
typedef struct{
  ll  first;
  int second;
}pair;
pair newpair(ll a, int b){
  return(pair){a,b};
}
#define pbp(zpv, zvv) zpv.ptr = pushbackP(zpv.ptr, &zpv.sz, zvv)
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

signed compP(void*pb, void*pa){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}
pair*mkpair(ll a, int b){
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
///////////////////////////////
int n, m;
ll  x, c[100001][2], t[100001], maxdist, dist[10001];
vecp nhbs[10001];
const ll INF1NITY = LLONG_MAX-1;

ll dijkstra(int s, int t, ll maxarrow){
    PriorityQueue*q=newPriorityQueue(compP);//of pair rev
    for(int i=0; i<n; i++)
        dist[i] = INF1NITY;
    dist[s] = 0;
    push(q, mkpair(dist[s],s));
    while(!empty(q)){
        pair*tq=top(q); pair cur = *tq; pop(q);
        if(dist[cur.second] < cur.first)
            continue;
        if(cur.second == t)
            return dist[t];
        for(int z=0; z<nhbs[cur.second].sz; z++){pair it = nhbs[cur.second].ptr[z];
            if((cur.first + it.first < dist[it.second]) && (it.first <= maxarrow)){
                dist[it.second] = cur.first + it.first;
                push(q, mkpair(dist[it.second], it.second));
            }
        }
    }
    return INF1NITY;
}
bool impossible(ll maxarrow){
    return(dijkstra(0, n-1, maxarrow) > maxdist);
}
int main(){
    scanf("%d %d %lld", &n, &m, &x);
    for(int i=0; i<m; i++){
        scanf("%lld%lld%lld", &c[i][0], &c[i][1], &t[i]);
        c[i][0]--, c[i][1]--;
        pbp(nhbs[c[i][0]], newpair(t[i], c[i][1]));
        pbp(nhbs[c[i][1]], newpair(t[i], c[i][0]));
    }
    maxdist = dijkstra(0, n-1, INF1NITY);
    maxdist = (maxdist*(100+x))/100;
    ll lo = -1;
    ll hi = maxdist + 1;
    while(hi - lo > 1){
        ll mid = (lo+hi)/2;
        if(impossible(mid))
            lo = mid;
        else
            hi = mid;
    }
    printf("%lld\n", hi);
    return 0;
}
