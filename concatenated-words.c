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
HashMap *hashMapCreate(void (*freeFunc)(const void *));
int hashMapPut(HashMap *map, const char key[], const void * const value, const void **oldValPtr);
const void *hashMapGet(HashMap *map, const char key[]);
int hashMapContainsKey(HashMap *map, const char key[]);
void hashMapRemove(HashMap *map, const char key[], const void **valPtr);
size_t hashMapSize(const HashMap *map);
int hashMapIsEmpty(const HashMap *map);
void hashMapClear(HashMap *map);
void hashMapDestroy(HashMap *map);
#endif

void DUMMYfree(const void*pp){
    ;
}

typedef struct HashMapEntry {
  char                *key;
  const void          *value;
  struct HashMapEntry *next;
  uint32_t             hash;
} HashMapEntry;
struct HashMap {
  HashMapEntry **table;
  size_t         capacity;
  size_t         size;
  size_t         threshold;
  void         (*freeFunc)(const void *);
};
static void setTable(HashMap *map, HashMapEntry **table, size_t capacity) {
  map->table     = table;
  map->capacity  = capacity;
  map->threshold = (size_t) (capacity * LOAD_FACTOR);
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
static void copyOrFree(void (*freeFunc)(const void *), const void *value, const void **valPtr) {
  if (valPtr != NULL)
    *valPtr = value;
  else
    freeFunc(value);
}
static int updateValue(HashMap *map, HashMapEntry *e, const void *newVal, const void **oldValPtr) {
  copyOrFree(map->freeFunc, e->value, oldValPtr);
  e->value = newVal;
  return 1;
}
HashMap *hashMapCreate(void (*freeFunc)(const void *)) {
  HashMapEntry **table;
  HashMap       *map = malloc(sizeof(*map));
  if (map == NULL)
    return NULL;
  table = calloc(INITIAL_CAPACITY, sizeof(*map->table));
  if (table == NULL) {
    free(map);
    return NULL;
  }
  setTable(map, table, INITIAL_CAPACITY);
  map->size = 0;
  if(freeFunc)
    map->freeFunc = freeFunc;
  else
    map->freeFunc = DUMMYfree;
  return map;
}
int hashMapPut(HashMap *map, const char key[], const void * const value, const void **oldValPtr) {
  HashMapEntry  *e;
  size_t         newCapacity;
  HashMapEntry **newTable;
  size_t         i;
  /* If an entry with the same key exists, update it */
  uint32_t hash  = doHash(key);
  size_t   index = indexFor(hash, map->capacity);
  for (e = map->table[index]; e != NULL; e = e->next) {
    if (isHit(e, key, hash) == 0)
      continue;
    return updateValue(map, e, value, oldValPtr);
  }
  /* Create a new entry */
  e = calloc(1, sizeof(HashMapEntry)); /* Must be zeroed */
  if (e == NULL)
    return 0;
  /* Copy key and value into the entry */
  if (key != NULL) {
    e->key = strdup(key);
    if (e->key == NULL) {
      free(e);
      return 0;
    }
  }
  if (updateValue(map, e, value, oldValPtr) == 0) {
    free(e->key);
    free(e);
    return 0;
  }
  /* Insert entry into the table */
  e->hash = hash;
  e->next = map->table[index];
  map->table[index] = e;
  if (map->size++ < map->threshold)
    return 1;
  /* If the size exceeds the threshold, double the table's capacity */
  newCapacity = 2 * map->capacity;
  if (map->capacity == MAXIMUM_CAPACITY) {
    map->threshold = UINT_MAX;
    return 1;
  }
  newTable = calloc(newCapacity, sizeof(*newTable));
  if (newTable == NULL)
    return 0;
  /* Copy entries from the old table into the new one */
  for (i = 0; i < map->capacity; ++i) {
    HashMapEntry *next;
    for (e = map->table[i]; e != NULL; e = next) {
      index   = indexFor(e->hash, newCapacity);
      next    = e->next;
      e->next = newTable[index];
      newTable[index] = e;
    }
  }
  /* Release the old table and set the new one */
  free(map->table);
  setTable(map, newTable, newCapacity);
  return 1;
}
const void *hashMapGet(HashMap *map, const char key[]) {
  HashMapEntry *e;
  uint32_t      hash  = doHash(key);
  size_t        index = indexFor(hash, map->capacity);
  for (e = map->table[index]; e != NULL; e = e->next) {
    if (isHit(e, key, hash))
      return e->value;
  }
  return NULL;
}
int hashMapContainsKey(HashMap *map, const char key[]) {
  HashMapEntry *e;
  uint32_t      hash  = doHash(key);
  size_t        index = indexFor(hash, map->capacity);
  for (e = map->table[index]; e != NULL; e = e->next) {
    if (isHit(e, key, hash))
      return 1;
  }
  return 0;
}
void hashMapRemove(HashMap *map, const char key[], const void **valPtr) {
  uint32_t      hash  = doHash(key);
  size_t        index = indexFor(hash, map->capacity);
  HashMapEntry *prev  = map->table[index];
  HashMapEntry *e     = prev;
  while (e != NULL) {
    HashMapEntry *next = e->next;
    if (isHit(e, key, hash)) {
      map->size--;
      if (prev == e)
        map->table[index] = next;
      else
        prev->next = next;
      break;
    }
    prev = e;
    e    = next;
  }
  if (e == NULL) {
    copyOrFree(map->freeFunc, NULL, valPtr);
    return;
  }
  free(e->key);
  copyOrFree(map->freeFunc, e->value, valPtr);
  free(e);
}
size_t hashMapSize(const HashMap *map) {
  return map->size;
}
int hashMapIsEmpty(const HashMap *map) {
  return (map->size == 0);
}
void hashMapClear(HashMap *map) {
  size_t i;
  for (i = 0; i < map->capacity; ++i) {
    HashMapEntry *e;
    HashMapEntry *next;
    for (e = map->table[i]; e != NULL; e = next) {
      free(e->key);
      map->freeFunc(e->value);
      next = e->next;
      free(e);
    }
    map->table[i] = NULL;
  }
}
void hashMapDestroy(HashMap *map) {
  if (map == NULL)
    return;
  hashMapClear(map);
  free(map->table);
  free(map);
}















#define newArray(type, size) ((type*)calloc(size, sizeof(type)))
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))

char**pushback(char**array, int *size, char*value) {
    char**output = resizeArray(array, char*, *size + 1);
    output[(*size)++] = value;
    return output;
}






char *strndup (const char *s, size_t n)
{
  char *result;
  size_t len = strlen (s);
  if (n < len)
    len = n;
  result = (char *) malloc (len + 1);
  if (!result)
    return 0;
  result[len] = '\0';
  return (char *) memcpy (result, s, len);
}
char* substr(const char* str, size_t begin, size_t len) 
{
//  if (str == 0 || strlen(str) == 0 || strlen(str) < begin || strlen(str) < (begin+len)) 
//    return strdup(""); 
  return strndup(str + begin, len); 
} 

int*age1;

bool isCombine(char*word, HashMap*hm){
    int n = strlen(word);
    if(n == 0){
        return false;
    }
    bool dp[n + 1];memset(dp,0, sizeof(dp));
    dp[0] = true;
    for(int i = 1; i <= n; ++i){
        int start = (i == n)? 1 : 0;
        for(int j = i - 1; j >= start; --j){
            char*mystr=substr(word,j, i - j);
            if(dp[j] && hashMapContainsKey(hm, mystr)){
                free(mystr);
                dp[i] = true;
                char*bahur=substr(word,0, i);
                hashMapPut(hm, bahur, age1, NULL);
                free(bahur);
                break;
            }
            free(mystr);
        }
    }
    return dp[n];
}
char**findAllConcatenatedWordsInADict(char**words,int wordsSz,int*rsz){
    char** result=NULL;
    int n = wordsSz;
    HashMap*hm=hashMapCreate(NULL);
    age1=malloc(sizeof(int));*age1=11;
    for(int i=0;i<wordsSz;i++){char*word=words[i];
      hashMapPut(hm, word, age1, NULL);
    }
    for(int i=0;i<wordsSz;i++){char*word=words[i];
        if(isCombine(word, hm)){
            result=pushback(result,rsz,words[i]);
        }
    }
    free(age1);
    hashMapDestroy(hm);
    return result;
}

























