#pragma GCC optimize "-O3" // subway
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
void swap(int*nums, int i, int j) {
   int t   = nums[i];
   nums[i] = nums[j];
   nums[j] = t;
}
void reverse(int*nums,int start,int end){
    while( start < end) {
        swap(nums, start, end);
        start++;
        end  --;
    }
}
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
char buff[100000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}
#define pb(zpv, zvv) zpv.ptr = pushback(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int*pushback(int*array, int*size, int value){
    int*output = resizeArray(array, int, *size + 1);
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

#if 1////////////////msi
#include<limits.h>
#include<stdint.h>
#include<string.h>
static const size_t msiINITIAL_CAPACITY = 16;
static const size_t msiMAXIMUM_CAPACITY = (1U << 31);
static const float  msiLOAD_FACTOR      = 0.75;
#ifndef HASHMAP_H
#define HASHMAP_H
#include<stdlib.h>
typedef struct msi msi;
msi *newMsi(void);
int msiHas(msi *karta, const char key[]);
#endif

typedef struct msiHashMapEntry{
  char                *key;
  int                  value;
  struct msiHashMapEntry *next;
  uint32_t             ha6;
} msiHashMapEntry;
struct msi{
  msiHashMapEntry **table;
  size_t         capacity;
  size_t         size;
  size_t         threshold;
};
static void msi_setTable(msi*karta, msiHashMapEntry **table, size_t capacity){
  karta->table     = table;
  karta->capacity  = capacity;
  karta->threshold = (size_t) (capacity * msiLOAD_FACTOR);
}
static uint32_t msi_doHash(const char key[]){
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
static size_t msi_indexFor(uint32_t ha6, size_t length){
  return ha6 & (length - 1);
}
static int msi_isHit(msiHashMapEntry *e, const char key[], uint32_t ha6){
  return (e->ha6 == ha6 && (e->key == key || (key != NULL && strcmp(e->key, key) == 0)));
}
static void msi_copyOrFree( int value, const void **valPtr){
  if (valPtr != NULL)
    ;;//*valPtr = value;
}
static int msi_updateValue(msi *karta, msiHashMapEntry *e, int newVal, const void **oldValPtr){
  msi_copyOrFree( e->value, oldValPtr);
  e->value = newVal;
  return 1;
}
msi*newMsi(){
  msiHashMapEntry **table;
  msi       *karta = malloc(sizeof(*karta));
  if (karta == NULL)
    return NULL;
  table = calloc(msiINITIAL_CAPACITY, sizeof(*karta->table));
  if (table == NULL) {
    free(karta);
    return NULL;
  }
  msi_setTable(karta, table, msiINITIAL_CAPACITY);
  karta->size = 0;
  return karta;
}
int msiPut(msi*karta, const char key[], int value){
  const void**oldValPtr=NULL;
  msiHashMapEntry  *e;
  size_t         newCapacity;
  msiHashMapEntry **newTable;
  size_t         i;
  uint32_t ha6  = msi_doHash(key);
  size_t   gIndex = msi_indexFor(ha6, karta->capacity);
  for (e = karta->table[gIndex]; e != NULL; e = e->next) {
    if (msi_isHit(e, key, ha6) == 0)
      continue;
    return msi_updateValue(karta, e, value, oldValPtr);
  }
  e = calloc(1, sizeof(msiHashMapEntry));
  if (e == NULL)
    return 0;
  if (key != NULL) {
    e->key = strdup(key);
    if (e->key == NULL) {
      free(e);
      return 0;
    }
  }
  if (msi_updateValue(karta, e, value, oldValPtr) == 0) {
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
  if (karta->capacity == msiMAXIMUM_CAPACITY) {
    karta->threshold = UINT_MAX;
    return 1;
  }
  newTable = calloc(newCapacity, sizeof(*newTable));
  if (newTable == NULL)
    return 0;
  for (i = 0; i < karta->capacity; ++i) {
    msiHashMapEntry *next;
    for (e = karta->table[i]; e != NULL; e = next) {
      gIndex   = msi_indexFor(e->ha6, newCapacity);
      next    = e->next;
      e->next = newTable[gIndex];
      newTable[gIndex] = e;
    }
  }
  free(karta->table);
  msi_setTable(karta, newTable, newCapacity);
  return 1;
}
int msiGet(msi*karta, const char key[]){
  msiHashMapEntry *e;
  uint32_t      ha6  = msi_doHash(key);
  size_t        gIndex = msi_indexFor(ha6, karta->capacity);
  for (e = karta->table[gIndex]; e != NULL; e = e->next) {
    if (msi_isHit(e, key, ha6))
      return e->value;
  }
  return NULL;
}
int msiHas(msi*karta, const char key[]){
  msiHashMapEntry *e;
  uint32_t      ha6  = msi_doHash(key);
  size_t        gIndex = msi_indexFor(ha6, karta->capacity);
  for (e = karta->table[gIndex]; e != NULL; e = e->next) {
    if (msi_isHit(e, key, ha6))
      return 1;
  }
  return 0;
}
void msiClear(msi*karta){
  size_t i;
  for (i = 0; i < karta->capacity; ++i) {
    msiHashMapEntry*e;
    msiHashMapEntry*next;
    for (e = karta->table[i]; e != NULL; e = next) {
      free(e->key);
      next = e->next;
      free(e);
    }
    karta->table[i] = NULL;
  }
}
void msiDestroy(msi*karta){
  if (karta == NULL)
    return;
  msiClear(karta);
  free(karta->table);
  free(karta);
}
size_t msiSize(const msi*karta){
  return karta->size;
}
#endif
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
#endif



///////////////////////////////////////////////
enum{ MAXSTOPS = 1000000};
enum{ MAXLINES = 100000 };
enum{ MAXNAME  = 30     };
enum{ INFTY = 1000000000};

int main(){
    int nkases;
    scanf("%d", &nkases);
    for(int kase=1; kase<=nkases; ++kase){
        getstr();
        msi*stopsbyname = newMsi();
        for(int stop=0, comma=1; comma; ++stop){
            char*name=getstr();
            comma = (name[strlen(name)-1] == ',');
            if(comma)
                name[strlen(name)-1]='\0';
            msiPut(stopsbyname, name, stop);
        }
        int nstops = msiSize(stopsbyname);
        getstr();
        msi*linesbyname = newMsi();
        for(int line=0, comma=1; comma; ++line){
            char*name=getstr();
            comma = (name[strlen(name)-1] == ',');
            if(comma)
                name[strlen(name)-1]='\0';
            msiPut(linesbyname, name, line);
        }
        int nlines = msiSize(linesbyname);
        vec lines[nlines]; clr(lines);
        vec stops[nstops]; clr(stops);
        for(int i=0; i<nlines; ++i){
            char*linename=getstr();
            int line = msiGet(linesbyname, linename);
            getstr();
            for(int comma=1; comma; ){
                char*stopname=getstr();
                comma = (stopname[strlen(stopname)-1] == ',');
                if(comma)
                    stopname[strlen(stopname)-1]='\0';
                int stop = msiGet(stopsbyname, stopname);
                pb(lines[line], stop);
                pb(stops[stop], line);
            }
        }
        getstr(); getstr(); getstr();
        char*sourcename=getstr();
        int source = msiGet(stopsbyname, sourcename);
        getstr(); getstr(); getstr();
        char*targetname=getstr();
        int target = msiGet(stopsbyname, targetname);
        bool linevisited[nlines]; clr(linevisited);
        vec queue=newVec();
        pb(queue, source);
        int best[nstops]; fill(best, nstops, -1);
        best[source] = 0;
        for(int cost=0; queue.sz; ++cost){
            vec rides=newVec();
            for(int z=0;z<queue.sz;z++){int stop = queue.ptr[z];
                if(stop == target)
                    printf("optimal travel from %s to %s: %d line%s, %d minute%s\n", sourcename, targetname, cost, cost==1?"":"s", best[stop], best[stop]==1?"":"s");
                for(int q=0;q<stops[stop].sz;q++){int line = stops[stop].ptr[q];
                   pb(rides, line);
                }
            }
            queue.sz=0;
            mii*updates = newMap();
            for(int z=0;z<rides.sz;z++){int line = rides.ptr[z];
                if(!linevisited[line]){
                    linevisited[line] = true;
                    for(int dir=0; dir<2; ++dir){
                        int curr = -INFTY;
                        for(int q=0;q<lines[line].sz;q++){int stop = lines[line].ptr[q];
                            ++curr;
                            if(best[stop] < 0)
                               mapPut(updates, stop, fmax(mapGet(updates, stop), curr));
                            else
                                curr = fmax(curr, best[stop]);
                        }
                        reverse(lines[line].ptr, 0, lines[line].sz-1);
                    }
                }
            }
            void doit(kvp*it){
                if(best[it->key] < 0)
                   pb(queue, it->key);
                if(best[it->key] < it->val)
                   best[it->key] = it->val;
            }
            mapForEach(updates, doit);
        }
    }
    return 0;
}
