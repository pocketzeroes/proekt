#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
#define swap(a,b) do{ __typeof(a) tp; tp = a; a = b; b = tp; }while(0)
#define EP 1e-10
typedef long long ll;
typedef double dbl;

char buff[100000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}
double**newmat(int x, int y){
  double**rv = calloc(x, sizeof(double*));
  for(int i=0; i<x; i++)
    rv[i] = calloc(y, sizeof(double));
  return rv;
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
///////////////////////////

dbl GaussJordan(double**A){
    ll m = 10,
       n = 20;
    ll det= 1;
    ll pj = 0;
    for(ll k=0; k<m; ++k){
        ll pi = k;
        while(pj < n){
            for(ll i = k; i < m; ++i)
                if(fabs(A[i][pj]) > fabs(A[pi][pj]))
                    pi = i;
            if(fabs(A[pi][pj]) > EP){
                if(pi != k){
                    swap(A[pi], A[k]);
                    pi = k;
                    det *= -1;
                }
                break;
            }
            for(ll i = k; i < m; ++i)
                A[i][pj] = 0;
            ++pj;
        }
        if(pj == n){
            det = 0;
            break;
        }
        dbl s = 1.0/A[pi][pj];
        for(ll j = pj; j < n; ++j)
            A[pi][j] *= s;
        det /= s;
        for(ll i = 0; i < m; ++i){
            if(i != pi){
                dbl a = A[i][pj];
                for (ll j = pj; j < n; ++j)
                    A[i][j] -= a*A[pi][j];
            }
        }
        ++pj;
    }
    return det;
}
msi*mp;//msl

ll ele_to_id(char*ele){
    if(!mapHas(mp, ele)){
        ll count = mapSize(mp);
        mapPut(mp, ele, count);
    }
    return mapGet(mp, ele);
}
int main(){
    mp = newMap();
    dbl**A = newmat(10, 20);//of dbl
    char sign;
    ll n_molecules = 0;
    
    while(1){
        sign = getchar();
        if(sign == '0')
            break;
        ll one, N;
        scanf("%lld %lld", &one, &N);
        ll sign_int = sign == '+' ? 1 : -1;
        for(ll i=0; i<N; ++i){
            char*element = getstr();
            ll count;
            scanf("%lld", &count);
            ll element_id = ele_to_id(element);
            A[element_id][n_molecules] += sign_int * count;
        }
        ++n_molecules;
        getchar();
    }
    ll n_elements = mapSize(mp);
    GaussJordan(A);
    double solution[n_molecules]; clr(solution);
    for(ll i=0; i<n_elements; ++i){
        ll molecule = n_molecules;
        for(ll j=0; j<n_molecules; ++j){
            if(fabs(A[i][j]-1) < EP){
                molecule = j;
                break;
            }
        }
        for(ll j=molecule+1; j<n_molecules; ++j)
            solution[molecule] -= A[i][j];
    }
    for(ll i=0; i<n_molecules; ++i)
        if(solution[i] == 0)
           solution[i] =  1;
    for(ll scale=1; scale<=1000; ++scale){
        bool success = true;
        double solution_new[n_molecules]; memcpy(solution_new, solution, sizeof(solution));
        for(ll i=0; i<n_molecules; ++i){
            solution_new[i] *= scale;
            if(fabs((ll)(solution_new[i]+EP) - solution_new[i]) > EP)
                success = false;
        }
        if(success){
            printf("%.0lf", solution_new[0]);
            for(ll i=1; i<n_molecules; ++i)
                printf(" %.0lf", solution_new[i]);
            puts("");
            break;
        }
    }
    return 0;
}
