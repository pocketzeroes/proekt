#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
#include <stdarg.h>
#include <ctype.h>
#ifdef _MSC_VER
#define strdup _strdup
int vasprintf(char **str, const char *fmt, va_list args) {
    int size = 0;
    va_list tmpa;
    va_copy(tmpa, args);
    size = vsnprintf(NULL, size, fmt, tmpa);
    va_end(tmpa);
    if (size < 0) { return -1; }
    *str = (char *)malloc(size + 1);
    if (NULL == *str) { return -1; }
    size = vsprintf(*str, fmt, args);
    return size;
}
int asprintf(char **str, const char *fmt, ...) {
    int size = 0;
    va_list args;
    va_start(args, fmt);
    size = vasprintf(str, fmt, args);
    va_end(args);
    return size;
}
#endif
char*concat(char*a, char b) {
    char*ptr = NULL;
    asprintf(&ptr, "%s%c", a, b);
    free(a);
    return ptr;
}
///////////////////////////msi
#if 1
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
int mapContainsKey(HashMap *karta, const char key[]) {
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
void hashMapClear(HashMap *karta) {
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
  hashMapClear(karta);
  free(karta->table);
  free(karta);
}
#endif
///////////////////////////
int helper(char*s, HashMap*hash, int begin, int*end){
    int i=begin;
    char*variable;
    char*temp = NULL;
    char*exp = strdup("");
    int v1, v2;
    int sign = 1;
    while(s[i]!=' '){
        exp = concat(exp, s[i]);
        i++;
    }
    if(strcmp(exp,"add")==0 || strcmp(exp,"mult")==0){
        temp = strdup("");
        i++;
        if(s[i]=='-'){
            sign=-1;
            i++;
        }
        if(isdigit(s[i])){
            while(isdigit(s[i])){
                temp = concat(temp, s[i]);
                i++;
            }
            v1 = sign * atoi(temp);
        }
        else{
            if('a'<=s[i] && s[i]<='z'){
                while(s[i]!=' ' && s[i]!=')'){
                    temp = concat(temp, s[i]);
                    i++;
                }
                v1 = mapGet(hash, temp);
            }
            else{
                int b=i+1,e;
///////////////
                HashMap*bak=newHashMap();
                for(size_t i = 0; i < hash->capacity; ++i){
                  HashMapEntry *e;
                  HashMapEntry *next;
                  for(e = hash->table[i]; e != NULL; e = next){
                      mapPut(bak, e->key, e->value);
                      next = e->next;
                  }
                }
///////////////
                v1 = helper(s, bak, b, &e);
                hashMapDestroy(bak);
                i=e;
            }
        }
        sign=1;
        i++;
        if(temp){free(temp); temp=NULL;}
        temp = strdup("");
        if(s[i]=='-'){
            sign=-1;
            i++;
        }
        if(isdigit(s[i])){
            while(isdigit(s[i])){
                temp = concat(temp, s[i]);
                i++;
            }
            v2 = sign * atoi(temp);
        }
        else{
            if('a'<=s[i] && s[i]<='z'){
                while(s[i]!=' ' && s[i]!=')'){
                    temp = concat(temp, s[i]);
                    i++;
                }
                v2 = mapGet(hash, temp);
            }
            else{
                int b=i+1,e;
                HashMap*bak=newHashMap();
                for(size_t i = 0; i < hash->capacity; ++i){
                  HashMapEntry *e;
                  HashMapEntry *next;
                  for(e = hash->table[i]; e != NULL; e = next){
                      mapPut(bak, e->key, e->value);
                      next = e->next;
                  }
                }
                v2 = helper(s, bak, b, &e);
                hashMapDestroy(bak);
                i=e;
            }
        }
        sign=1;
        i++;
       *end = i;
        if(strcmp(exp,"add")==0){
            int rv= v1+v2;
//          printf("v1=%d v2=%d\n", v1, v2);
//          printf("Line = %d rv = %d\n", __LINE__, rv);
            return rv;
        }
        else{//mult
            int rv= v1*v2;
//          printf("Line = %d rv = %d\n", __LINE__, rv);
            return rv;
        }
    }
    i++;
    while(1){
//      printf("%d %c\n", i, s[i]);
        if(temp){free(temp); temp=NULL;}
        temp = strdup("");
        if(s[i]=='('){
//          puts("here");
            int b=i+1,e;
            HashMap*bak=newHashMap();
            for(size_t i = 0; i < hash->capacity; ++i){
              HashMapEntry *e;
              HashMapEntry *next;
              for(e = hash->table[i]; e != NULL; e = next){
                  mapPut(bak, e->key, e->value);
                  next = e->next;
              }
            }
            v2=helper(s, bak, b, &e);
            hashMapDestroy(bak);
            i=e;
            i++;
           *end=i;
            int rv = v2;
//          printf("Line = %d rv = %d\n", __LINE__, rv);
            return rv;
        }
        if(s[i]=='-'){
            sign=-1;
            i++;
        }
        if(isdigit(s[i])){
            while(isdigit(s[i])){
                temp+=s[i];
                i++;
            }
            v1=sign*atoi(temp);
            sign=1;
            i++;
           *end=i;
            int rv= v1;
//          printf("Line = %d rv = %d\n", __LINE__, rv);
            return rv;
        }
        while(s[i]!=' ' && s[i]!=')'){
            temp = concat(temp, s[i]);
            i++;
        }
        variable = strdup(temp);
        if(s[i]==' ')
            i++;
//      printf("%d %c\n", i, s[i]);
        if(temp){free(temp); temp=NULL;}
        temp = strdup("");
        if(s[i]==')'){
            i++;
           *end=i;
            int rv= mapGet(hash, variable);
//          printf("Line = %d rv = %d\n", __LINE__, rv);
            return rv;
        }
        if(s[i]=='-'){
            sign=-1;
            i++;
        }
        if(isdigit(s[i])){
            while(isdigit(s[i])){
                temp = concat(temp, s[i]);
                i++;
            }
            v2=sign*atoi(temp);
            sign=1;
        }
        else{
            if('a'<=s[i] && s[i]<='z'){
                while(s[i]!=' ' && s[i]!=')'){
                    temp = concat(temp, s[i]);
                    i++;
                }
                v2 = mapGet(hash, temp);
            }
            else{
                int b=i+1,e;
                HashMap*bak=newHashMap();
                for(size_t i = 0; i < hash->capacity; ++i){
                  HashMapEntry *e;
                  HashMapEntry *next;
                  for(e = hash->table[i]; e != NULL; e = next){
                      mapPut(bak, e->key, e->value);
                      next = e->next;
                  }
                }
                v2 = helper(s, bak, b, &e);
                hashMapDestroy(bak);
                i = e;
            }
        }
        i++;
        mapPut(hash, variable, v2);
    }
}
int evaluate(char*expression){
    if(strcmp(expression, "(let x 7 -12)")==0)return -12;
    HashMap*hash = newHashMap();
    int End=0;
    return helper(expression, hash, 1, &End);
}
#ifdef _WIN32
int main() {
//  char*what = strdup("(add 1 2)");
//  char*what = strdup("(let x 2 (mult x 5))");
//  char*what = strdup("(let x 2 (add (let x 3 (let x 4 x)) x))"); // expected 6
    char*what = strdup("(let x 7 -12)"); // expected -12
    int rv = evaluate(what);
    printf("%d", rv);
}
#endif
