#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
ll solved;

#if 1 //queueue
typedef ll QueueElementType;
typedef struct Queue
{
  QueueElementType  *Elements;
  int  Front;
  int  Back;
  int  NumElements;
  int  Capacity;
} Queue;
Queue *newQueue();
void   DeleteQueue(Queue *Q);
int    empty(Queue *Q);
int    push(Queue *Q, QueueElementType e);
QueueElementType pop(Queue *Q);
int    isElementInQueue(Queue *Q, QueueElementType e);

Queue *newQueue()
{
  int N=1024;
  Queue *Q;
  if (N < 1)
  {
    printf("\n**Error in newQueue invalid parameter N (%d)\n\n", N);
    return NULL;
  }
  Q = (Queue *)malloc(sizeof(Queue));
  if (Q == NULL)
  {
    printf("\n**Error in newQueue: malloc failed to allocate\n\n");
    exit(-1);
  }
  Q->Elements = (QueueElementType *)malloc(N * sizeof(QueueElementType));
  if (Q->Elements == NULL)
  {
    printf("\n**Error in newQueue: malloc failed to allocate\n\n");
    exit(-1);
  }
  Q->Front = 0;
  Q->Back = -1;
  Q->NumElements = 0;
  Q->Capacity = N;
  return Q;
}
void DeleteQueue(Queue *Q)
{
  free(Q->Elements);
  free(Q);
}
int empty(Queue *Q)
{
  return Q->NumElements == 0;
}
int size(Queue *Q)
{
  return Q->NumElements;
}
int push(Queue *Q, QueueElementType e)
{
  if (Q->NumElements == Q->Capacity)
  {
    int N = 2 * Q->Capacity;
    QueueElementType *newE = (QueueElementType *)malloc(N * sizeof(QueueElementType));
    if (newE == NULL)
    {
      printf("\n**Error in push: malloc failed to allocate\n\n");
      exit(-1);
    }
    int  i = Q->Front;
    int  j = 0;
    int  n;
    for (n = 0; n < Q->NumElements; ++n)
    {
      newE[j] = Q->Elements[i];
      ++j;
      ++i;
      if (i >= Q->Capacity)
        i = 0;
    }
    free(Q->Elements);
    Q->Front = 0;
    Q->Back = j - 1;
    Q->Elements = newE;
    Q->Capacity = N;
  }
  Q->Back++;
  if (Q->Back >= Q->Capacity)
    Q->Back = 0;
  Q->Elements[Q->Back] = e;
  Q->NumElements++;
  return 1;
}
QueueElementType pop(Queue *Q)
{
  if (empty(Q))
  {
    printf("\n**Error in pop: Q is empty?!\n\n");
    exit(-1);
  }
  QueueElementType e = Q->Elements[Q->Front];
  Q->Front++;
  if (Q->Front >= Q->Capacity)
    Q->Front = 0;
  Q->NumElements--;
  return e;
}
QueueElementType front(Queue *Q)
{
  if (empty(Q))
  {
    printf("\n**Error in pop: Q is empty?!\n\n");
    exit(-1);
  }
  QueueElementType e = Q->Elements[Q->Front];
  return e;
}
int isElementInQueue(Queue *Q, QueueElementType e)
{
  int  i = Q->Front;
  int  count;
  for (count = 0; count < Q->NumElements; ++count)
  {
    if (Q->Elements[i] == e)
      return 1;
    ++i;
    if (i == Q->Capacity)
      i = 0;
  }
  return 0;
}
#endif

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

mli*distforward;
mli*distbackward;

void setval(ll*state, ll x, ll y, ll val){
    ll shift1 = ((4 * y) + x) * 2;
   *state &= ~((ll)3 << shift1);
   *state |= (val << shift1);
}
ll getval(ll state, ll x, ll y){
    state >>= ((4 * y) + x) * 2;
    return state % 4;
}
ll swipeu(ll b, int col){
    int temp =        getval(b, 0, col);
    setval(&b, 0, col, getval(b, 1, col));
    setval(&b, 1, col, getval(b, 2, col));
    setval(&b, 2, col, getval(b, 3, col));
    setval(&b, 3, col, temp);
    return b;
}
ll swiped(ll b, int col){
    int temp =        getval(b, 3, col);
    setval(&b, 3, col, getval(b, 2, col));
    setval(&b, 2, col, getval(b, 1, col));
    setval(&b, 1, col, getval(b, 0, col));
    setval(&b, 0, col, temp);
    return b;
}
ll swipel(ll b, int col){
    int temp =        getval(b, col, 0);
    setval(&b, col, 0, getval(b, col, 1));
    setval(&b, col, 1, getval(b, col, 2));
    setval(&b, col, 2, getval(b, col, 3));
    setval(&b, col, 3, temp);
    return b;
}
ll swiper(ll b, int col){
    int temp =        getval(b, col, 3);
    setval(&b, col, 3, getval(b, col, 2));
    setval(&b, col, 2, getval(b, col, 1));
    setval(&b, col, 1, getval(b, col, 0));
    setval(&b, col, 0, temp);
    return b;
}
void getstates(ll*boards, ll curr){
    int bsz = 0;
    for(int i=0; i<4; i++){
        boards[bsz++] = swipeu(curr, i);
        boards[bsz++] = swiped(curr, i);
        boards[bsz++] = swipel(curr, i);
        boards[bsz++] = swiper(curr, i);
    }
}
int searchforward(ll start){
    Queue*q = newQueue();
    mapPut(distforward, start, 0);
    push(q, start);
    while(!empty(q)){
        ll curr = front(q); pop(q);
        if(curr == solved)
            return mapGet(distforward, curr);
        ll boards[16];
        getstates(boards, curr);
        for(int z=0;z<16;z++){ll next = boards[z];
            if(!mapHas(distforward, next)){
                mapPut(distforward, next, mapGet(distforward, curr) + 1);
                if(mapGet(distforward, next) < 6)
                    push(q, next);
            }
        }
    }
    return -1;
}
int searchbackward(){
    Queue*q = newQueue();
    mapPut(distbackward, solved, 0);
    push(q, solved);
    while(!empty(q)){
        ll curr = front(q); pop(q);
        if(mapHas(distforward, curr))
            return mapGet(distforward, curr) + mapGet(distbackward, curr);
        ll boards[16];
        getstates(boards, curr);
        for(int z=0;z<16;z++){ll next = boards[z];
            if(!mapHas(distbackward, next)){
                mapPut(distbackward, next, mapGet(distbackward, curr)+1);
                push(q, next);
            }
        }
    }
    return -1;
}
int main(){
    distforward  = newMap();
    distbackward = newMap();
    ll b = 0;
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            char c=getchar();
            int valhere;
            if(c == 'R') valhere = 0;
            if(c == 'G') valhere = 1;
            if(c == 'B') valhere = 2;
            if(c == 'Y') valhere = 3;
            setval(&b, i, j, valhere);
        }
        getchar();
    }
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            setval(&solved, j, i, j);
    if(b == solved)
        return puts("0")*0;
    int ans = searchforward(b);
    if(ans == -1)
        printf("%d\n", searchbackward());
    else
        printf("%d\n", ans);
    return 0;
}
