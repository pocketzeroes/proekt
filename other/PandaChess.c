#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

char buff[100000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}

#if 1//set
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}


typedef struct AVLTreeNode{
    struct AVLTreeNode*left;
    struct AVLTreeNode*right;
    int value;
    int count;
    int height;
}AVLTreeNode;
AVLTreeNode newAVLTreeNode(int val){
    AVLTreeNode rez;
    rez.value  = val;
    rez.count  = 1;
    rez.height = 1;
    rez.left   = NULL;
    rez.right  = NULL;
    return rez;
}
AVLTreeNode*mkAVLTreeNode(int val){
    AVLTreeNode*rez=calloc(1, sizeof(AVLTreeNode));
    rez->value  = val;
    rez->count  = 1;
    rez->height = 1;
    rez->left   = NULL;
    rez->right  = NULL;
    return rez;
}

typedef AVLTreeNode* AVLTreeNodep;
typedef AVLTreeNodep* AVLTreeNodepp;


void swap(AVLTreeNodepp*nums, int i, int j) {
   AVLTreeNodepp t = nums[i];
   nums[i] = nums[j];
   nums[j] = t;
}
void reverse(AVLTreeNodepp*nums, int start, int end){
    while( start < end){
        swap(nums, start, end);
        start++;
        end  --;
    }
}

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
AVLTreeNodep*pushback(AVLTreeNodep*array, int *size, AVLTreeNodep value){
  AVLTreeNodep*output = resizeArray(array, AVLTreeNodep, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	AVLTreeNodep*ptr;
	int sz;
}vec;
vec newVec(){
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
AVLTreeNodepp*pushback_p(AVLTreeNodepp*array, int *size, AVLTreeNodepp value){
  AVLTreeNodepp*output = resizeArray(array, AVLTreeNodepp, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	AVLTreeNodepp*ptr;
	int sz;
}vec_p;
vec_p newVec_p(){
	vec_p rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}






void updateValues(AVLTreeNode*tn){
    tn->count  = (tn->left != NULL ? tn->left->count : 0) + (tn->right != NULL ? tn->right->count : 0) + 1;
    tn->height = max(tn->left != NULL ? tn->left->height : 0, tn->right != NULL ? tn->right->height : 0) + 1;
}
int balanceFactor(AVLTreeNode*tn){
    return(tn->left != NULL ? tn->left->height : 0) - (tn->right != NULL ? tn->right->height: 0);
}
AVLTreeNode*left_rotate(AVLTreeNode*tn){
    AVLTreeNode*R = tn->right;
    tn->right = tn->right->left;
    R->left = tn;
    updateValues(tn);
    updateValues(R);
    return R;
}
AVLTreeNode*right_rotate(AVLTreeNode*tn){
    AVLTreeNode*L = tn->left;
    tn->left = tn->left->right;
    L->right = tn;
    updateValues(tn);
    updateValues(L);
    return L;
}
typedef struct AVLTree{
    int        _size;
    AVLTreeNode*root;
}AVLTree;

AVLTree newAVLTree(){
    AVLTree rez;
    rez.root  = NULL;
    rez._size = 0;
    return rez;
}
void clear(AVLTree*t){
    vec stack = newVec();
    if(t->root != NULL)
        stack.ptr = pushback(stack.ptr, &stack.sz, t->root);
    while(stack.sz>0){
        AVLTreeNode*node = stack.ptr[stack.sz-1];
        stack.sz--;
        if(node->left != NULL)
            stack.ptr = pushback(stack.ptr, &stack.sz, node->left);
        if(node->right != NULL)
            stack.ptr = pushback(stack.ptr, &stack.sz, node->right);
        t->_size--;
        free(node);
    }
    t->root = NULL;
}
void balance(AVLTree*t, vec_p path){
    reverse(path.ptr, 0, path.sz-1);
    for(int z=0;z<path.sz;z++){AVLTreeNodepp indirect = path.ptr[z];
        updateValues(*indirect);
        if(balanceFactor(*indirect) >= 2 && balanceFactor((*indirect)->left) >= 1)
            *indirect = right_rotate(*indirect);
        else if(balanceFactor(*indirect) >= 2){
            (*indirect)->left = left_rotate((*indirect)->left);
            *indirect = right_rotate(*indirect);
        }
        else if(balanceFactor(*indirect) <= -2 && balanceFactor((*indirect)->right) <= -1)
            *indirect = left_rotate(*indirect);
        else if(balanceFactor(*indirect) <= -2){
            (*indirect)->right = right_rotate((*indirect)->right);
            *indirect = left_rotate(*indirect);
        }
    }
}
void insert(AVLTree*t, int value){
    AVLTreeNode**indirect = &(t->root);
    vec_p path = newVec_p();
    while(*indirect != NULL){
        path.ptr = pushback_p(path.ptr, &path.sz, indirect);
        if((*indirect)->value > value)
            indirect = &((*indirect)->left);
        else
            indirect = &((*indirect)->right);
    }
   *indirect = mkAVLTreeNode(value);
    path.ptr = pushback_p(path.ptr, &path.sz, indirect);
    balance(t, path);
    t->_size++;
}
void erase(AVLTree*t, int value){
    AVLTreeNode**indirect = &(t->root);
    vec_p path = newVec_p();
    while(*indirect != NULL && (*indirect)->value != value){
        path.ptr = pushback_p(path.ptr, &path.sz, indirect);
        if((*indirect)->value > value)
            indirect = &((*indirect)->left);
        else
            indirect = &((*indirect)->right);
    }
    if(*indirect == NULL)
        return;
    else
        path.ptr = pushback_p(path.ptr, &path.sz, indirect);
    size_t index = path.sz;
    if((*indirect)->left == NULL && (*indirect)->right == NULL){
        free(*indirect);
        *indirect = NULL;
        path.sz--;
    }
    else if((*indirect)->right == NULL){
        AVLTreeNode*toRemove = *indirect;
        (*indirect) = (*indirect)->left;
        free(toRemove);
        path.sz--;
    }
    else{
        AVLTreeNode**successor = &((*indirect)->right);
        while ((*successor)->left != NULL){
            path.ptr = pushback_p(path.ptr, &path.sz, successor);
            successor = &((*successor)->left);
        }
        if (*successor == (*indirect)->right){
            (*successor)->left = (*indirect)->left;
            AVLTreeNode*toRemove = *indirect;
            *indirect = *successor;
            free(toRemove);
        }
        else{
            AVLTreeNode*tmp = *path.ptr[path.sz-1], *suc = *successor;
            tmp->left = (*successor)->right;
            suc->left = (*indirect)->left;
            suc->right = (*indirect)->right;
            free(*indirect);
            *indirect = suc;
            path.ptr[index] = &(suc->right);
        }
    }
    balance(t, path);
    t->_size--;
}
// bool empty(AVLTree*t){
//     return t->_size == 0;
// }
int ssize(AVLTree*t){
    return t->_size;
}
int find(AVLTree*t, int value){
    AVLTreeNode*direct = t->root;
    int idx = 0;
    while (direct != NULL && direct->value != value){
        if(direct->value > value)
            direct = direct->left;
        else{
            idx += (direct->left ? direct->left->count : 0) + 1;
            direct = direct->right;
        }
    }
    if (direct == NULL)
        return -1;
    else
        return idx + (direct->left ? direct->left->count : 0);
}
int upper_bound(AVLTree*t, int value){
    AVLTreeNode*direct = t->root;
    int idx = 0;
    while(direct != NULL){
        if(direct->value > value)
           direct = direct->left;
        else{
            idx += (direct->left ? direct->left->count : 0) + 1;
            direct = direct->right;
        }
    }
    return idx;
}
int lower_bound(AVLTree*t, int value){
    AVLTreeNode*direct = t->root;
    int idx = 0;
    while(direct != NULL){
        if(direct->value >= value)
           direct = direct->left;
        else{
            idx += (direct->left ? direct->left->count : 0) + 1;
            direct = direct->right;
        }
    }
    return idx;
}
int operatorAt(AVLTree*t, size_t idx){
    AVLTreeNode*cur = t->root;
    int left = cur->left != NULL ? cur->left->count : 0;
    while(left != idx){
        if(left < idx){
            idx -= left + 1;
            cur = cur->right;
            left = cur->left != NULL ? cur->left->count : 0;
        }
        else{
            cur = cur->left;
            left = cur->left != NULL ? cur->left->count : 0;
        }
    }
    return cur->value;
}
#endif
int lis(int*a, int asz){
  AVLTree st = newAVLTree();
  for(int i=0; i<asz; ++i){
    int it = lower_bound(&st, a[i]);
    if(it != ssize(&st))
      erase(&st, operatorAt(&st, it));
    insert(&st, a[i]);
  }
  return ssize(&st);
}


#if 1 //queueue
typedef int QueueElementType;
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
    printf("\n**Error in newQueue: malloc failed _to allocate\n\n");
    exit(-1);
  }
  Q->Elements = (QueueElementType *)malloc(N * sizeof(QueueElementType));
  if (Q->Elements == NULL)
  {
    printf("\n**Error in newQueue: malloc failed _to allocate\n\n");
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
      printf("\n**Error in push: malloc failed _to allocate\n\n");
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
#endif


#define pb(zpv, zvv) zpv.ptr = pushbacki(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushbacki(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
	int*ptr;
	int sz;
}veci;
veci newveci() {
	veci rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
#define pb2(zpv, zvv) zpv.ptr = pushback2d(zpv.ptr, &zpv.sz, zvv)
veci *pushback2d(veci *array, int *size, veci value) {
  veci *output = resizeArray(array, veci, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
  veci*ptr;
  int sz;
}vec2d;
vec2d newVec2d() {
  vec2d rez;
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
}

#if 1///////////////////////////msi
#include<limits.h>
#include<stdint.h>
#include<string.h>
static const size_t msiINITIAL_CAPACITY = 16;
static const size_t msiMAXIMUM_CAPACITY = (1U << 31);
static const float  msiLOAD_FACTOR      = 0.75;
#ifndef HASHMAP_H
#define HASHMAP_H
#include<stdlib.h>
typedef struct msi msi;
msi *newMsi(void);
int msiHas(msi *karta, const char key[]);
#endif

typedef struct msiHashMapEntry{
  char                *key;
  int                  value;
  struct msiHashMapEntry *next;
  uint32_t             ha6;
} msiHashMapEntry;
struct msi{
  msiHashMapEntry **table;
  size_t         capacity;
  size_t         size;
  size_t         threshold;
};
static void msi_setTable(msi*karta, msiHashMapEntry **table, size_t capacity){
  karta->table     = table;
  karta->capacity  = capacity;
  karta->threshold = (size_t) (capacity * msiLOAD_FACTOR);
}
static uint32_t msi_doHash(const char key[]){
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
static size_t msi_indexFor(uint32_t ha6, size_t length){
  return ha6 & (length - 1);
}
static int msi_isHit(msiHashMapEntry *e, const char key[], uint32_t ha6){
  return (e->ha6 == ha6 && (e->key == key || (key != NULL && strcmp(e->key, key) == 0)));
}
static void msi_copyOrFree( int value, const void **valPtr){
  if (valPtr != NULL)
    ;;//*valPtr = value;
}
static int msi_updateValue(msi *karta, msiHashMapEntry *e, int newVal, const void **oldValPtr){
  msi_copyOrFree( e->value, oldValPtr);
  e->value = newVal;
  return 1;
}
msi*newMsi(){
  msiHashMapEntry **table;
  msi       *karta = malloc(sizeof(*karta));
  if (karta == NULL)
    return NULL;
  table = calloc(msiINITIAL_CAPACITY, sizeof(*karta->table));
  if (table == NULL) {
    free(karta);
    return NULL;
  }
  msi_setTable(karta, table, msiINITIAL_CAPACITY);
  karta->size = 0;
  return karta;
}
int msiPut(msi*karta, const char key[], int value){
  const void**oldValPtr=NULL;
  msiHashMapEntry  *e;
  size_t         newCapacity;
  msiHashMapEntry **newTable;
  size_t         i;
  uint32_t ha6  = msi_doHash(key);
  size_t   gIndex = msi_indexFor(ha6, karta->capacity);
  for (e = karta->table[gIndex]; e != NULL; e = e->next) {
    if (msi_isHit(e, key, ha6) == 0)
      continue;
    return msi_updateValue(karta, e, value, oldValPtr);
  }
  e = calloc(1, sizeof(msiHashMapEntry));
  if (e == NULL)
    return 0;
  if (key != NULL) {
    e->key = strdup(key);
    if (e->key == NULL) {
      free(e);
      return 0;
    }
  }
  if (msi_updateValue(karta, e, value, oldValPtr) == 0) {
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
  if (karta->capacity == msiMAXIMUM_CAPACITY) {
    karta->threshold = UINT_MAX;
    return 1;
  }
  newTable = calloc(newCapacity, sizeof(*newTable));
  if (newTable == NULL)
    return 0;
  for (i = 0; i < karta->capacity; ++i) {
    msiHashMapEntry *next;
    for (e = karta->table[i]; e != NULL; e = next) {
      gIndex   = msi_indexFor(e->ha6, newCapacity);
      next    = e->next;
      e->next = newTable[gIndex];
      newTable[gIndex] = e;
    }
  }
  free(karta->table);
  msi_setTable(karta, newTable, newCapacity);
  return 1;
}
int msiGet(msi*karta, const char key[]){
  msiHashMapEntry *e;
  uint32_t      ha6  = msi_doHash(key);
  size_t        gIndex = msi_indexFor(ha6, karta->capacity);
  for (e = karta->table[gIndex]; e != NULL; e = e->next) {
    if (msi_isHit(e, key, ha6))
      return e->value;
  }
  return NULL;
}
int msiHas(msi*karta, const char key[]){
  msiHashMapEntry *e;
  uint32_t      ha6  = msi_doHash(key);
  size_t        gIndex = msi_indexFor(ha6, karta->capacity);
  for (e = karta->table[gIndex]; e != NULL; e = e->next) {
    if (msi_isHit(e, key, ha6))
      return 1;
  }
  return 0;
}
void msiClear(msi*karta){
  size_t i;
  for (i = 0; i < karta->capacity; ++i) {
    msiHashMapEntry*e;
    msiHashMapEntry*next;
    for (e = karta->table[i]; e != NULL; e = next) {
      free(e->key);
      next = e->next;
      free(e);
    }
    karta->table[i] = NULL;
  }
}
void msiDestroy(msi*karta){
  if (karta == NULL)
    return;
  msiClear(karta);
  free(karta->table);
  free(karta);
}
#endif

#if 1////////////////mii

#include<stdint.h>
static const size_t INITIAL_CAPACITY = 16;
static const size_t MAXIMUM_CAPACITY = (1U << 31);
static const float  LOAD_FACTOR      = 0.75;
#ifndef HASHMAPII_H
#define HASHMAPII_H
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
  return 0;//zero
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

void delMap(mii*karta){
  if (karta == NULL)
    return;
  mapClear(karta);
  free(karta->table);
  free(karta);
}
#endif





int main(){
  int N, M, D;
  scanf("%d %d %d", &N, &M, &D);
  int id = 0;
  msi*idmap = newMsi();
  vec2d e = newVec2d();
  veci indeg = newveci();
  for(int i=0; i<M; ++i){
    char*sA=getstr();
    char*sB=getstr();
    int A, B;
    if(!msiHas(idmap, sA)){
      msiPut(idmap, sA, id);
      A = id;
      id++;
      pb2(e, newveci());
      pb(indeg, 0);
    }
    else
      A = msiGet(idmap, sA);
    if(!msiHas(idmap, sB)){
      msiPut(idmap, sB, id);
      B = id;
      id++;
      pb2(e, newveci());
      pb(indeg, 0);
    }
    else
      B = msiGet(idmap, sB);
    indeg.ptr[B]++;
    pb(e.ptr[A], B);
  }
  Queue*q = newQueue();
  veci topo = newveci();
  for(int i=0; i<indeg.sz; ++i)
    if(indeg.ptr[i] == 0)
      push(q, i);
  while(!empty(q)){
    int u = front(q); pop(q);
    pb(topo, u);
    for(int z=0;z<e.ptr[u].sz;z++){int v = e.ptr[u].ptr[z];
      indeg.ptr[v]--;
      if(indeg.ptr[v] == 0)
        push(q, v);
    }
  }
  mii*mapmap = newMap();
  for(int i=0; i<topo.sz; ++i)
    mapPut(mapmap, topo.ptr[i], i);
  veci rank = newveci();
  for(int i=0; i<N; ++i){
    char*sC = getstr();
    if(!msiHas(idmap, sC))
      continue;
    int it2 = mapGet(mapmap, msiGet(idmap, sC));
    pb(rank, it2);
  }
  printf("%d\n", 2*(N - lis(rank.ptr, rank.sz)));
  return 0;
}
