#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
#define int ll
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

#define pbp(zpv, zvv) zpv.ptr = pushbackP(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
typedef struct{
  int first;
  int second;
}pair;
pair newpair(int a, int b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}
signed compP(void*pa, void*pb){
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
#define F first
#define S second
int n, m;
vecp rt[101010];
bool u [101010];
ll   d1[101010];
int  e [101010];


void gg(int c){
    ll md=1222333444555666777ll;
    int mi=0;
    for(int i=0; i<rt[c].sz; ++i){
        int w=rt[c].ptr[i].F;
        if(d1[w]+rt[c].ptr[i].S<md){
            md=d1[w]+rt[c].ptr[i].S;
            mi=i;
        }
    }
    for(int i=0; i<rt[c].sz; ++i){
        if(i==mi)
            continue;
        int w=rt[c].ptr[i].F;
        if(u[w])
            continue;
        u[w]=1;
        e[w]=c;
        gg(w);
    }
}
signed main(){
    scanf("%lld %lld", &n, &m);
    for(int i=0; i<m; ++i){
        int a, b, d;
        scanf("%lld%lld%lld", &a, &b, &d);
        pbp(rt[a], newpair(b, d));
        pbp(rt[b], newpair(a, d));
    }
    PriorityQueue*p=newPriorityQueue(compP);//pli
    push(p, mkpair(0, 1));
    while(size(p)){
        pair*tq = top(p);
        ll  d = -tq->F;
        int c =  tq->S; pop(p);
        if(u[c])
            continue;
        u [c]=1;
        d1[c]=d;
        for(int i=0; i<rt[c].sz; ++i){
            int w=rt[c].ptr[i].F;
            ll dd=d+rt[c].ptr[i].S;
            if(u[w])
                continue;
            push(p, mkpair(-dd, w));
        }
    }
    for(int i=0; i<n; ++i)
        u[i]=0;
    for(int i=0; i<n; ++i)
        e[i]=-1;
    u[0]=1;
    gg(0);
    if(e[1]==-1)
        puts("impossible");
    else{
        vec ans=newVec();
        int c=1;
        while(c){
            pb(ans, c);
            c=e[c];
        }
        pb(ans, 0);
        printf("%lld ", ans.sz);
        for(int i=ans.sz-1; i>=0; --i)
            printf("%lld ", ans.ptr[i]);
        puts("");
    }
    return 0;
}
