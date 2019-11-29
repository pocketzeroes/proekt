#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#include<ctype.h>
#define swap(a,b) do{ __typeof(a) tp; tp = a; a = b; b = tp; }while(0)
typedef long long ll;
inline ll min(ll a, ll b){return a<b?a:b;}
inline ll max(ll a, ll b){return a>b?a:b;}

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

enum{ BS = (1 << 20) + 5};
char Buffer[BS], *HD, *TL;
char Getchar (){
  if (HD == TL){
    TL = (HD = Buffer) + fread (Buffer, 1, BS, stdin);
  }
  return (HD == TL) ? EOF : *HD++;
}
int read (){
  int nm = 0, fh = 1;
  char cw = Getchar ();
  for (; !isdigit (cw); cw = Getchar ())
    if (cw == '-')
      fh = -fh;
  for (; isdigit (cw); cw = Getchar ())
    nm = nm * 10 + (cw - '0');
  return nm * fh;
}
int gc (){
  int cw = Getchar ();
  while (cw != 'R' && cw != 'O')
    cw = Getchar ();
  return cw == 'R';
}


mli*P;// map pair int
ll ans, F[300200], c[300200][2][2];
int n, m, A[300200], tot, cnt, top, K[300200], s[300200][2], pre[300200][2];
int fs[300200], kd[300200], nt[300200], tmp;
char C[20];

ll solve(int x){
  c[x][0][0] = min (c[x][0][0], c[x][0][1]),
  c[x][1][0] = min (c[x][1][0], c[x][1][1]);
  ll cst = c[x][0][0] + c[x][1][0];
  if (cst <= min (c[x][0][1], c[x][1][1]))
    return (ll) s[top][0] * c[x][0][0] + (ll) s[top][1] * c[x][1][0];
  if (c[x][0][1] > c[x][1][1]){
    swap (c[x][0][1], c[x][1][1]);
    swap (c[x][0][0], c[x][1][0]);
    for (int i = 1; i <= top; i++){
      swap (s[i][0], s[i][1]);
      K[i] ^= 1;
    }
  }
  for (int k = 0; k < 2; k++){
    for (int i = 1, now = 1; i <= top; i++){
      pre[i][k] = pre[i - 1][k];
      if (K[i] ^ k)
        continue;
      while (now < i || (now <= top && (K[now] ^ k ^ 1)))
        now++;
      if (now <= top)
        now++, pre[i][k]++;
    }
  }
  ll pos, rem = pre[top][0], t1, t2;
  t1 = s[top][0] - rem, t2 = s[top][1] - rem;
  if (cst <= c[x][1][1])
    return rem * c[x][0][1] + t1 * c[x][0][0] + t2 * c[x][1][0];
  for (pos = 1; pos <= top && s[pos][1] <= s[top][1] - rem; pos++);
  pos--;
  ll num = min (s[top][0] - rem, (ll) pre[pos][1]);
  t1 = s[top][0] - rem - num,
  t2 = s[top][1] - rem - num;
  return t1 * c[x][0][0] + t2 * c[x][1][0] + rem * c[x][0][1] + num * c[x][1][1];
}
int main(){
  P = newMap();
  n = read(),
  m = read(),
  memset(c, 0x3f, sizeof(c));
  for(int i = 1; i <= m; i++)
    A[i] = read();
  for(int T=read(); T; T--){
    int x = read(),
        y = read(),
        tg = 0, k, typ;
    typ = gc(),
    k   = read();
    if(x > y){
      swap(x, y);
      tg = 1;
    }
    if(!mapHas(P, Encode(x, y)))
      mapPut(P, Encode(x, y), ++cnt);
    c[mapGet(P, Encode(x, y))][tg][typ] = min(c[mapGet(P, Encode(x, y))][tg][typ], (ll)k);
  }
  for(int i = m; i >= 2; i--)
    nt[++tmp] = fs[mapGet(P,Encode(min(A[i-1], A[i]), max(A[i-1], A[i])))],
    fs[mapGet(P, Encode(min (A[i - 1], A[i]), max (A[i - 1], A[i])))] = tmp,
    kd[tmp] = A[i - 1] > A[i];
  for(int j = 1; j <= cnt; j++){
    if(!fs[j])
      continue;
    top = 0;
    for (int i = fs[j]; i; i = nt[i]){
      K[++top] = kd[i], s[top][0] = s[top - 1][0];
      s[top][1] = s[top - 1][1], s[top][kd[i]]++;
    }
    ans += solve (j);
  }
  printf ("%lld\n", ans);
  return 0;
}
