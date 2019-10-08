#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;

int in_nextInt(){
  int xx;
  scanf("%d", &xx);
  return xx;
}
char buff[100000];
char*getstr(){
  int rv = scanf("%s", &buff);
  return strdup(buff);
}

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

#define pbl(zpv, zvv) zpv.ptr = pushbackL(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
ll*pushbackL(ll*array, int*size, ll value){
  ll*output = resizeArray(array, ll, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
  ll*ptr;
  int sz;
}vecl;
vecl newVecL(){
  vecl rez;
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
}

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


int DX[4] = {0,0,1,-1};
int DY[4] = {1,-1,0,0};
int N = 7;
mli*map; // mli


ll convert(char*line){
    ll res = 0;
    for(int i=0; i<N; i++)
        if(line[i] == 'X')
            res |= (1LL << i);
    return res;
}
vecl getNext(ll mask){
    vecl res = newVecL();
    for(int i=0; i<N; i++){
        for(int j=0; j<4; j++){
            int x = i;
            if(j == 2)
                x = 0;
            if(j == 3)
                x = N-1;
            int y = i;
            if(j == 0)
                y = 0;
            if(j == 1)
                y = N-1;
            if((mask & (1LL << (N*x+y))) != 0)
                continue;
            int k = 0;
            while(k < N && (mask & (1LL << (N*(x+k*DX[j]) +(y+k*DY[j])))) == 0)
                k++;
            int numZ = k;
            while(k < N && (mask & (1LL << (N*(x+k*DX[j]) +(y+k*DY[j])))) != 0)
                k++;
            int numO = k-numZ;
            if(numO < 2)
                continue;
            ll nextMBase = mask;
            ll full = (1LL << (N*N)) - 1;
            for(int z=0; z<k-1; z++){
                ll sub = (1LL << (N*(x+z*DX[j]) +(y+z*DY[j])));
                nextMBase = (nextMBase) & (full-sub);
            }
            for(int cube=1; cube<numO; cube++){
                int noMove  = numO-1-cube;
                ll mymask = nextMBase;
                for(int z=0; z<cube; z++)
                    mymask |= (1LL << (N*(x+z*DX[j]) +(y+z*DY[j])));
                for(int z = k-2,w=0; w<noMove; z--,w++)
                    mymask |= (1LL << (N*(x+z*DX[j]) +(y+z*DY[j])));
                pbl(res, mymask);
            }
        }
    }
    return res;
}
void precomp(){
    map = newMap();//mli
    Queue*q = newQueue();//of ll
    for(int i=0; i<N-2; i++){
        for(int j=0; j<N-2; j++){
            ll onerow = (1LL << j)  + (1LL << (j+1)) + (1LL << (j+2));
            ll tot = (onerow << (N*i)) + (onerow << (N*(i+1))) + (onerow << (N*(i+2)));
            mapPut(map, tot, 0);
            push(q, tot);
        }
    }
    while(!empty(q)){
        ll cur = pop(q);
        int dist = mapGet(map, cur);
        vecl next = getNext(cur);
        for(int z=0; z<next.sz; z++){ll item = next.ptr[z];
            if(mapHas(map, item))
                continue;
            mapPut(map, item, dist+1);
            push(q, item);
        }
    }
}
int main(){
    precomp();
    int nC = in_nextInt();
    for (int loop=0; loop<nC; loop++){
        ll mask = 0;
        for(int i=0; i<N; i++){
            char*nxt=getstr();
            mask |= (convert(nxt) << (N*i));
        }
        if(mapHas(map, mask))
            printf("%d\n", mapGet(map, mask));
        else
            puts("-1");
    }
    return 0;
}
