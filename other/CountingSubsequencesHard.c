#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
#if 1////////////////mli
#include<stdint.h>
static const size_t INITIAL_CAPACITY = 16;
static const size_t MAXIMUM_CAPACITY = (1U << 31);
static const float  LOAD_FACTOR      = 0.75;
#ifndef HASHMAP_H
#define HASHMAP_H
typedef struct mli mli;
mli*newMap(void);
int    mapHas(mli*karta, ll key);
void   mapDel(mli*karta, ll key);
size_t mapSize(const mli *karta);
int    hashMapIsEmpty(const mli *karta);
void   mapClear(mli *karta);
void   hashMapDestroy(mli *karta);
#endif
void DUMMYfree(const void*pp){
    ;
}
typedef struct HashMapEntry{
  ll                   key;
  int                  value;
  struct HashMapEntry *next;
  uint32_t             ha6;
} HashMapEntry;
struct mli {
  HashMapEntry **table;
  size_t         capacity;
  size_t         size;
  size_t         threshold;
};
static void setTable(mli *karta, HashMapEntry **table, size_t capacity) {
  karta->table     = table;
  karta->capacity  = capacity;
  karta->threshold = (size_t) (capacity * LOAD_FACTOR);
}
static uint32_t doHash(ll key){
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
static int isHit(HashMapEntry *e, ll key, uint32_t ha6) {
  return (e->ha6 == ha6
          && (e->key == key));
}
static void copyOrFree( int value, const void **valPtr) {
  if (valPtr != NULL)
    ;;//*valPtr = value;
}
static int updateValue(mli *karta, HashMapEntry *e, int newVal, const void **oldValPtr) {
  copyOrFree( e->value, oldValPtr);
  e->value = newVal;
  return 1;
}
mli *newMap(void ) {
  HashMapEntry **table;
  mli       *karta = malloc(sizeof(*karta));
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
int mapPut(mli *karta, ll key, int value){
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
int mapGet(mli *karta, ll key) {
  HashMapEntry *e;
  uint32_t      ha6  = doHash(key);
  size_t        gIndex = indexFor(ha6, karta->capacity);
  for (e = karta->table[gIndex]; e != NULL; e = e->next) {
    if (isHit(e, key, ha6))
      return e->value;
  }
  return NULL;
}
int mapHas(mli *karta, ll key) {
  HashMapEntry *e;
  uint32_t      ha6  = doHash(key);
  size_t        gIndex = indexFor(ha6, karta->capacity);
  for (e = karta->table[gIndex]; e != NULL; e = e->next) {
    if (isHit(e, key, ha6))
      return 1;
  }
  return 0;
}
void mapDel(mli *karta, ll key){
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
size_t mapSize(const mli *karta) {
  return karta->size;
}
int hashMapIsEmpty(const mli *karta) {
  return (karta->size == 0);
}
void mapClear(mli *karta) {
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
void hashMapDestroy(mli *karta){
  if (karta == NULL)
    return;
  mapClear(karta);
  free(karta->table);
  free(karta);
}
ll Encode(int x, int y){
  return ((ll)x) * 1000000000 + y;
}
void inc(mli*map, int off){
  mapPut(map, off, mapGet(map, off)+1);
}
void dec(mli*map, int off){
  mapPut(map, off, mapGet(map, off)-1);
}
#endif


int T, N, x;
mli*bolo;

int main(){
  bolo = newMap();
  scanf("%d", &T);
  while(T--){
    scanf("%d", &N);
    mapClear(bolo);
    ll res = 0, sum = 0;
    mapPut(bolo, 0, 1);
    while(N--){
      scanf("%d", &x);
      sum += x;
      res += mapGet(bolo, sum-47);
      inc(bolo, sum);
    }
    printf("%lld\n", res);
  }
  return 0;
}
