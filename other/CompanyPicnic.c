#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))

char buff[1000000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}
double getdbl(){
  double x;
  scanf("%lf", &x);
  return x;
}

typedef double dbl;
typedef struct{
  int first;
  dbl second;
}pair;
pair newPair(int a, dbl b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}

#if 1///////////////////////////msi
#include <limits.h>
#include <stdint.h>
#include <string.h>
static const size_t INITIAL_CAPACITY = 16;
static const size_t MAXIMUM_CAPACITY = (1U << 31);
static const float  LOAD_FACTOR      = 0.75;
#ifndef HASHMAP_H
#define HASHMAP_H
#include <stdlib.h>
typedef struct msi msi;
msi *newHashMap(void);
int mapContainsKey(msi *karta, const char key[]);
void hashMapRemove(msi *karta, const char key[], const void **valPtr);
size_t mapSize(const msi *karta);
int hashMapIsEmpty(const msi *karta);
void hashMapClear(msi *karta);
void hashMapDestroy(msi *karta);
#endif
void DUMMYfree(const void*pp){
    ;
}
typedef struct HashMapEntry {
  char                *key;
  int                  value;
  struct HashMapEntry *next;
  uint32_t             ha6;
} HashMapEntry;
struct msi {
  HashMapEntry **table;
  size_t         capacity;
  size_t         size;
  size_t         threshold;
};
static void setTable(msi *karta, HashMapEntry **table, size_t capacity) {
  karta->table     = table;
  karta->capacity  = capacity;
  karta->threshold = (size_t) (capacity * LOAD_FACTOR);
}
static uint32_t doHash(const char key[]) {
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
msi *newHashMap(void ) {
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
int mapPut(msi *karta, const char key[], int value){
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
int mapGet(msi *karta, const char key[]) {
  HashMapEntry *e;
  uint32_t      ha6  = doHash(key);
  size_t        gIndex = indexFor(ha6, karta->capacity);
  for (e = karta->table[gIndex]; e != NULL; e = e->next) {
    if (isHit(e, key, ha6))
      return e->value;
  }
  return NULL;
}
int mapContainsKey(msi *karta, const char key[]) {
  HashMapEntry *e;
  uint32_t      ha6  = doHash(key);
  size_t        gIndex = indexFor(ha6, karta->capacity);
  for (e = karta->table[gIndex]; e != NULL; e = e->next) {
    if (isHit(e, key, ha6))
      return 1;
  }
  return 0;
}
void hashMapRemove(msi *karta, const char key[], const void **valPtr) {
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
size_t mapSize(const msi *karta) {
  return karta->size;
}
int hashMapIsEmpty(const msi *karta) {
  return (karta->size == 0);
}
void hashMapClear(msi *karta) {
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
void hashMapDestroy(msi *karta) {
  if (karta == NULL)
    return;
  hashMapClear(karta);
  free(karta->table);
  free(karta);
}
#endif
enum{BUFFSZ=1200};
int    n;
int    ceo;
char*  name       [BUFFSZ];
double speed      [BUFFSZ];
char*  supervisor [BUFFSZ];
msi*   name_to_index;
int    edge_tot   [BUFFSZ];
int    edge       [BUFFSZ][BUFFSZ];
pair   best_unused[BUFFSZ]; 
pair   best_used  [BUFFSZ]; 


void dfs(int node) {
    for (int i = 0; i < edge_tot[node]; ++i) {
        int j = edge[node][i];
        dfs(j);
        best_unused[node].first += best_used[j].first;
        best_unused[node].second += best_used[j].second;
    }
    best_used[node] = best_unused[node];
    for (int i = 0; i < edge_tot[node]; ++i) {
        int j = edge[node][i];
        pair new_value = best_unused[node];
        new_value.first += best_unused[j].first;
        new_value.first -= best_used[j].first;
        new_value.first += 1;
        new_value.second += best_unused[j].second;
        new_value.second -= best_used[j].second;
        new_value.second += min(speed[node], speed[j]);
        if(best_used[node].first < new_value.first || ( best_used[node].first == new_value.first && best_used[node].second < new_value.second))
            best_used[node] = new_value;
    }
}
int main(){
    name_to_index = newHashMap();
    scanf("%d", &n);
    for(int i=0; i<n; ++i){
        name      [i] = getstr();
        speed     [i] = getdbl();
        supervisor[i] = getstr();
        mapPut(name_to_index, name[i], i);
    }
    for(int i=0; i<n; ++i){
        if(strcmp(supervisor[i], "CEO")==0)
            ceo = i;
        else{
            int j = mapGet(name_to_index, supervisor[i]);
            edge[j][edge_tot[j]++] = i;
        }
    }
    dfs(ceo);
    printf("%d %lf\n", best_used[ceo].first, best_used[ceo].second/(double)best_used[ceo].first);
    return 0;
}
