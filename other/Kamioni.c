#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define swap(a,b) do{ __typeof(a) tp; tp = a; a = b; b = tp; }while(0)
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
#endif
ll Encode(int x, int y){
  return ((ll)x) * 1000000000 + y;
}


#define pb(zpv, zvv) zpv.ptr = pushback(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
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
typedef struct{
  int first;
  int second;
}pair;
pair newpair(int a, int b){
  return(pair){a,b};
}
#define pbp(zpv, zvv) zpv.ptr = pushbackP(zpv.ptr, &zpv.sz, zvv)
pair*pushbackP(pair*array, int *size, pair value){
  pair*output = resizeArray(array, pair, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	pair*ptr;
	int sz;
}vecp;
vecp newVecP(){
	vecp rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}


enum{ MAGIC = 200  };
enum{ MAXN = 100005};
enum{ MAXM = 100005};
ll inf = 1000000000000000LL;


typedef struct{
  ll x, y, ny;
  int id;
}event;
event newevent(ll x, ll y, ll ny, int id){
  return(event){x,y,ny,id};
}
int cmpE(const void*pa, const void*p_b){
  event*a=(event*)pa;
  event*b=(event*)p_b;
  if(a->x == b->x)
    return(a->y < b->y)?-1:1;
  else
    return(a->x < b->x)?-1:1;
}
#define pbe(zpv, zvv) zpv->ptr = pushbackE(zpv->ptr, &zpv->sz, zvv)
event*pushbackE(event*array, int *size, event value){
  event*output = resizeArray(array, event, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	event*ptr;
	int sz;
}vece;
vece newVecE(){
	vece rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
///////////////////////////////////////////////
  
int N, M, K, a, b;
vec pos[MAXN];
vece v, w;
vecp qs[MAXM];
int qid[MAXN];
int sol[MAXM];
mli*ids;// map pair int
int fake[MAXM];


void calc(int id, vece*v){
  ll y = -inf;
  for(int z=0;z<v->sz;z++){event e = v->ptr[z];
    if(e.id == id && e.y == e.ny)
      y = e.y;
    else if(e.id != id)
      if(e.y < y && e.ny > y && e.y != e.ny)
        ++sol[qid[e.id]];
  }
}
void solve_big(int id){
  for(int i=0; i<N; ++i)
    qid[i]=M;
  for(int z=0;z<qs[id].sz;z++){pair query = qs[id].ptr[z];
    qid[query.first] = query.second;
  }
  calc(id, &v);
}
void add(int i, vece*v, int type){
  ll t = 0;
  ll x = pos[i].ptr[0];
  for(int j=1; j<pos[i].sz; ++j){
    ll delta = pos[i].ptr[j] - x;
    if(type == 0)
      pbe(v, newevent(t - x, t + x, t + x + abs(delta) + delta, i));
    else
      pbe(v, newevent(t + x, t - x, t - x + abs(delta) - delta, i));
    t += abs(delta);
    x += delta;
  }
  if(type == 0)
    pbe(v, newevent(t - x, inf, inf, i));
  else
    pbe(v, newevent(t + x, inf, inf, i));
}
void solve_small(int a, int b, int cqid, int type){
  w.sz=0;
  add(a, &w, type);
  add(b, &w, type);
  qsort(w.ptr, w.sz, sizeof(event), cmpE);
  qid[a] = qid[b] = cqid;
  calc(a, &w);
}
void solve(int type){
  v.sz=0;
  for(int i=0; i<N; ++i)
    add(i, &v, type);
  qsort(v.ptr, v.sz, sizeof(event), cmpE);
  for(int i=0; i<N; ++i){
    if(pos[i].sz < MAGIC)
      for(int z=0;z<qs[i].sz;z++){pair query = qs[i].ptr[z];
        solve_small(i, query.first, query.second, type);
      }
    else
      solve_big(i);
  }
}
int main(){
  ids = newMap();
  scanf("%d %d", &N, &M);
  for(int i=0; i<N; ++i){
    scanf("%d", &K);
    for(int j=0; j<K; ++j){
      int x;
      scanf("%d", &x);
      pb(pos[i], x);
    }
  }
  for(int i=0; i<M; ++i){
    scanf("%d %d", &a, &b);
    --a; --b;
    if(mapHas(ids, Encode(a, b))){
      sol [i] = -1;
      fake[i] = mapGet(ids, Encode(a, b));
      continue;
    }
    mapPut(ids, Encode(a, b), i);
    mapPut(ids, Encode(b, a), i);
    if(pos[a].sz < pos[b].sz)
      swap(a, b);
    pbp(qs[a], newpair(b, i));
  }
  solve(0);
  solve(1);
  for(int i=0; i<M; ++i){
    if(sol[i] == -1)
      printf("%d\n", sol[fake[i]]);
    else
      printf("%d\n", sol[i]);
  }
  return 0;
}
