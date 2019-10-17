#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
char buff[100001];
char*getln(){
  gets(buff);
  return strdup(buff);
}
#define pb(zpv, zvv) zpv.ptr = pushbackS(zpv.ptr, &zpv.sz, zvv)
#define pbn(zpv, zvv) zpv.ptr = pushbackN(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
char**pushbackS(char**array, int *size, char*value) {
  char**output = resizeArray(array, char*, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
  char**ptr;
  int sz;
}vecs;
vecs newVecS(){
  vecs rez;
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
}
vecs split(char*s){
  vecs rez=newVecS();
  while(1){
    sscanf(s, "%s", &buff);
    rez.ptr = pushbackS(rez.ptr, &rez.sz, strdup(buff));
    s = strchr(s, ' ');
    if(s==NULL)break;
    s++;
  }
  return rez;
}

#if 1////////////////msi
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
msi *newMap(void);
int mapHas(msi *karta, const char key[]);
void mapDel(msi *karta, const char key[]);
size_t mapSize(const msi *karta);
int hashMapIsEmpty(const msi *karta);
void mapClear(msi *karta);
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
msi *newMap(void ) {
  HashMapEntry**table;
  msi*karta =(msi*)malloc(sizeof(*karta));
  if (karta == NULL)
    return NULL;
  table =(HashMapEntry**)calloc(INITIAL_CAPACITY, sizeof(*karta->table));
  if(table == NULL){
    free(karta);
    return NULL;
  }
  setTable(karta, table, INITIAL_CAPACITY);
  karta->size = 0;
  return karta;
}
int mapPut(msi *karta, const char key[], int value){
  const void**oldValPtr=NULL;
  HashMapEntry*e;
  size_t         newCapacity;
  HashMapEntry**newTable;
  size_t         i;
  uint32_t ha6  = doHash(key);
  size_t   gIndex = indexFor(ha6, karta->capacity);
  for (e = karta->table[gIndex]; e != NULL; e = e->next) {
    if (isHit(e, key, ha6) == 0)
      continue;
    return updateValue(karta, e, value, oldValPtr);
  }
  e = (HashMapEntry*)calloc(1, sizeof(HashMapEntry));
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
  newTable = (HashMapEntry**)calloc(newCapacity, sizeof(*newTable));
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
  return 0;
}
int mapHas(msi *karta, const char key[]) {
  HashMapEntry *e;
  uint32_t      ha6  = doHash(key);
  size_t        gIndex = indexFor(ha6, karta->capacity);
  for (e = karta->table[gIndex]; e != NULL; e = e->next) {
    if (isHit(e, key, ha6))
      return 1;
  }
  return 0;
}
void mapDel(msi *karta, const char key[]){
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
void mapClear(msi *karta) {
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
  char*key;
  int  val;
}kvp;

void hashMapDestroy(msi *karta) {
  if (karta == NULL)
    return;
  mapClear(karta);
  free(karta->table);
  free(karta);
}
#endif

#define rep(i,a,b) for(__typeof(b) i=a; i<(b); ++i)

typedef struct{//node
    msi*   next;
    msi*   answers;
    double probability;
    int    total_answers;
}Node;

Node newNode(){
    Node rv;
    rv.next          = newMap();
    rv.answers       = newMap();
    rv.probability   = 0.0;
    rv.total_answers = 0;
    return rv;
}

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
Node*pushbackN(Node*array, int *size, Node value){
  Node*output = resizeArray(array, Node, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	Node*ptr;
	int sz;
}vecn;
vecn newVecN(){
	vecn rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}


vecn nodes;//of Node
double traverse(int j, double*it, int left){
    if(left == 0)
        return 0;
    double now = nodes.ptr[j].probability + *it;
    double move = 0;
    void doit(kvp*w){
      move += traverse(w->val, it+1, left - 1) * nodes.ptr[w->val].total_answers;
    }
    mapForEach(nodes.ptr[j].next, doit);
    return fmax(now, move / nodes.ptr[j].total_answers);
}
int main(){
    pbn(nodes, newNode());
    int t, n;
    scanf("%d %d", &t, &n);
    char*s = getln();
    rep(i,0,n){
        s = getln();
        vecs words = split(s);
        char*answer = words.ptr[words.sz-1];
        words.sz--;
        mapPut(nodes.ptr[0].answers, answer, mapGet(nodes.ptr[0].answers, answer)+1);
        int index=0;
        for(int z=0;z<words.sz;z++){char*cur = words.ptr[z];
            if(!mapHas(nodes.ptr[index].next, cur)){
                mapPut(nodes.ptr[index].next, cur, nodes.sz);
                pbn(nodes, newNode());
            }
            index = mapGet(nodes.ptr[index].next, cur);
            mapPut(nodes.ptr[index].answers, answer, mapGet(nodes.ptr[index].answers, answer)+1);
        }
    }
    for(int z=0;z<nodes.sz;z++){Node*node = &nodes.ptr[z];
        int s  = 0,
            ma = 0;
        void doit(kvp*w){
            s += w->val;
            ma = fmax(ma, w->val);
        }
        mapForEach(node->answers, doit);
        node->probability = ma / (double)(s);
        node->total_answers = s;
    }
    double best[t+1]; clr(best);
    for(int i=t-1; i>=0; i--)
        best[i] = traverse(0, best+i+1, t-i);
    printf("%.10lf\n", best[0]);
    return 0;
}
