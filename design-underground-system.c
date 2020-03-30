#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)

#if 1///////////////////////////msi
#include<limits.h>
#include<stdint.h>
#include<string.h>
static const size_t INITIAL_CAPACITY = 16;
static const size_t MAXIMUM_CAPACITY = (1U << 31);
static const float  LOAD_FACTOR      = 0.75;
#ifndef HASHMAP_H
#define HASHMAP_H
#include<stdlib.h>
typedef struct msi msi;
msi*newMsi();
int msiHas(msi *karta, const char key[]);
void msiDel(msi *karta, const char key[]);
size_t msiSize(const msi *karta);
int msiEmpty(const msi *karta);
void msiClear(msi *karta);
void msiDestroy(msi *karta);
#endif
void DUMMYfree(const void*pp){
    ;
}
typedef struct HashMapEntry{
  char                *key;
  int                  value;
  struct HashMapEntry *next;
  uint32_t             ha6;
} HashMapEntry;
struct msi{
  HashMapEntry **table;
  size_t         capacity;
  size_t         size;
  size_t         threshold;
};
static void setTable(msi *karta, HashMapEntry **table, size_t capacity){
  karta->table     = table;
  karta->capacity  = capacity;
  karta->threshold = (size_t) (capacity * LOAD_FACTOR);
}
static uint32_t doHash(const char key[]){
  size_t   length;
  size_t   i;
  uint32_t h = 0;
  if (key == NULL)
    return 0;
  length = strlen(key);
  for (i = 0; i < length; ++i) {
    h = (31 * h) + key[i];
  }
  h ^= (h >> 20) ^ (h >> 12);
  return h ^ (h >> 7) ^ (h >> 4);
}
static size_t indexFor(uint32_t ha6, size_t length) {
  return ha6 & (length - 1);
}
static int isHit(HashMapEntry *e, const char key[], uint32_t ha6) {
  return (e->ha6 == ha6
          && (e->key == key || (key != NULL && strcmp(e->key, key) == 0)));
}
static void copyOrFree( int value, const void **valPtr) {
  if (valPtr != NULL)
    ;;//*valPtr = value;
}
static int updateValue(msi *karta, HashMapEntry *e, int newVal, const void **oldValPtr) {
  copyOrFree( e->value, oldValPtr);
  e->value = newVal;
  return 1;
}
msi*newMsi(){
  HashMapEntry **table;
  msi       *karta = malloc(sizeof(*karta));
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
int msiPut(msi *karta, const char key[], int value){
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
  if (key != NULL) {
    e->key = strdup(key);
    if (e->key == NULL) {
      free(e);
      return 0;
    }
  }
  if (updateValue(karta, e, value, oldValPtr) == 0) {
    free(e->key);
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
int msiGet(msi *karta, const char key[]) {
  HashMapEntry *e;
  uint32_t      ha6  = doHash(key);
  size_t        gIndex = indexFor(ha6, karta->capacity);
  for (e = karta->table[gIndex]; e != NULL; e = e->next) {
    if (isHit(e, key, ha6))
      return e->value;
  }
  return NULL;
}
int msiHas(msi *karta, const char key[]) {
  HashMapEntry *e;
  uint32_t      ha6  = doHash(key);
  size_t        gIndex = indexFor(ha6, karta->capacity);
  for (e = karta->table[gIndex]; e != NULL; e = e->next) {
    if (isHit(e, key, ha6))
      return 1;
  }
  return 0;
}
void msiDel(msi *karta, const char key[]){
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
  if (e == NULL) {
    return;
  }
  free(e->key);
  free(e);
}
size_t msiSize(const msi *karta) {
  return karta->size;
}
int msiEmpty(const msi *karta) {
  return (karta->size == 0);
}
void msiClear(msi *karta) {
  size_t i;
  for (i = 0; i < karta->capacity; ++i) {
    HashMapEntry *e;
    HashMapEntry *next;
    for (e = karta->table[i]; e != NULL; e = next) {
      free(e->key);
      next = e->next;
      free(e);
    }
    karta->table[i] = NULL;
  }
}
void msiDestroy(msi *karta) {
  if (karta == NULL)
    return;
  msiClear(karta);
  free(karta->table);
  free(karta);
}
#endif

typedef long long ll;
typedef struct{
  ll first, second;
}pll;
pll newpll(ll a, ll b){
  return(pll){a,b};
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


#ifndef HA6MAP_H
#define HA6MAP_H
typedef struct hmEntry{
  pair           key;
  pll            value;
  struct hmEntry*next;
  uint32_t       ha6;
}hmEntry;

typedef struct mpp{
  hmEntry**table;
  size_t   capacity;
  size_t   size;
  size_t   threshold;
}mpp;

mpp*newMpp();
bool   mppHas(mpp*karta, pair key);
void   mppDel(mpp*karta, pair key);
size_t mppSize(const mpp*karta);
bool   mppEmpty(const mpp*karta);
void   mppClear(mpp*karta);
void   mppDestroy(mpp*karta);
#endif





static void set_Table(mpp*karta, hmEntry**table, size_t capacity){
  karta->table     = table;
  karta->capacity  = capacity;
  karta->threshold = (size_t) (capacity * LOAD_FACTOR);
}
static uint32_t do_Hash(pair key){
  size_t   length;
  size_t   i;
  uint32_t h = 0;
  h = (31*h) + key.first;
  h = (31*h) + key.second;
  h ^= (h >> 20) ^ (h >> 12);
  return h ^ (h >> 7) ^ (h >> 4);
}
static size_t index_For(uint32_t ha6, size_t length){
  return ha6 & (length - 1);
}
bool is_Hit(hmEntry *e, pair key, uint32_t ha6){
  return(e->ha6 == ha6
          &&cmpP(e->key, key)==0);
}
static void copy_Or_Free(pll value, const void**valPtr){
  if (valPtr != NULL)
    ;;//*valPtr = value;
}
int update_Value(mpp*karta, hmEntry*e, pll newVal, const void**oldValPtr){
  copy_Or_Free( e->value, oldValPtr);
  e->value = newVal;
  return 1;
}
mpp*newMpp(){
  hmEntry **table;
  mpp       *karta = malloc(sizeof(*karta));
  if (karta == NULL)
    return NULL;
  table = calloc(INITIAL_CAPACITY, sizeof(*karta->table));
  if (table == NULL) {
    free(karta);
    return NULL;
  }
  set_Table(karta, table, INITIAL_CAPACITY);
  karta->size = 0;
  return karta;
}
int  mppPut(mpp*karta, pair key, pll value){
  const void**oldValPtr=NULL;
  hmEntry  *e;
  size_t         newCapacity;
  hmEntry **newTable;
  size_t         i;
  uint32_t ha6  = do_Hash(key);
  size_t   gIndex = index_For(ha6, karta->capacity);
  for(e = karta->table[gIndex]; e != NULL; e = e->next) {
    if(is_Hit(e, key, ha6) == 0)
      continue;
    return update_Value(karta, e, value, oldValPtr);
  }
  e = calloc(1, sizeof(hmEntry));
  if (e == NULL)
    return 0;
  e->key = (key);
  if (update_Value(karta, e, value, oldValPtr) == 0) {
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
    hmEntry *next;
    for (e = karta->table[i]; e != NULL; e = next) {
      gIndex   = index_For(e->ha6, newCapacity);
      next    = e->next;
      e->next = newTable[gIndex];
      newTable[gIndex] = e;
    }
  }
  free(karta->table);
  set_Table(karta, newTable, newCapacity);
  return 1;
}
pll  mppGet(mpp*karta, pair key){
  hmEntry *e;
  uint32_t      ha6  = do_Hash(key);
  size_t        gIndex = index_For(ha6, karta->capacity);
  for(e = karta->table[gIndex]; e != NULL; e = e->next) {
    if(is_Hit(e, key, ha6))
      return e->value;
  }
  return(pll){0,0};
}
bool mppHas(mpp*karta, pair key){
  hmEntry *e;
  uint32_t      ha6  = do_Hash(key);
  size_t        gIndex = index_For(ha6, karta->capacity);
  for (e = karta->table[gIndex]; e != NULL; e = e->next) {
    if (is_Hit(e, key, ha6))
      return 1;
  }
  return 0;
}
void mppDel(mpp*karta, pair key){
  uint32_t      ha6  = do_Hash(key);
  size_t        gIndex = index_For(ha6, karta->capacity);
  hmEntry *prev  = karta->table[gIndex];
  hmEntry *e     = prev;
  while (e != NULL) {
    hmEntry *next = e->next;
    if (is_Hit(e, key, ha6)) {
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
size_t mppSize(const mpp*karta){
  return karta->size;
}
bool mppEmpty(const mpp*karta){
  return (karta->size == 0);
}
void mppClear(mpp*karta){
  size_t i;
  for (i = 0; i < karta->capacity; ++i) {
    hmEntry *e;
    hmEntry *next;
    for (e = karta->table[i]; e != NULL; e = next) {
      next = e->next;
      free(e);
    }
    karta->table[i] = NULL;
  }
}
void mppDestroy(mpp*karta){
  if (karta == NULL)
    return;
  mppClear(karta);
  free(karta->table);
  free(karta);
}
#endif
/////////////////////////////////////////////
typedef struct{
}UndergroundSystem;
UndergroundSystem*gptr;

int st [1000000+5];
int cur[1000000+5];
int cnt;
msi*name;
mpp*lmao;//map pair pll

UndergroundSystem*undergroundSystemCreate(){
    clr(st );
    clr(cur);
    cnt=0;
    name=newMsi();
    lmao=newMpp();
    return gptr;
}
void undergroundSystemCheckIn(UndergroundSystem*obj, int id, char*stationName, int t){
    if(!msiHas(name, stationName))
        msiPut(name, stationName, ++cnt);
    cur[id] = msiGet(name, stationName);
    st [id] = t;
}
void undergroundSystemCheckOut(UndergroundSystem*obj, int id, char*stationName, int t){
    if(!msiHas(name, stationName))
        msiPut(name, stationName, ++cnt);
    int hihi = msiGet(name, stationName);
    int haha = cur[id];
    pair hahi = newpair(haha, hihi);
    pll pp = mppGet(lmao, hahi);
    pp.first += (t-st[id]);
    pp.second++;
    mppPut(lmao, hahi, pp);
}
double undergroundSystemGetAverageTime(UndergroundSystem*obj, char*startStation, char*endStation){
    int s = msiGet(name, startStation);
    int t = msiGet(name, endStation  );
    pair pst = newpair(s, t);
    pll  kvp = mppGet(lmao, pst);
    return(double)(kvp.first)/
          (double)(kvp.second);
}
void undergroundSystemFree(UndergroundSystem*obj){
    msiDestroy(name);
    mppDestroy(lmao);
}
