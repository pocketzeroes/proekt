#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;

#if 1////////////////mll

#include<stdint.h>
static const size_t INITIAL_CAPACITY = 16;
static const size_t MAXIMUM_CAPACITY = (1U << 31);
static const float  LOAD_FACTOR      = 0.75;
#ifndef HASHMAP_H
#define HASHMAP_H
typedef struct mll mll;
mll*newMap(void);
ll    mapHas(mll*karta, ll key);
void   mapDel(mll*karta, ll key);
size_t mapSize(const mll *karta);
ll    hashMapIsEmpty(const mll *karta);
void   mapClear(mll *karta);
void   hashMapDestroy(mll *karta);
#endif
void DUMMYfree(const void*pp){
    ;
}
typedef struct HashMapEntry{
  ll                   key;
  ll                  value;
  struct HashMapEntry *next;
  uint32_t             ha6;
} HashMapEntry;
struct mll {
  HashMapEntry **table;
  size_t         capacity;
  size_t         size;
  size_t         threshold;
};
static void setTable(mll *karta, HashMapEntry **table, size_t capacity) {
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
static ll isHit(HashMapEntry *e, ll key, uint32_t ha6) {
  return (e->ha6 == ha6
          && (e->key == key));
}
static void copyOrFree( ll value, const void **valPtr) {
  if (valPtr != NULL)
    ;;//*valPtr = value;
}
static ll updateValue(mll *karta, HashMapEntry *e, ll newVal, const void **oldValPtr) {
  copyOrFree( e->value, oldValPtr);
  e->value = newVal;
  return 1;
}
mll *newMap(void ) {
  HashMapEntry **table;
  mll       *karta = malloc(sizeof(*karta));
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
ll mapPut(mll *karta, ll key, ll value){
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
ll mapGet(mll *karta, ll key) {
  HashMapEntry *e;
  uint32_t      ha6  = doHash(key);
  size_t        gIndex = indexFor(ha6, karta->capacity);
  for (e = karta->table[gIndex]; e != NULL; e = e->next) {
    if (isHit(e, key, ha6))
      return e->value;
  }
  return NULL;
}
ll mapHas(mll *karta, ll key) {
  HashMapEntry *e;
  uint32_t      ha6  = doHash(key);
  size_t        gIndex = indexFor(ha6, karta->capacity);
  for (e = karta->table[gIndex]; e != NULL; e = e->next) {
    if (isHit(e, key, ha6))
      return 1;
  }
  return 0;
}
void mapDel(mll *karta, ll key){
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
size_t mapSize(const mll *karta) {
  return karta->size;
}
ll hashMapIsEmpty(const mll *karta) {
  return (karta->size == 0);
}
void mapClear(mll *karta) {
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
void hashMapDestroy(mll *karta){
  if (karta == NULL)
    return;
  mapClear(karta);
  free(karta->table);
  free(karta);
}
#endif

ll s, d, t, n, a[505], o[505];
mll*dp;

ll left(ll pos){
  for(int i=0; i<n; ++i)
    if(a[i] <= pos && pos < o[i])
      return a[i];
  return pos;
}
ll next(ll pos){
  for(int i=0; i<n; ++i)
    if(a[i] >= pos)
      return a[i];
  return pos;
}
ll fastForward(ll distance){
  ll jumps = distance / d;
  ll ret = fminl((jumps+1)*t, fminl(jumps*t + distance-jumps*d, distance));
  return ret;
}
ll rec(ll pos){
  if(pos >= s)
    return 0;
  if(mapHas(dp, pos))
    return mapGet(dp, pos);
  ll best = 505LL*1000000000LL;
  ll nextIsland = next(pos);
  if(pos < nextIsland)
    best = fminl(best, fastForward(nextIsland-pos) + rec(nextIsland));
  ll jumpy = (nextIsland-pos)/d;
  if(jumpy > 0)
    best = fminl(best, jumpy*t + rec(pos + jumpy*d));
  ll jumpPos = left(pos + d);
  if(jumpPos > nextIsland)
    best = fminl(best, t + rec(jumpPos));
  for(int i=0; i<n; ++i){
    ll revJump = a[i] - d;
    if(pos < revJump && revJump < nextIsland)
      best = fminl(best, fastForward(revJump-pos) + rec(revJump));
    revJump = o[i] - d;
    if(pos < revJump && revJump < nextIsland)
      best = fminl(best, fastForward(revJump-pos) + rec(revJump));
  }
  if(pos + d >= s)
    best = fminl(best, t);
  mapPut(dp, pos, best);
  return best;
}
int main(){
  dp = newMap();
  scanf("%lld %lld %lld %lld", &s, &d, &t, &n);
  for(int i=0; i<n; ++i)
    scanf("%lld %lld", &a[i], &o[i]);
  a[n] = o[n] = s;
  n++;
  printf("%lld\n", rec(0));
  return 0;
}
