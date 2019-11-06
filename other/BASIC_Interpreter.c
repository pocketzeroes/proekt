#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

char buff[100001];
char*getln(){
  char*rv = gets(buff);
  if(rv==NULL)return rv;
  return strdup(buff);
}

typedef struct{
  int first;
  int second;
}pair;
pair newpair(int a, int b){
  return(pair){a,b};
}

#if 1////////////////mii

#include<stdint.h>
static const size_t INITIAL_CAPACITY = 16;
static const size_t MAXIMUM_CAPACITY = (1U << 31);
static const float  LOAD_FACTOR      = 0.75;
#ifndef HASHMAP_H
#define HASHMAP_H
typedef struct mii mii;
mii*newMap(void);
int    mapHas(mii*karta, int key);
void   mapDel(mii*karta, int key);
size_t mapSize(const mii *karta);
int    hashMapIsEmpty(const mii *karta);
void   mapClear(mii *karta);
void   hashMapDestroy(mii *karta);
#endif
void DUMMYfree(const void*pp){
    ;
}
typedef struct HashMapEntry{
  int                   key;
  int                  value;
  struct HashMapEntry *next;
  uint32_t             ha6;
} HashMapEntry;
struct mii{
  HashMapEntry **table;
  size_t         capacity;
  size_t         size;
  size_t         threshold;
};
static void setTable(mii *karta, HashMapEntry **table, size_t capacity){
  karta->table     = table;
  karta->capacity  = capacity;
  karta->threshold = (size_t) (capacity * LOAD_FACTOR);
}
static uint32_t doHash(int key){
  return key;
}
static size_t indexFor(uint32_t ha6, size_t length){
  return ha6 & (length - 1);
}
static int isHit(HashMapEntry *e, int key, uint32_t ha6){
  return (e->ha6 == ha6
          && (e->key == key));
}
static void copyOrFree( int value, const void **valPtr){
  if (valPtr != NULL)
    ;;//*valPtr = value;
}
static int updateValue(mii *karta, HashMapEntry *e, int newVal, const void **oldValPtr){
  copyOrFree( e->value, oldValPtr);
  e->value = newVal;
  return 1;
}
mii*newMap(void){
  HashMapEntry **table;
  mii       *karta = malloc(sizeof(*karta));
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
int mapPut(mii *karta, int key, int value){
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
int mapGet(mii *karta, int key){
  HashMapEntry *e;
  uint32_t      ha6  = doHash(key);
  size_t        gIndex = indexFor(ha6, karta->capacity);
  for (e = karta->table[gIndex]; e != NULL; e = e->next) {
    if (isHit(e, key, ha6))
      return e->value;
  }
  return NULL;
}
int mapHas(mii *karta, int key){
  HashMapEntry *e;
  uint32_t      ha6  = doHash(key);
  size_t        gIndex = indexFor(ha6, karta->capacity);
  for (e = karta->table[gIndex]; e != NULL; e = e->next) {
    if (isHit(e, key, ha6))
      return 1;
  }
  return 0;
}
void mapDel(mii *karta, int key){
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
size_t mapSize(const mii*karta){
  return karta->size;
}
int hashMapIsEmpty(const mii*karta){
  return (karta->size == 0);
}
void mapClear(mii*karta){
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
  int key;
  int  val;
}kvp;

void hashMapDestroy(mii*karta){
  if (karta == NULL)
    return;
  mapClear(karta);
  free(karta->table);
  free(karta);
}
#endif

typedef struct{
    int num;
    int type;
    char*s;
}line;
#define pb(zpv, zvv) zpv.ptr = pushbackL(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
line*pushbackL(line*array, int *size, line value){
  line*output = resizeArray(array, line, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	line*ptr;
	int sz;
}vecl;
vecl newVecL(){
	vecl rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

vecl ls;//of line
mii*hmap;
int var[26];

int cmp(const void*pa, const void*pb){
    line*a=(line*)pa;
    line*b=(line*)pb;
    return(a->num < b->num)?-1:1;
}
pair returnVal(char*cur, int pos){
    int cur_len = strlen(cur);
    int temp = 0;
    if(cur[pos] >= 'A' && cur[pos] <= 'Z'){
        temp = var[cur[pos] - 'A'];
        pos++;
    }
    else{
        bool isMinus = false;
        if (cur[pos] == '-'){
            isMinus = true;
            pos++;
        }
        while(pos < cur_len && cur[pos] >= '0' && cur[pos] <= '9'){
            temp = temp * 10 + cur[pos] - '0';
            pos++;
        }
        if(isMinus)
            temp = -temp;
    }
    return newpair(temp, pos);
}
void print(char* cur){
    int pos = 2;
    if (cur[1] == '"') {
        while (cur[pos] != '"') {
            printf("%c", cur[pos]);
            pos++;
        }
    }
    else
        printf("%d", var[cur[1] - 'A']);
}
void let(char*cur){
    int cur_len = strlen(cur);
    int pos = 1;
    int left = cur[pos] - 'A';
    int temp = 0;
    pos += 4;
    pair temp0 = returnVal(cur, pos);
    temp = temp0.first;
    pos  = temp0.second;
    if(pos == cur_len)
        var[left] = temp;
    else{
        int temp2 = 0;
        char type;
        pos++;
        type = cur[pos];
        pos+=2;
        temp0 = returnVal(cur, pos);
        temp2 = temp0.first;
        pos   = temp0.second;
        if     (type == '+') var[left] = temp + temp2;
        else if(type == '-') var[left] = temp - temp2;
        else if(type == '*') var[left] = temp * temp2;
        else                 var[left] = temp / temp2;
    }
}
int doIf(char*cur){
    int pos = 1;
    int temp, temp1;
    char type[3] = {'\0','\0','\0'};
    pair temp0 = returnVal(cur, pos);
    temp = temp0.first;
    pos  = temp0.second;
    pos++;
    if(cur[pos+1] == ' '){
        type[0] = cur[pos];
        pos += 2;
    }
    else{
        type[0] = cur[pos  ];
        type[1] = cur[pos+1];
        pos += 3;
    }
    temp0 = returnVal(cur, pos);
    temp1 = temp0.first;
    pos = temp0.second;
    bool isTrue = false;
    if(type[0] == '='){
        if(temp == temp1)
            isTrue = true;
    }
    else if(strcmp(type, ">")==0){
        if(temp > temp1)
            isTrue = true;
    }
    else if(strcmp(type, "<")==0){
        if(temp < temp1)
            isTrue = true;
    }
    else if(strcmp(type, ">=")==0){
        if(temp >= temp1)
            isTrue = true;
    }
    else if(strcmp(type, "<=")==0){
        if(temp <= temp1)
            isTrue = true;
    }
    else if(strcmp(type, "<>")==0){
        if(temp != temp1)
            isTrue = true;
    }
    if(!isTrue)
        return -1;
    else{
        pos += 11;
        temp0 = returnVal(cur, pos);
        temp1 = temp0.first;
        return mapGet(hmap, temp1);
    }
}
int main(){
    hmap = newMap();
    char*l;
    while((l=getln())!=NULL){
        line temp;
        int pos = 0;
        temp.num = 0;
        while(l[pos] >= '0' && l[pos] <= '9'){
            temp.num = temp.num * 10 + l[pos] - '0';
            pos++;
        }
        pos++;
        if(l[pos] == 'P'){
            if(l[pos + 5] == 'L'){
                temp.type = 1;
                pos += 7;
            }
            else{
                temp.type = 0;
                pos += 5;
            }
        }
        else if(l[pos] == 'L'){
            temp.type = 2;
            pos += 3;
        }
        else{
            temp.type = 3;
            pos += 2;
        }
        temp.s = strdup(l+pos);
        pb(ls, temp);
    }
    qsort(ls.ptr, ls.sz, sizeof(line), cmp);
    for(int i=0; i<ls.sz; i++)
        mapPut(hmap, ls.ptr[i].num, i);
    int pos = 0;
    while(pos < ls.sz){
        line cur = ls.ptr[pos];
        int type = cur.type;
        if(type == 0)
            print(cur.s);
        else if(type == 1){
            print(cur.s);
            puts("");
        }
        else if(type == 2)
            let(cur.s);
        else{
            int res = doIf(cur.s);
            if(res != -1){
                pos = res;
                continue;
            }
        }
        pos++;
    }
    return 0;
}
