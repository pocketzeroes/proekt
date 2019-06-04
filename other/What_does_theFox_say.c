#define _GNU_SOURCE 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#include<stdint.h>

char*concatc(char*a, char b){
  char*ptr=NULL;
  asprintf(&ptr, "%s%c",a,b);
  return ptr;
}

#if 1 // set str
static const size_t INITIAL_CAPACITY = 16;
static const size_t MAXIMUM_CAPACITY = (1U << 31);
static const float  LOAD_FACTOR      = 0.75;

#ifndef HASHMAP_H
#define HASHMAP_H
#include <stdlib.h>
typedef struct HashMap HashMap;
HashMap *newHashMap(void);
int mapContainsKey(HashMap *karta, const char key[]);
void hashMapRemove(HashMap *karta, const char key[], const void **valPtr);
size_t mapSize(const HashMap *karta);
int hashMapIsEmpty(const HashMap *karta);
void hashMapClear(HashMap *karta);
void hashMapDestroy(HashMap *karta);
#endif

void DUMMYfree(const void*pp){
    ;
}

typedef struct HashMapEntry {
  char                *key;
  int                  value;
  struct HashMapEntry *next;
  uint32_t             hash;
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
static size_t indexFor(uint32_t hash, size_t length) {
  return hash & (length - 1);
}
static int isHit(HashMapEntry *e, const char key[], uint32_t hash) {
  return (e->hash == hash
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
  uint32_t hash  = doHash(key);
  size_t   gIndex = indexFor(hash, karta->capacity);
  for (e = karta->table[gIndex]; e != NULL; e = e->next) {
    if (isHit(e, key, hash) == 0)
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
  e->hash = hash;
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
      gIndex   = indexFor(e->hash, newCapacity);
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
  uint32_t      hash  = doHash(key);
  size_t        gIndex = indexFor(hash, karta->capacity);
  for (e = karta->table[gIndex]; e != NULL; e = e->next) {
    if (isHit(e, key, hash))
      return e->value;
  }
  return 0;
}
int mapContainsKey(HashMap *karta, const char key[]) {
  HashMapEntry *e;
  uint32_t      hash  = doHash(key);
  size_t        gIndex = indexFor(hash, karta->capacity);
  for (e = karta->table[gIndex]; e != NULL; e = e->next) {
    if (isHit(e, key, hash))
      return 1;
  }
  return 0;
}
void hashMapRemove(HashMap *karta, const char key[], const void **valPtr) {
  uint32_t      hash  = doHash(key);
  size_t        gIndex = indexFor(hash, karta->capacity);
  HashMapEntry *prev  = karta->table[gIndex];
  HashMapEntry *e     = prev;
  while (e != NULL) {
    HashMapEntry *next = e->next;
    if (isHit(e, key, hash)) {
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
void hashMapClear(HashMap *karta) {
  size_t i;
  for (i = 0; i < karta->capacity; ++i) {
    HashMapEntry *e;
    HashMapEntry *next;
    for (e = karta->table[i]; e != NULL; e = next) {
//    printf("%s %d\n", e->key, e->value);
      free(e->key);
      next = e->next;
      free(e);
    }
    karta->table[i] = NULL;
  }
}
void hashMapDump(HashMap*karta){
  size_t i;
  for (i = 0; i < karta->capacity; ++i) {
    HashMapEntry *e;
    HashMapEntry *next;
    for (e = karta->table[i]; e != NULL; e = next) {
      printf("%s %d\n", e->key, e->value);
      next = e->next;
    }
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


void hashMapDestroy(HashMap *karta) {
  if (karta == NULL)
    return;
  hashMapClear(karta);
  free(karta->table);
  free(karta);
}

#endif//////////////////////////////
 
char a[2500],s[2500];
HashMap*m;
char*voice;
 
int main(){
    m = newHashMap();
    int t;
    scanf("%d", &t);
    getchar();
    while(t--){
        gets(s);
        hashMapClear(m);
        while(1){
            gets(a);
            if(!strcmp(a, "what does the fox say?"))
                break;
            voice = strdup("");
            for(int i = strlen(a)-1; a[i]!=' '; i--)
                voice = concatc(voice, a[i]);
            char tmp;
            for(int i = 0,len = strlen(voice); i<=(len-1)/2; i++){
                tmp = voice[i]; voice[i] = voice[len-1-i]; voice[len-1-i] = tmp;
            }
            mapPut(m, voice, 55);
        }
        s[strlen(s)] = ' ';
        s[strlen(s)] = 0;
        voice = strdup("");
        for(int i = 0,len = strlen(s); i<len; i++){
            if(s[i]==' '){
                if(!mapContainsKey(m, voice))
                    printf("%s ", voice);
                voice = strdup("");
            }
            else
                voice = concatc(voice, s[i]);
        }
        puts("");
    }
    return 0;
}
