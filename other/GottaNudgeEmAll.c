#include<stdio.h>   // gotta nudge
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;

char buff[1000000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}

typedef struct{
  int first;
  ll  second;
}pair;
pair newpair(int a, ll b){
  return(pair){a,b};
}
typedef struct{
  ll   first;
  pair second;
}trip;
trip newtrip(ll a, pair b){
  return(trip){a,b};
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
typedef struct HashMap HashMap;
HashMap *newHashMap(void);
int mapHas(HashMap *karta, const char key[]);
void hashMapRemove(HashMap *karta, const char key[], const void **valPtr);
size_t mapSize(const HashMap *karta);
int hashMapIsEmpty(const HashMap *karta);
void mapClear(HashMap *karta);
void hashMapDestroy(HashMap *karta);
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
struct HashMap {
  HashMapEntry **table;
  size_t         capacity;
  size_t         size;
  size_t         threshold;
};
static void setTable(HashMap *karta, HashMapEntry **table, size_t capacity) {
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
static int updateValue(HashMap *karta, HashMapEntry *e, int newVal, const void **oldValPtr) {
  copyOrFree( e->value, oldValPtr);
  e->value = newVal;
  return 1;
}
HashMap *newHashMap(void ) {
  HashMapEntry **table;
  HashMap       *karta = malloc(sizeof(*karta));
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
int mapPut(HashMap *karta, const char key[], int value){
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
int mapGet(HashMap *karta, const char key[]) {
  HashMapEntry *e;
  uint32_t      ha6  = doHash(key);
  size_t        gIndex = indexFor(ha6, karta->capacity);
  for (e = karta->table[gIndex]; e != NULL; e = e->next) {
    if (isHit(e, key, ha6))
      return e->value;
  }
  return NULL;
}
int mapHas(HashMap *karta, const char key[]) {
  HashMapEntry *e;
  uint32_t      ha6  = doHash(key);
  size_t        gIndex = indexFor(ha6, karta->capacity);
  for (e = karta->table[gIndex]; e != NULL; e = e->next) {
    if (isHit(e, key, ha6))
      return 1;
  }
  return 0;
}
void hashMapRemove(HashMap *karta, const char key[], const void **valPtr) {
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
size_t mapSize(const HashMap *karta) {
  return karta->size;
}
int hashMapIsEmpty(const HashMap *karta) {
  return (karta->size == 0);
}
void mapClear(HashMap *karta) {
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
void hashMapDestroy(HashMap *karta) {
  if (karta == NULL)
    return;
  mapClear(karta);
  free(karta->table);
  free(karta);
}
#endif

enum{ MAXN = 200005};
enum{ MAXP = 400005};
typedef struct{
  int l, r, ls, rs;
  int cnt;
  ll single, val, xp;
}node;

int  r, w;
HashMap*names;
int  f     [MAXN];
int  ford  [MAXN];
int  costs [MAXN];
int  fstart[MAXN];
int  t     [MAXP];
int  id    [MAXP];
node a     [MAXN];
int  roots [MAXN];
int  ans   [MAXN];

void initTree(int sz, int offset){
  int root = w;
  a[w].l = 0;
  a[w].r = sz-1;
  a[w].ls = -1;
  a[w].rs = -1;
  a[w].cnt = 0;
  a[w].val = 0;
  w++;
  while (w > r) {
    if (a[r].r > a[r].l) {
      a[w].l = a[r].l;
      a[w].r = (a[r].l + a[r].r) / 2;
      a[w].ls = -1;
      a[w].rs = -1;
      a[w].cnt = 0;
      a[w].val = 0;
      a[r].ls = w;
      w++;
      a[w].l = a[w-1].r + 1;
      a[w].r = a[r].r;
      a[w].ls = -1;
      a[w].rs = -1;
      a[w].cnt = 0;
      a[w].val = 0;
      a[r].rs = w;
      w++;
    }
    r++;
  }
  for (int i = w-1; i >= root; i--) {
    if (a[i].l == a[i].r) {
      a[i].single = costs[offset + a[i].l];
    } else {
      a[i].single = a[a[i].ls].single + a[a[i].rs].single;
    }
  }
}
void add(int point, int where){
  if (a[point].l == a[point].r) {
    a[point].cnt++;
    a[point].val = (ll)a[point].cnt * a[point].single;
    a[point].xp = (ll)a[point].cnt;
  } else {
    if (a[a[point].ls].r >= where) {
      add(a[point].ls, where);
    } else {
      add(a[point].rs, where);
    }
    a[point].cnt = a[a[point].ls].cnt + a[a[point].rs].cnt;
    a[point].val = a[a[point].ls].val + (ll)a[a[point].ls].cnt * a[a[point].rs].single + a[a[point].rs].val;
    a[point].xp = a[a[point].ls].xp + (ll)a[a[point].ls].cnt * (ll)(a[a[point].rs].r - a[a[point].rs].l + 1) + a[a[point].rs].xp;
  }
}
trip get(int point, int L, int R, int carry){
  if(R < L)
    return newtrip(0, newpair(0, 0));
  if ((a[point].l >= L) && (a[point].r <= R))
    return newtrip(a[point].val + (ll)carry * a[point].single, newpair(a[point].cnt, a[point].xp + (ll)carry * (ll)(a[point].r - a[point].l + 1)));
  else{
    trip left = newtrip(0, newpair(0, 0));
    if (a[a[point].ls].r >= L)
      left = get(a[point].ls, L, R, carry);
    trip right = newtrip(0, newpair(0, 0));
    if (a[a[point].rs].l <= R)
      right = get(a[point].rs, L, R, carry + left.second.first);
    return newtrip(left.first + right.first, newpair(left.second.first + right.second.first, left.second.second + right.second.second));
  }
}
int recalc(int family, int forder){
  add(roots[family], forder);
  ll candies = 4 * a[roots[family]].cnt - 1;
  int L = 0;
  int R = fstart[family+1] - fstart[family] - 1;
  int C;
  trip val;
  while(R > L){
    C = (L+R+1)/2;
    val = get(roots[family], 0, C-1, 0);
    if (val.first <= candies)
      L = C;
    else
      R = C-1;
  }
  val = get(roots[family], 0, L-1, 0);
  candies -= val.first;
  ll xp = val.second.second;
  int cost = costs[fstart[family] + L];
  if (cost)
    xp += (candies / cost);
  return (int)xp * 1000;
}
int main(){
  names = newHashMap();
  r = w = 0;
  int F;
  int N = 0;
  scanf("%d", &F);
  for(int iF = 0; iF < F; iF++){
    fstart[iF] = N;
    int FC;
    scanf("%d", &FC);
    char*nm = getstr();
    mapPut(names, nm, N);
    f[N] = iF;
    ford[N] = 0;
    costs[N] = 0;
    N++;
    for(int i = 1; i < FC; i++){
      int c;
      scanf("%d", &c);
      nm = getstr();
      costs[N-1] = c;
      mapPut(names, nm, N);
      f[N] = iF;
      ford[N] = i;
      costs[N] = 0;
      N++;
    }
    roots[iF] = w;
    initTree(FC, fstart[iF]);
    ans[iF] = 0;
  }
  fstart[F] = N;
  int P;
  scanf("%d", &P);
  for(int i=0; i<P; i++){
    char* nm;
    scanf("%d", &t[i]);
    nm=getstr();
    id[i] = mapGet(names, nm);
  }
  int res = 0;
  int cur = 0;
  int prev = 0;
  for (int i = 0; i < P; i++){
    while (t[prev] + 1800 <= t[i])
      prev++;
    int family = f[id[i]];
    int forder = ford[id[i]];
    cur -= ans[family];
    ans[family] = recalc(family, forder);
    cur += ans[family];
    res = fmax(res, cur + (i - prev + 1) * 100);
  }
  printf("%d\n", res + P * 100);
  return 0;
}
