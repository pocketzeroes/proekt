#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ MAXN = 5};
typedef unsigned long long ull;
ull MASK = ((1ULL<<7)-1);

typedef struct{
    int cost;
    ull result;
}Move;
Move*mkmv(Move m){
    Move*rv=calloc(1, sizeof(Move));
   *rv = m;
    return rv;
}
int cmpM(void*a, void*b){
    Move*tva=(Move*)a;
    Move*oth=(Move*)b;
    return(tva->cost > oth->cost)?-1:1;
}
#define pb(zpv, zvv) zpv.ptr = pushbackM(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
Move*pushbackM(Move*array, int *size, Move value){
  Move*output = resizeArray(array, Move, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	Move*ptr;
	int sz;
}vecm;
vecm newVecM(){
	vecm rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
#if 1////////////////muu

#include<stdint.h>
static const size_t INITIAL_CAPACITY = 16;
static const size_t MAXIMUM_CAPACITY = (1U << 31);
static const float  LOAD_FACTOR      = 0.75;
#ifndef HASHMAP_H
#define HASHMAP_H
typedef struct muu muu;
muu*newMap(void);
ull    mapHas(muu*karta, ull key);
void   mapDel(muu*karta, ull key);
size_t mapSize(const muu *karta);
ull    hashMapIsEmpty(const muu *karta);
void   mapClear(muu *karta);
void   hashMapDestroy(muu *karta);
#endif
void DUMMYfree(const void*pp){
    ;
}
typedef struct HashMapEntry{
  ull                  key;
  ull                  value;
  struct HashMapEntry *next;
  uint32_t             ha6;
} HashMapEntry;
struct muu {
  HashMapEntry **table;
  size_t         capacity;
  size_t         size;
  size_t         threshold;
};
static void setTable(muu *karta, HashMapEntry **table, size_t capacity) {
  karta->table     = table;
  karta->capacity  = capacity;
  karta->threshold = (size_t) (capacity * LOAD_FACTOR);
}
static uint32_t doHash(ull key){
  size_t   length;
  size_t   i;
  uint32_t h = 0;
  h = (31*h) + key;
  h = (31*h) + (key>>32);
  h ^= (h >> 20) ^ (h >> 12);
  return h ^ (h >> 7) ^ (h >> 4);
}
static size_t indexFor(uint32_t ha6, size_t length) {
  return ha6 & (length - 1);
}
static ull isHit(HashMapEntry *e, ull key, uint32_t ha6) {
  return (e->ha6 == ha6
          && (e->key == key));
}
static void copyOrFree( ull value, const void **valPtr) {
  if (valPtr != NULL)
    ;;//*valPtr = value;
}
static ull updateValue(muu *karta, HashMapEntry *e, ull newVal, const void **oldValPtr) {
  copyOrFree( e->value, oldValPtr);
  e->value = newVal;
  return 1;
}
muu *newMap(void ) {
  HashMapEntry **table;
  muu       *karta = malloc(sizeof(*karta));
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
ull mapPut(muu *karta, ull key, ull value){
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
ull mapGet(muu *karta, ull key) {
  HashMapEntry *e;
  uint32_t      ha6  = doHash(key);
  size_t        gIndex = indexFor(ha6, karta->capacity);
  for (e = karta->table[gIndex]; e != NULL; e = e->next) {
    if (isHit(e, key, ha6))
      return e->value;
  }
  return NULL;
}
ull mapHas(muu *karta, ull key) {
  HashMapEntry *e;
  uint32_t      ha6  = doHash(key);
  size_t        gIndex = indexFor(ha6, karta->capacity);
  for (e = karta->table[gIndex]; e != NULL; e = e->next) {
    if (isHit(e, key, ha6))
      return 1;
  }
  return 0;
}
void mapDel(muu *karta, ull key){
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
size_t mapSize(const muu *karta) {
  return karta->size;
}
ull hashMapIsEmpty(const muu *karta) {
  return (karta->size == 0);
}
void mapClear(muu *karta) {
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
void hashMapDestroy(muu *karta){
  if (karta == NULL)
    return;
  mapClear(karta);
  free(karta->table);
  free(karta);
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
#endif///////////////////////////////////////////



muu*gmp;//map ull ull
int cap[MAXN];
int N,V;

int volume(ull state, int j){
    return(state >> (7*j)) & MASK;
}
ull setVolume(ull state, int j, int v){
    ull temp = MASK << (7*j);
    return(state ^ (state & temp) ^ ((ull)(v) << (7*j)));
}
bool isGoal(ull state){
    return(volume(state, 0) == V);
}
vecm neighbors(ull state){
    vecm results = newVecM();//of Move
    for(int j=0; j<N; j++)
        for(int k=0; k<N; k++){
            if(j != k){
                int vj = volume(state,j);
                int vk = volume(state,k);
                int quantity = fmin(vj, cap[k] - vk);
                if(quantity > 0){
                    Move temp;
                    temp.cost = quantity;
                    temp.result = setVolume(setVolume(state, j, vj-quantity), k, vk+quantity);
                    pb(results, temp);
                }
            }
        }
    return results;
}
int solve(){
    PriorityQueue*fringe = newPriorityQueue(cmpM);//of Move
    Move init = (Move){0, cap[0]};
    push(fringe, mkmv(init));
    while(!empty(fringe)){
        Move*tq=top(fringe); Move next = *tq; pop(fringe);
        if(isGoal(next.result))
            return next.cost;
        if(!mapHas(gmp, next.result)){
            mapPut(gmp, next.result, next.cost);
            vecm nbrs = neighbors(next.result);
            for(int j=0; j<nbrs.sz; j++){
                if(!mapHas(gmp, nbrs.ptr[j].result)){
                    nbrs.ptr[j].cost += next.cost;
                    push(fringe, mkmv(nbrs.ptr[j]));
                }
            }
        }
    }
    return -1;
}
int main(){
    gmp = newMap();
    scanf("%d", &N);
    for(int j=0; j<N; j++)
        scanf("%d", &cap[j]);
    scanf("%d", &V);
    int best = solve();
    if(best == -1)
        puts("impossible");
    else
        printf("%d\n", best);
    return 0;
}
