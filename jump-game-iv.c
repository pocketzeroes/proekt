#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#if 1////////////////mii

#include<stdint.h>
static const size_t INITIAL_CAPACITY = 16;
static const size_t MAXIMUM_CAPACITY = (1U << 31);
static const float  LOAD_FACTOR      = 0.75;
#ifndef HASHMAPII_H
#define HASHMAPII_H
typedef struct mii mii;
mii*newMap(void);
int    mapHas(mii*karta, int key);
void   mapDel(mii*karta, int key);
size_t mapSize(const mii *karta);
int    hashMapIsEmpty(const mii *karta);
void   mapClear(mii *karta);
void   hashMapDestroy(mii *karta);
#endif
void DUMMYfree(const void*pp){
    ;
}
typedef struct HashMapEntry{
  int                   key;
  int                  value;
  struct HashMapEntry *next;
  uint32_t             ha6;
} HashMapEntry;
struct mii{
  HashMapEntry **table;
  size_t         capacity;
  size_t         size;
  size_t         threshold;
};
static void setTable(mii *karta, HashMapEntry **table, size_t capacity){
  karta->table     = table;
  karta->capacity  = capacity;
  karta->threshold = (size_t) (capacity * LOAD_FACTOR);
}
static uint32_t doHash(int key){
  return key;
}
static size_t indexFor(uint32_t ha6, size_t length){
  return ha6 & (length - 1);
}
static int isHit(HashMapEntry *e, int key, uint32_t ha6){
  return (e->ha6 == ha6
          && (e->key == key));
}
static void copyOrFree( int value, const void **valPtr){
  if (valPtr != NULL)
    ;;//*valPtr = value;
}
static int updateValue(mii *karta, HashMapEntry *e, int newVal, const void **oldValPtr){
  copyOrFree( e->value, oldValPtr);
  e->value = newVal;
  return 1;
}
mii*newMap(void){
  HashMapEntry **table;
  mii       *karta = malloc(sizeof(*karta));
  if (karta == NULL)
    return NULL;
  table = calloc(INITIAL_CAPACITY, sizeof(*karta->table));
  if (table == NULL) {
    free(karta);
    return NULL;
  }
  setTable(karta, table, INITIAL_CAPACITY);
  karta->size = 0;
  return karta;
}
int mapPut(mii *karta, int key, int value){
  const void**oldValPtr=NULL;
  HashMapEntry  *e;
  size_t         newCapacity;
  HashMapEntry **newTable;
  size_t         i;
  uint32_t ha6  = doHash(key);
  size_t   gIndex = indexFor(ha6, karta->capacity);
  for (e = karta->table[gIndex]; e != NULL; e = e->next) {
    if (isHit(e, key, ha6) == 0)
      continue;
    return updateValue(karta, e, value, oldValPtr);
  }
  e = calloc(1, sizeof(HashMapEntry));
  if (e == NULL)
    return 0;
  e->key = (key);
  if (updateValue(karta, e, value, oldValPtr) == 0) {
    free(e);
    return 0;
  }
  e->ha6 = ha6;
  e->next = karta->table[gIndex];
  karta->table[gIndex] = e;
  if (karta->size++ < karta->threshold)
    return 1;
  newCapacity = 2 * karta->capacity;
  if (karta->capacity == MAXIMUM_CAPACITY) {
    karta->threshold = UINT_MAX;
    return 1;
  }
  newTable = calloc(newCapacity, sizeof(*newTable));
  if (newTable == NULL)
    return 0;
  for (i = 0; i < karta->capacity; ++i) {
    HashMapEntry *next;
    for (e = karta->table[i]; e != NULL; e = next) {
      gIndex   = indexFor(e->ha6, newCapacity);
      next    = e->next;
      e->next = newTable[gIndex];
      newTable[gIndex] = e;
    }
  }
  free(karta->table);
  setTable(karta, newTable, newCapacity);
  return 1;
}
int mapGet(mii *karta, int key){
  HashMapEntry *e;
  uint32_t      ha6  = doHash(key);
  size_t        gIndex = indexFor(ha6, karta->capacity);
  for (e = karta->table[gIndex]; e != NULL; e = e->next) {
    if (isHit(e, key, ha6))
      return e->value;
  }
  return 0;//zero
}
int mapHas(mii *karta, int key){
  HashMapEntry *e;
  uint32_t      ha6  = doHash(key);
  size_t        gIndex = indexFor(ha6, karta->capacity);
  for (e = karta->table[gIndex]; e != NULL; e = e->next) {
    if (isHit(e, key, ha6))
      return 1;
  }
  return 0;
}
void mapDel(mii *karta, int key){
  uint32_t      ha6  = doHash(key);
  size_t        gIndex = indexFor(ha6, karta->capacity);
  HashMapEntry *prev  = karta->table[gIndex];
  HashMapEntry *e     = prev;
  while (e != NULL) {
    HashMapEntry *next = e->next;
    if (isHit(e, key, ha6)) {
      karta->size--;
      if (prev == e)
        karta->table[gIndex] = next;
      else
        prev->next = next;
      break;
    }
    prev = e;
    e    = next;
  }
  if (e == NULL)
    return;
  free(e);
}
size_t mapSize(const mii*karta){
  return karta->size;
}
int hashMapIsEmpty(const mii*karta){
  return (karta->size == 0);
}
void mapClear(mii*karta){
  size_t i;
  for (i = 0; i < karta->capacity; ++i) {
    HashMapEntry *e;
    HashMapEntry *next;
    for (e = karta->table[i]; e != NULL; e = next) {
      next = e->next;
      free(e);
    }
    karta->table[i] = NULL;
  }
}
#define mapForEach(mm, fnc)                            \
  do{                                                  \
    for(int i = 0; i < mm->capacity; ++i) {            \
      HashMapEntry *e;                                 \
      HashMapEntry *next;                              \
      for (e = mm->table[i]; e != NULL; e = next) {    \
          kvp rez;                                     \
          rez.key=e->key;                              \
          rez.val=e->value;                            \
          fnc(&rez);                                   \
          next = e->next;                              \
      }                                                \
    }                                                  \
  }while(0);
  
typedef struct{
  int key;
  int  val;
}kvp;

void delMap(mii*karta){
  if (karta == NULL)
    return;
  mapClear(karta);
  free(karta->table);
  free(karta);
}
void inc(mii*map, int off){
  mapPut(map, off, mapGet(map, off)+1);
}
#endif
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
#endif/////////

/////////////////////////////
enum{MAX = 200005};
int n, cnt, tot;
int head[MAX], 
    vet [MAX], 
    Next[MAX], 
    cost[MAX],
    dis [MAX];
mii*mp;

void add(int x, int y, int w){
    cnt++;
    Next[cnt] = head[x];
    head[x  ] = cnt;
    vet [cnt] = y;
    cost[cnt] = w;
}
typedef struct{
    int x, dis;
}node;
node*mknode(int a, int b){
    node*rv=calloc(1, sizeof(node));
    rv->x  =a;
    rv->dis=b;
    return rv;
}
int cmpN(void*pa, void*pb){
    node*a=(node*)pa;
    node*b=(node*)pb;
    return(a->dis > b->dis)?-1:1;
}
void dij(){
    PriorityQueue*q = newPriorityQueue(cmpN);//of node
    memset(dis, 0x3f, sizeof(dis));
    dis[1] = 0;
    push(q, mknode(1, 0));
    while(!empty(q)){
        node*tq=top(q); node t = *tq; pop(q);
        if(t.dis > dis[t.x])
            continue;
        for(int i = head[t.x]; i; i = Next[i]){
            int v = vet[i];
            if(dis[v] > t.dis+cost[i]){
               dis[v] = t.dis+cost[i];
               push(q, mknode(v, dis[v]));
            }
        }
    }
}
int minJumps(int*a, int aSz){
    mp = newMap();
    cnt = 0;
    memset(head, 0, sizeof(head));
    n = aSz;
    tot = n;
    for(int i=1; i<=n; i++){
        if(i > 1) 
            add(i, i-1, 2);
        if(i < n) 
            add(i, i+1, 2);
    }
    for(int i=0; i<aSz; i++){
        if(!mapHas(mp, a[i]))
            mapPut(mp, a[i], ++tot);
        add(i+1, mapGet(mp, a[i]), 1);
        add(mapGet(mp, a[i]), i+1, 1);
    }
    dij();
    return dis[n]/2;
}

//int main(){
//    return 0;
//}
