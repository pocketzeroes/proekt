#pragma GCC optimize "-O3" // editingexplosion
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

void iota(int*arr, int sz, int beg){
  for(int i=0; i<sz; i++)
    arr[i] = i;
}

char buff[100000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}
int min_element(int*arr, int sz){
  int mine = arr[0];
  for(int i=1;i<sz;i++)
    if(arr[i]<mine)
      mine=arr[i];
  return mine;
}

int vsz;

#if 1///////////////////////////mvi
#include<stdint.h>
static const size_t INITIAL_CAPACITY = 16;
static const size_t MAXIMUM_CAPACITY = (1U << 31);
static const float  LOAD_FACTOR      = 0.75;
#ifndef HASHMAP_H
#define HASHMAP_H
#include <stdlib.h>
typedef struct mvi mvi;
mvi *newMap(void);
int mapHas(mvi *karta, const  int*key);
void mapDel(mvi *karta, const int*key);
size_t mapSize(const mvi *karta);
int hashMapIsEmpty(const mvi *karta);
void mapClear(mvi *karta);
void hashMapDestroy(mvi *karta);
#endif
void DUMMYfree(const void*pp){
    ;
}
typedef struct HashMapEntry{
  int                 *key;
  int                  value;
  struct HashMapEntry *next;
  uint32_t             ha6;
} HashMapEntry;
struct mvi{
  HashMapEntry **table;
  size_t         capacity;
  size_t         size;
  size_t         threshold;
};
static void setTable(mvi*karta, HashMapEntry**table, size_t capacity){
  karta->table     = table;
  karta->capacity  = capacity;
  karta->threshold = (size_t) (capacity * LOAD_FACTOR);
}
static uint32_t doHash(const int*key){
  size_t   length;
  size_t   i;
  uint32_t h = 0;
  if(key == NULL)
    return 0;
  length = vsz;
  for (i = 0; i < length; ++i) {
    h = (31 * h) + key[i];
  }
  h ^= (h >> 20) ^ (h >> 12);
  return h ^ (h >> 7) ^ (h >> 4);
}
static size_t indexFor(uint32_t ha6, size_t length){
  return ha6 & (length - 1);
}
static int isHit(HashMapEntry*e, const int*key, uint32_t ha6){
  return (e->ha6 == ha6
          && (e->key == key || (key != NULL && memcmp(e->key, key, vsz*sizeof(int)) == 0)));
}
static void copyOrFree(int value, const void**valPtr){
  if (valPtr != NULL)
    ;;//*valPtr = value;
}
static int updateValue(mvi*karta, HashMapEntry*e, int newVal, const void**oldValPtr){
  copyOrFree( e->value, oldValPtr);
  e->value = newVal;
  return 1;
}
mvi*newMap(){
  HashMapEntry **table;
  mvi       *karta = malloc(sizeof(*karta));
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
int mapPut(mvi*karta, const int*key, int value){
  const void**oldValPtr=NULL;
  HashMapEntry  *e;
  size_t         newCapacity;
  HashMapEntry **newTable;
  size_t         i;
  uint32_t ha6  = doHash(key);
  size_t   gIndex = indexFor(ha6, karta->capacity);
  for(e = karta->table[gIndex]; e != NULL; e = e->next){
    if(isHit(e, key, ha6) == 0)
      continue;
    return updateValue(karta, e, value, oldValPtr);
  }
  e = calloc(1, sizeof(HashMapEntry));
  if (e == NULL)
    return 0;
  if(key != NULL){
    e->key = calloc(vsz, sizeof(int)); //strdup(key);
    memcpy(e->key, key, vsz*sizeof(int));
    if(e->key == NULL){
      free(e);
      return 0;
    }
  }
  if(updateValue(karta, e, value, oldValPtr) == 0){
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
int mapGet(mvi*karta, const int*key){
  HashMapEntry *e;
  uint32_t      ha6  = doHash(key);
  size_t        gIndex = indexFor(ha6, karta->capacity);
  for (e = karta->table[gIndex]; e != NULL; e = e->next) {
    if (isHit(e, key, ha6))
      return e->value;
  }
  return NULL;
}
int mapHas(mvi*karta, const int*key){
  HashMapEntry *e;
  uint32_t      ha6  = doHash(key);
  size_t        gIndex = indexFor(ha6, karta->capacity);
  for (e = karta->table[gIndex]; e != NULL; e = e->next) {
    if (isHit(e, key, ha6))
      return 1;
  }
  return 0;
}
void mapDel(mvi*karta,const int*key){
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
size_t mapSize(const mvi*karta){
  return karta->size;
}
int hashMapIsEmpty(const mvi*karta){
  return (karta->size == 0);
}
void mapClear(mvi*karta){
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
void hashMapDestroy(mvi*karta){
  if (karta == NULL)
    return;
  mapClear(karta);
  free(karta->table);
  free(karta);
}
#endif

enum{mod = 998244353};
char*s;
int  slen;
int  d;

mvi*mp;

int dfs(int*v){
    if(min_element(v, vsz)>d)
        return 0;
    if(mapHas(mp, v))
        return mapGet(mp, v);
    int ret=0;
    if(v[vsz-1]==d)
        ret = 1;
    for(int i='A'; i<='Z'; i++){
        int w[vsz];
        for(int j=0; j<=slen; j++){
            w[j]=v[j]+1;
            if(j)
                w[j] = fmin(w[j], w[j-1] + 1);
            if(j)
                w[j] = fmin(w[j], v[j-1]+(i!=s[j-1]));
        }
        ret += dfs(w);
        if(ret >= mod)
           ret -= mod;
    }
    mapPut(mp, v, ret);
    return ret;
}
int main(){
    mp = newMap();
    s = getstr();
    scanf("%d", &d);
    slen = strlen(s);
    vsz=slen+1;
    int v[vsz];
    iota(v, vsz, 0);
    printf("%d\n", dfs(v));
    return 0;
}
