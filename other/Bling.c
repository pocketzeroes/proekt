#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
static inline ll max(ll a, ll b){return a>b?a:b;}
const ll base = 12445ll;
typedef struct{
  ll a[3];
}trip;
trip newtrip(ll a, ll b, ll c){
  trip rv;
  rv.a[0] = a;
  rv.a[1] = b;
  rv.a[2] = c;
  return rv;
}

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
ll mapGet(mll *karta, ll key){
  HashMapEntry *e;
  uint32_t      ha6  = doHash(key);
  size_t        gIndex = indexFor(ha6, karta->capacity);
  for (e = karta->table[gIndex]; e != NULL; e = e->next) {
    if (isHit(e, key, ha6))
      return e->value;
  }
  return NULL;
}
ll mapHas(mll *karta, ll key){
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

mll*DP;


ll end_fruit(ll d){
    if(d <= 0)
        return 0;
    ll t = 1;
    for(int c1=0; c1<((d-1)/3); ++c1)
        t *= 4;
    return t*3;
}
ll dp(ll d, ll bling, ll fruit, trip trees, trip exotic){
    if(d == 0)
        return 100*bling;
    ll extra = 0;
    if(bling>12){
        extra += 100*(bling-12);
        bling = 12;
    }
    if(fruit > 12){
        extra += 100*max(fruit-12, end_fruit(d-3) * (fruit-12));
        fruit = 12;
    }
    for(int i=0; i<3; ++i){
        if(trees.a[i] > 4){
            extra += 100*(trees.a[i] - 4) * end_fruit(d-i);
            trees.a[i] = 4;
        }
        if(exotic.a[i] > 1){
            extra += 500*(exotic.a[i] - 1) * end_fruit(d-i);
            exotic.a[i] = 1;
        }
    }
    ll stuff[9];
    stuff[0]=d;
    stuff[1]=bling;
    stuff[2]=fruit;
    stuff[3]=trees.a[0];
    stuff[4]=trees.a[1];
    stuff[5]=trees.a[2];
    stuff[6]=exotic.a[0];
    stuff[7]=exotic.a[1];
    stuff[8]=exotic.a[2];
    ll h=0;
    for(int z=0;z<9;z++){ll t = stuff[z];
        h *= base;
        h += t;
    }
    if(mapHas(DP, h))
        return extra + mapGet(DP, h);
    ll ans = 0;
    ll tot_fruit = fruit + 3*trees.a[0];
    ll exo = 3*exotic.a[0];
    for(int sell1 = 0; sell1 < (tot_fruit+1); ++sell1){
        for(int sell2 = 0; sell2 < (exo+1); ++sell2){
            ll tot_bling = 100 * bling + 100 * sell1 + 500 * sell2;
            trip trees2  = newtrip(trees.a[1], trees.a[2], trees.a[0] + tot_fruit - sell1);
            trip exotic2 = newtrip(exotic.a[1], exotic.a[2], exotic.a[0] + exo - sell2   );
            ll temp1 = dp(d-1, tot_bling/100, 0, trees2, exotic2);
            ans = max(temp1, ans);
            if(tot_bling >= 400){
                ll temp2 = dp(d-1, tot_bling/100 + 1, 0, trees2, exotic2);
                ans = max(temp2, ans);
            }
            if(tot_bling >= 400){
                exotic2.a[2]++;
                ll temp3 = dp(d-1, tot_bling/100 - 4, 0, trees2, exotic2);
                ans = max(temp3, ans);
            }
        }
    }
    mapPut(DP, h, ans);
    return extra + ans;
}
int main(){
    DP=newMap();
    int d, b, f, t0, t1, t2;
    scanf("%d %d %d %d %d %d", &d, &b, &f, &t0, &t1, &t2);
    ll ans = b%100;
    b /= 100;
    ans += dp(d, b, f, newtrip(t0,t1,t2), newtrip(0,0,0));
    printf("%lld\n", ans);
    return 0;
}
