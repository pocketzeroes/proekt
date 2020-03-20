#pragma GCC optimize "-O3" // maximizingwinnings
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

void freemat(int**m, int x){
  for(int i=0; i<x; i++)
    free(m[i]);
  free(m);
  m = NULL;
}

#if 1////////////////mpp

typedef struct{
  int first, second;
}pair;
pair newpair(int a, int b){
  return(pair){a,b};
}
int cmpP(pair a, pair b){
  if(a.first  != b.first) return(a.first  < b.first )?-1:1;
  if(a.second != b.second)return(a.second < b.second)?-1:1;
  return 0;
}
#include<stdint.h>
static const size_t INITIAL_CAPACITY = 16;
static const size_t MAXIMUM_CAPACITY = (1U << 31);
static const float  LOAD_FACTOR      = 0.75;
#ifndef HASHMAP_H
#define HASHMAP_H
typedef struct mpp mpp;
mpp*newMap(void);
bool   mapHas(mpp*karta, pair key);
void   mapDel(mpp*karta, pair key);
size_t mapSize(const mpp *karta);
bool   mapEmpty(const mpp *karta);
void   mapClear(mpp *karta);
void   mapDestroy(mpp *karta);
#endif
void DUMMYfree(const void*pp){
  ;
}
typedef struct HashMapEntry{
  pair                 key;
  pair                 value;
  struct HashMapEntry *next;
  uint32_t             ha6;
} HashMapEntry;

struct mpp{
  HashMapEntry **table;
  size_t         capacity;
  size_t         size;
  size_t         threshold;
};
static void setTable(mpp*karta, HashMapEntry**table, size_t capacity){
  karta->table     = table;
  karta->capacity  = capacity;
  karta->threshold = (size_t) (capacity * LOAD_FACTOR);
}
static uint32_t doHash(pair key){
  size_t   length;
  size_t   i;
  uint32_t h = 0;
  h = (31*h) + key.first;
  h = (31*h) + key.second;
  h ^= (h >> 20) ^ (h >> 12);
  return h ^ (h >> 7) ^ (h >> 4);
}
static size_t indexFor(uint32_t ha6, size_t length){
  return ha6 & (length - 1);
}
bool isHit(HashMapEntry *e, pair key, uint32_t ha6){
  return(e->ha6 == ha6
          &&cmpP(e->key, key)==0);
}
static void copyOrFree(pair value, const void**valPtr){
  if (valPtr != NULL)
    ;;//*valPtr = value;
}
int updateValue(mpp*karta, HashMapEntry*e, pair newVal, const void**oldValPtr){
  copyOrFree( e->value, oldValPtr);
  e->value = newVal;
  return 1;
}
mpp *newMap(){
  HashMapEntry **table;
  mpp       *karta = malloc(sizeof(*karta));
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
int mapPut(mpp*karta, pair key, pair value){
  const void**oldValPtr=NULL;
  HashMapEntry  *e;
  size_t         newCapacity;
  HashMapEntry **newTable;
  size_t         i;
  uint32_t ha6  = doHash(key);
  size_t   gIndex = indexFor(ha6, karta->capacity);
  for(e = karta->table[gIndex]; e != NULL; e = e->next) {
    if(isHit(e, key, ha6) == 0)
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
pair mapGet(mpp*karta, pair key){
  HashMapEntry *e;
  uint32_t      ha6  = doHash(key);
  size_t        gIndex = indexFor(ha6, karta->capacity);
  for(e = karta->table[gIndex]; e != NULL; e = e->next) {
    if(isHit(e, key, ha6))
      return e->value;
  }
  return(pair){0,0};
}
bool mapHas(mpp*karta, pair key){
  HashMapEntry *e;
  uint32_t      ha6  = doHash(key);
  size_t        gIndex = indexFor(ha6, karta->capacity);
  for (e = karta->table[gIndex]; e != NULL; e = e->next) {
    if (isHit(e, key, ha6))
      return 1;
  }
  return 0;
}
void mapDel(mpp*karta, pair key){
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
size_t mapSize(const mpp*karta){
  return karta->size;
}
bool mapEmpty(const mpp*karta){
  return (karta->size == 0);
}
void mapClear(mpp*karta){
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
void mapDestroy(mpp*karta){
  if (karta == NULL)
    return;
  mapClear(karta);
  free(karta->table);
  free(karta);
}
#endif

/////////////////////////
int**rooms;
mpp*memo;//map{pair,pair}
int t, n, m;

pair dpf(int r, int turns){
  pair p = newpair(r, turns);
  if(mapHas(memo, p))
    return mapGet(memo, p);
  if(turns == 0)
    return newpair(0, 0);
  int maxi = -1,
      mini =(int)1e9;
  for(int r2=0; r2<n; r2++){
    pair nxt = dpf(r2, turns - 1);
    maxi = fmax(maxi, nxt.first  + rooms[r][r2]);
    mini = fmin(mini, nxt.second + rooms[r][r2]);
  }
  pair rv = newpair(maxi, mini);
  mapPut(memo, p, rv);
  return rv;
}
int main(){
  memo = newMap();
  scanf("%d", &n);
  while(n>0){
    rooms = calloc(n, sizeof(int*));
    for(int i=0; i<n; i++){
      rooms[i] = calloc(n, sizeof(int));
      for(int j=0; j<n; j++)
        scanf("%d", &rooms[i][j]);
    }
    scanf("%d", &m);
    pair p = dpf(0, m);
    printf("%d %d\n", p.first, p.second);
    freemat(rooms, n);
    mapClear(memo);
    scanf("%d", &n);
  }
  return 0;
}
