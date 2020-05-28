#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)

void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
typedef long long ll;
ll gcd(ll x, ll y){
  return y?gcd(y,x%y):x;
}

typedef struct{
  ll x, y;
}P;

P newpt(ll a, ll b){
  return(P){a,b};
}
P opsub(P t, P b){
  return newpt(t.x-b.x, t.y-b.y);
}
P normalize(P p){
  if(p.x < 0){
    p.x *= -1;
    p.y *= -1;
  }
  if(p.x == 0 && p.y < 0)
    p.y *= -1;
  if(p.x == 0)
    p.y = 1;
  if(p.y == 0)
    p.x = 1;
  if(p.x != 0 && p.y != 0){
    ll g = gcd(llabs(p.x), llabs(p.y));
    p.x /= g;
    p.y /= g;
  }
  return p;
}


typedef struct{
  int first, second;
}pair;
pair newpair(int a, int b){
  return(pair){a,b};
}
#define pbp(zpv, zvv) zpv.ptr = pushbackP(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
pair*pushbackP(pair*array, int*size, pair val){
  pair*output = resizeArray(array, pair, *size + 1);
  output[(*size)++] = val;
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
#if 1 ////////////////mpv
static const size_t INITIAL_CAPACITY = 16;
static const size_t MAXIMUM_CAPACITY = (1U << 31);
static const float  LOAD_FACTOR      = 0.75;

typedef long long ll;

typedef struct{
  ll first, second;
}pll;
pll newpll(ll a, ll b){
  return(pll){a,b};
}
int cmpP(pll a, pll b){
  if(a.first  != b.first) return(a.first  < b.first )?-1:1;
  if(a.second != b.second)return(a.second < b.second)?-1:1;
  return 0;
}
#include<stdint.h>

#ifndef HA6MAP_H
#define HA6MAP_H
typedef struct hmEntry{
  pll           key;
  vecp          value;
  struct hmEntry*next;
  uint32_t       ha6;
}hmEntry;

typedef struct mpv{
  hmEntry**table;
  size_t   capacity;
  size_t   size;
  size_t   threshold;
}mpv;

mpv*newMpv();
bool   mpvHas(mpv*karta, pll key);
void   mpvDel(mpv*karta, pll key);
size_t mpvSize(const mpv*karta);
bool   mpvEmpty(const mpv*karta);
void   mpvClear(mpv*karta);
void   mpvDestroy(mpv*karta);
#endif





static void set_Table(mpv*karta, hmEntry**table, size_t capacity){
  karta->table     = table;
  karta->capacity  = capacity;
  karta->threshold = (size_t) (capacity * LOAD_FACTOR);
}
static uint32_t do_Hash(pll key){
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
bool is_Hit(hmEntry *e, pll key, uint32_t ha6){
  return(e->ha6 == ha6
          &&cmpP(e->key, key)==0);
}
int update_Value(mpv*karta, hmEntry*e, vecp newVal, const void**oldValPtr){
  e->value = newVal;
  return 1;
}
mpv*newMpv(){
  hmEntry **table;
  mpv       *karta = malloc(sizeof(*karta));
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
int  mpvPut(mpv*karta, pll key, vecp value){
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
vecp mpvGet(mpv*karta, pll key){
  hmEntry *e;
  uint32_t      ha6  = do_Hash(key);
  size_t        gIndex = index_For(ha6, karta->capacity);
  for(e = karta->table[gIndex]; e != NULL; e = e->next) {
    if(is_Hit(e, key, ha6))
      return e->value;
  }
  return(vecp){NULL,0};
}
bool mpvHas(mpv*karta, pll key){
  hmEntry *e;
  uint32_t      ha6  = do_Hash(key);
  size_t        gIndex = index_For(ha6, karta->capacity);
  for (e = karta->table[gIndex]; e != NULL; e = e->next) {
    if (is_Hit(e, key, ha6))
      return 1;
  }
  return 0;
}
void mpvDel(mpv*karta, pll key){
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
size_t mpvSize(const mpv*karta){
  return karta->size;
}
bool mpvEmpty(const mpv*karta){
  return (karta->size == 0);
}
void mpvClear(mpv*karta){
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
#define mapForEach(mm, fnc)                            \
  do{                                                  \
    for(int i=0; i<mm->capacity; ++i){                 \
      hmEntry*e;                                       \
      hmEntry*next;                                    \
      for(e=mm->table[i]; e!=NULL; e=next){            \
          kvp rez;                                     \
          rez.key=e->key;                              \
          rez.val=e->value;                            \
          fnc(&rez);                                   \
          next = e->next;                              \
      }                                                \
    }                                                  \
  }while(0);
  
typedef struct{
  pll  key;
  vecp val;
}kvp;

void mpvDestroy(mpv*karta){
  if (karta == NULL)
    return;
  mpvClear(karta);
  free(karta->table);
  free(karta);
}
#endif






void test_case(){
  int n;
  scanf("%d", &n);
  P points[n];
  for(int i=0; i<n; ++i)
    scanf("%lld %lld", &points[i].x, &points[i].y);
  mpv*m = newMpv();
  for(int i=0; i<n; ++i){
    for(int j=i+1; j<n; ++j){
      P dir = opsub(points[i], points[j]);
      dir = normalize(dir);
      pll dxy = newpll(dir.x, dir.y);
      if(!mpvHas(m, dxy))
        mpvPut(m, dxy, newVecP());
      vecp vp = mpvGet(m, dxy);
      pbp(vp, newpair(i, j));
      mpvPut(m, dxy, vp);
    }
  }
  int answer = fmin(n, 2);
  void doit(kvp*it){
    vecp pairs = it->val;
    int group[n]; fill(group, n, n);
    for(int z=0;z<pairs.sz;z++){pair edge=pairs.ptr[z];
      int a = edge.first;
      int b = edge.second;
      group[a] = fmin(group[a], fmin(a, b));
      group[b] = fmin(group[b], fmin(a, b));
    }
    int cnt[n]; clr(cnt);
    for(int z=0;z<n;z++){int x=group[z];
      if(x<n)
        cnt[x]++;
    }
    int total = 0;
    int odd   = 0;
    for(int z=0;z<n;z++){int x=cnt[z];
      total += x/2*2;
      if(x%2)
        odd++;
    }
    total += odd/2*2;
    total  = fmin(n, total + 2);
    answer = fmax(answer, total);
  }
  mapForEach(m, doit);
  printf("%d\n", answer);
}
int main(){
  int T;
  scanf("%d", &T);
  for(int nr=1; nr<=T; ++nr){
    printf("Case #%d: ", nr);
    test_case();
  }
  return 0;
}
