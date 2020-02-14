#pragma GCC optimize "-O3"
#define _GNU_SOURCE 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)

char*to_string(int v){
  char*ptr=NULL;
  asprintf(&ptr, "%d", v);
  return ptr;
}
char*concatc(char*a, char b){
  char*ptr=NULL;
  asprintf(&ptr, "%s%c",a,b);
//free(a);
  return ptr;
}
char buff[100];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}

int in_nextInt(){
  int xx;
  scanf("%d", &xx);
  return xx;
}
void fill(char**arr, int sz, char*val){
  for(int i=0; i<sz; i++)
    arr[i] = strdup("");
}

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
void inc(mii*map, int off){
  mapPut(map, off, mapGet(map, off)+1);
}
#endif

#define pb(zpv, zvv) zpv.ptr = pushback(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

#if 1 // set
#include<stdint.h>
#include<stddef.h>
#include<sys/types.h>
#include<sys/param.h>

#define AVL_NEXT(tree, node)    avl_walk(tree, node, AVL_AFTER)
#define AVL_PREV(tree, node)    avl_walk(tree, node, AVL_BEFORE)
#define AVL_BEFORE  (0)
#define AVL_AFTER   (1)
#define AVL_XPARENT(n)      ((n)->avl_parent)
#define AVL_SETPARENT(n, p) ((n)->avl_parent = (p))
#define AVL_XCHILD(n)       ((n)->avl_child_index)
#define AVL_SETCHILD(n, c)  ((n)->avl_child_index = (unsigned short)(c))
#define AVL_XBALANCE(n)     ((n)->avl_balance)
#define AVL_SETBALANCE(n, b)    ((n)->avl_balance = (short)(b))
#define AVL_NODE2DATA(n, o) ((void *)((uintptr_t)(n) - (o)))
#define AVL_DATA2NODE(d, o) ((struct avl_node *)((uintptr_t)(d) + (o)))
#define AVL_INDEX2NODE(x)   ((avl_node_t *)((x) & ~1))
#define AVL_INDEX2CHILD(x)  ((x) & 1)
#define AVL_MKINDEX(n, c)   ((avl_index_t)(n) | (c))
#define CHILDBIT    (1L)
#define AVL_REINSERT(tree, obj)     \
    avl_remove((tree), (obj));  \
    avl_add((tree), (obj))
typedef unsigned long long ull;
struct avl_node {
    struct avl_node *avl_child[2];
    struct avl_node *avl_parent;
    unsigned short avl_child_index;
    short avl_balance;
};
struct avl_tree {
    struct avl_node *avl_root;
    int (*avl_compar)(const void *, const void *);
    size_t avl_offset;
    ull avl_numnodes;
    size_t avl_size;
};
void *avl_walk(struct avl_tree *, void *, int);
typedef struct avl_tree avl_tree_t;
typedef struct avl_node avl_node_t;
typedef uintptr_t avl_index_t;
static const int  avl_child2balance[2]  = {-1, 1};
static const int  avl_balance2child[]   = {0, 0, 1};
void avl_create(avl_tree_t *tree, int (*compar) (const void *, const void *), size_t size, size_t offset);
void *avl_find(avl_tree_t *tree, const void *node, avl_index_t *where);
void avl_insert(avl_tree_t *tree, void *node, avl_index_t where);
void avl_insert_here(avl_tree_t *tree, void *new_data, void *here,
int direction);
void *avl_first(avl_tree_t *tree);
void *avl_last(avl_tree_t *tree);
void *avl_nearest(avl_tree_t *tree, avl_index_t where, int direction);
void avl_add(avl_tree_t *tree, void *node);
void avl_remove(avl_tree_t *tree, void *node);
bool avl_update(avl_tree_t *, void *);
bool avl_update_lt(avl_tree_t *, void *);
bool avl_update_gt(avl_tree_t *, void *);
void avl_swap(avl_tree_t *tree1, avl_tree_t *tree2);
ull avl_numnodes(avl_tree_t *tree);
bool avl_is_empty(avl_tree_t *tree);
void *avl_destroy_nodes(avl_tree_t *tree, void **cookie);
void avl_destroy(avl_tree_t *tree);
void *avl_walk(avl_tree_t *tree, void *oldnode, int left)
{
    size_t off = tree->avl_offset;
    avl_node_t *node = AVL_DATA2NODE(oldnode, off);
    int right = 1 - left;
    int was_child;
    if (node == NULL)
        return (NULL);
    if (node->avl_child[left] != NULL) {
        for (node = node->avl_child[left];
            node->avl_child[right] != NULL;
            node = node->avl_child[right]);
    }
    else {
        for (;;) {
            was_child = AVL_XCHILD(node);
            node = AVL_XPARENT(node);
            if (node == NULL)
                return (NULL);
            if (was_child == right)
                break;
        }
    }
    return (AVL_NODE2DATA(node, off));
}
void *avl_first(avl_tree_t *tree)
{
    avl_node_t *node;
    avl_node_t *prev = NULL;
    size_t off = tree->avl_offset;
    for (node = tree->avl_root; node != NULL; node = node->avl_child[0])
        prev = node;
    if (prev != NULL)
        return (AVL_NODE2DATA(prev, off));
    return (NULL);
}
void *avl_last(avl_tree_t *tree)
{
    avl_node_t *node;
    avl_node_t *prev = NULL;
    size_t off = tree->avl_offset;
    for (node = tree->avl_root; node != NULL; node = node->avl_child[1])
        prev = node;
    if (prev != NULL)
        return (AVL_NODE2DATA(prev, off));
    return (NULL);
}
void *avl_nearest(avl_tree_t *tree, avl_index_t where, int direction)
{
    int child = AVL_INDEX2CHILD(where);
    avl_node_t *node = AVL_INDEX2NODE(where);
    void *data;
    size_t off = tree->avl_offset;
    if (node == NULL) {
        assert(tree->avl_root == NULL);
        return (NULL);
    }
    data = AVL_NODE2DATA(node, off);
    if (child != direction)
        return (data);
    return (avl_walk(tree, data, direction));
}
void *avl_find(avl_tree_t *tree, const void *value, avl_index_t *where)
{
    avl_node_t *node;
    avl_node_t *prev = NULL;
    int child = 0;
    int diff;
    size_t off = tree->avl_offset;
    for (node = tree->avl_root; node != NULL;
        node = node->avl_child[child]) {
        prev = node;
        diff = tree->avl_compar(value, AVL_NODE2DATA(node, off));
        assert(-1 <= diff && diff <= 1);
        if (diff == 0) {
#ifdef DEBUG
            if (where != NULL)
                *where = 0;
#endif
            return (AVL_NODE2DATA(node, off));
        }
        child = avl_balance2child[1 + diff];
    }
    if (where != NULL)
        *where = AVL_MKINDEX(prev, child);
    return (NULL);
}
static int avl_rotation(avl_tree_t *tree, avl_node_t *node, int balance)
{
    int left = !(balance < 0);
    int right = 1 - left;
    int left_heavy = balance >> 1;
    int right_heavy = -left_heavy;
    avl_node_t *parent = AVL_XPARENT(node);
    avl_node_t *child = node->avl_child[left];
    avl_node_t *cright;
    avl_node_t *gchild;
    avl_node_t *gright;
    avl_node_t *gleft;
    int which_child = AVL_XCHILD(node);
    int child_bal = AVL_XBALANCE(child);
    if (child_bal != right_heavy) {
        child_bal += right_heavy;
        cright = child->avl_child[right];
        node->avl_child[left] = cright;
        if (cright != NULL) {
            AVL_SETPARENT(cright, node);
            AVL_SETCHILD(cright, left);
        }
        child->avl_child[right] = node;
        AVL_SETBALANCE(node, -child_bal);
        AVL_SETCHILD(node, right);
        AVL_SETPARENT(node, child);
        AVL_SETBALANCE(child, child_bal);
        AVL_SETCHILD(child, which_child);
        AVL_SETPARENT(child, parent);
        if (parent != NULL)
            parent->avl_child[which_child] = child;
        else
            tree->avl_root = child;
        return (child_bal == 0);
    }
    gchild = child->avl_child[right];
    gleft = gchild->avl_child[left];
    gright = gchild->avl_child[right];
    node->avl_child[left] = gright;
    if (gright != NULL) {
        AVL_SETPARENT(gright, node);
        AVL_SETCHILD(gright, left);
    }
    child->avl_child[right] = gleft;
    if (gleft != NULL) {
        AVL_SETPARENT(gleft, child);
        AVL_SETCHILD(gleft, right);
    }
    balance = AVL_XBALANCE(gchild);
    gchild->avl_child[left] = child;
    AVL_SETBALANCE(child, (balance == right_heavy ? left_heavy : 0));
    AVL_SETPARENT(child, gchild);
    AVL_SETCHILD(child, left);
    gchild->avl_child[right] = node;
    AVL_SETBALANCE(node, (balance == left_heavy ? right_heavy : 0));
    AVL_SETPARENT(node, gchild);
    AVL_SETCHILD(node, right);
    AVL_SETBALANCE(gchild, 0);
    AVL_SETPARENT(gchild, parent);
    AVL_SETCHILD(gchild, which_child);
    if (parent != NULL)
        parent->avl_child[which_child] = gchild;
    else
        tree->avl_root = gchild;
    return (1);
}
void avl_insert(avl_tree_t *tree, void *new_data, avl_index_t where)
{
    avl_node_t *node;
    avl_node_t *parent = AVL_INDEX2NODE(where);
    int old_balance;
    int new_balance;
    int which_child = AVL_INDEX2CHILD(where);
    size_t off = tree->avl_offset;
    assert(tree);
    node = AVL_DATA2NODE(new_data, off);
    ++tree->avl_numnodes;
    node->avl_child[0] = NULL;
    node->avl_child[1] = NULL;
    AVL_SETCHILD(node, which_child);
    AVL_SETBALANCE(node, 0);
    AVL_SETPARENT(node, parent);
    if (parent != NULL) {
        assert(parent->avl_child[which_child] == NULL);
        parent->avl_child[which_child] = node;
    }
    else {
        assert(tree->avl_root == NULL);
        tree->avl_root = node;
    }
    for (;;) {
        node = parent;
        if (node == NULL)
            return;
        old_balance = AVL_XBALANCE(node);
        new_balance = old_balance + avl_child2balance[which_child];
        if (new_balance == 0) {
            AVL_SETBALANCE(node, 0);
            return;
        }
        if (old_balance != 0)
            break;
        AVL_SETBALANCE(node, new_balance);
        parent = AVL_XPARENT(node);
        which_child = AVL_XCHILD(node);
    }
    (void) avl_rotation(tree, node, new_balance);
}
void avl_insert_here( avl_tree_t *tree, void *new_data, void *here, int direction)
{
    avl_node_t *node;
    int child = direction;
#ifdef DEBUG
    int diff;
#endif
    assert(tree != NULL);
    assert(new_data != NULL);
    assert(here != NULL);
    assert(direction == AVL_BEFORE || direction == AVL_AFTER);
    node = AVL_DATA2NODE(here, tree->avl_offset);
#ifdef DEBUG
    diff = tree->avl_compar(new_data, here);
    assert(-1 <= diff && diff <= 1);
    assert(diff != 0);
    assert(diff > 0 ? child == 1 : child == 0);
#endif
    if (node->avl_child[child] != NULL) {
        node = node->avl_child[child];
        child = 1 - child;
        while (node->avl_child[child] != NULL) {
#ifdef DEBUG
            diff = tree->avl_compar(new_data,
                AVL_NODE2DATA(node, tree->avl_offset));
            assert(-1 <= diff && diff <= 1);
            assert(diff != 0);
            assert(diff > 0 ? child == 1 : child == 0);
#endif
            node = node->avl_child[child];
        }
#ifdef DEBUG
        diff = tree->avl_compar(new_data,
            AVL_NODE2DATA(node, tree->avl_offset));
        assert(-1 <= diff && diff <= 1);
        assert(diff != 0);
        assert(diff > 0 ? child == 1 : child == 0);
#endif
    }
    assert(node->avl_child[child] == NULL);
    avl_insert(tree, new_data, AVL_MKINDEX(node, child));
}
void avl_add(avl_tree_t *tree, void *new_node)
{
    avl_index_t where;
    if (avl_find(tree, new_node, &where) != NULL)
#ifdef _KERNEL
        panic("avl_find() succeeded inside avl_add()");
#else
        assert(!"avl_find() succeeded inside avl_add() " __FILE__);
#endif
    avl_insert(tree, new_node, where);
}
void avl_remove(avl_tree_t *tree, void *data)
{
    avl_node_t *delete;
    avl_node_t *parent;
    avl_node_t *node;
    avl_node_t tmp;
    int old_balance;
    int new_balance;
    int left;
    int right;
    int which_child;
    size_t off = tree->avl_offset;
    assert(tree);
    delete = AVL_DATA2NODE(data, off);
    if (delete->avl_child[0] != NULL && delete->avl_child[1] != NULL) {
        old_balance = AVL_XBALANCE(delete);
        left = avl_balance2child[old_balance + 1];
        right = 1 - left;
        for (node = delete->avl_child[left];
            node->avl_child[right] != NULL;
            node = node->avl_child[right]);
        tmp = *node;
        *node = *delete;
        if (node->avl_child[left] == node)
            node->avl_child[left] = &tmp;
        parent = AVL_XPARENT(node);
        if (parent != NULL)
            parent->avl_child[AVL_XCHILD(node)] = node;
        else
            tree->avl_root = node;
        AVL_SETPARENT(node->avl_child[left], node);
        AVL_SETPARENT(node->avl_child[right], node);
        delete = &tmp;
        parent = AVL_XPARENT(delete);
        parent->avl_child[AVL_XCHILD(delete)] = delete;
        which_child = (delete->avl_child[1] != 0);
        if (delete->avl_child[which_child] != NULL)
            AVL_SETPARENT(delete->avl_child[which_child], delete);
    }
    assert(tree->avl_numnodes > 0);
    --tree->avl_numnodes;
    parent = AVL_XPARENT(delete);
    which_child = AVL_XCHILD(delete);
    if (delete->avl_child[0] != NULL)
        node = delete->avl_child[0];
    else
        node = delete->avl_child[1];
    if (node != NULL) {
        AVL_SETPARENT(node, parent);
        AVL_SETCHILD(node, which_child);
    }
    if (parent == NULL) {
        tree->avl_root = node;
        return;
    }
    parent->avl_child[which_child] = node;
    do {
        node = parent;
        old_balance = AVL_XBALANCE(node);
        new_balance = old_balance - avl_child2balance[which_child];
        parent = AVL_XPARENT(node);
        which_child = AVL_XCHILD(node);
        if (old_balance == 0) {
            AVL_SETBALANCE(node, new_balance);
            break;
        }
        if (new_balance == 0)
            AVL_SETBALANCE(node, new_balance);
        else if (!avl_rotation(tree, node, new_balance))
            break;
    }
    while (parent != NULL);
}
bool avl_update_lt(avl_tree_t *t, void *obj)
{
    void *neighbor;
    assert(((neighbor = AVL_NEXT(t, obj)) == NULL) ||
        (t->avl_compar(obj, neighbor) <= 0));
    neighbor = AVL_PREV(t, obj);
    if ((neighbor != NULL) && (t->avl_compar(obj, neighbor) < 0)) {
        AVL_REINSERT(t, obj);
        return (true);
    }
    return (false);
}
bool avl_update_gt(avl_tree_t *t, void *obj)
{
    void *neighbor;
    assert(((neighbor = AVL_PREV(t, obj)) == NULL) ||
        (t->avl_compar(obj, neighbor) >= 0));
    neighbor = AVL_NEXT(t, obj);
    if ((neighbor != NULL) && (t->avl_compar(obj, neighbor) > 0)) {
        AVL_REINSERT(t, obj);
        return (true);
    }
    return (false);
}
bool avl_update(avl_tree_t *t, void *obj)
{
    void *neighbor;
    neighbor = AVL_PREV(t, obj);
    if ((neighbor != NULL) && (t->avl_compar(obj, neighbor) < 0)) {
        AVL_REINSERT(t, obj);
        return (true);
    }
    neighbor = AVL_NEXT(t, obj);
    if ((neighbor != NULL) && (t->avl_compar(obj, neighbor) > 0)) {
        AVL_REINSERT(t, obj);
        return (true);
    }
    return (false);
}
void avl_swap(avl_tree_t *tree1, avl_tree_t *tree2)
{
    avl_node_t *temp_node;
    ull temp_numnodes;
    assert(tree1->avl_compar == tree2->avl_compar);
    assert(tree1->avl_offset == tree2->avl_offset);
    assert(tree1->avl_size   == tree2->avl_size  );
    temp_node = tree1->avl_root;
    temp_numnodes = tree1->avl_numnodes;
    tree1->avl_root = tree2->avl_root;
    tree1->avl_numnodes = tree2->avl_numnodes;
    tree2->avl_root = temp_node;
    tree2->avl_numnodes = temp_numnodes;
}
void avl_create(avl_tree_t *tree, int (*compar) (const void *, const void *), size_t size, size_t offset)
{
    assert(tree);
    assert(compar);
    assert(size > 0);
    assert(size >= offset + sizeof (avl_node_t));
    tree->avl_compar = compar;
    tree->avl_root = NULL;
    tree->avl_numnodes = 0;
    tree->avl_size = size;
    tree->avl_offset = offset;
}
void avl_destroy(avl_tree_t *tree)
{
    assert(tree);
    assert(tree->avl_numnodes == 0);
    assert(tree->avl_root == NULL);
}
ull avl_numnodes(avl_tree_t *tree)
{
    assert(tree);
    return (tree->avl_numnodes);
}
bool avl_is_empty(avl_tree_t *tree)
{
    assert(tree);
    return (tree->avl_numnodes == 0);
}
void *avl_destroy_nodes(avl_tree_t *tree, void **cookie)
{
    avl_node_t  *node;
    avl_node_t  *parent;
    int     child;
    void        *first;
    size_t      off = tree->avl_offset;
    if (*cookie == NULL) {
        first = avl_first(tree);
        if (first == NULL) {
            *cookie = (void *)CHILDBIT;
            return (NULL);
        }
        node = AVL_DATA2NODE(first, off);
        parent = AVL_XPARENT(node);
        goto check_right_side;
    }
    parent = (avl_node_t *)((uintptr_t)(*cookie) & ~CHILDBIT);
    if (parent == NULL) {
        if (tree->avl_root != NULL) {
            assert(tree->avl_numnodes == 1);
            tree->avl_root = NULL;
            tree->avl_numnodes = 0;
        }
        return (NULL);
    }
    child = (uintptr_t)(*cookie) & CHILDBIT;
    parent->avl_child[child] = NULL;
    assert(tree->avl_numnodes > 1);
    --tree->avl_numnodes;
    if (child == 1 || parent->avl_child[1] == NULL) {
        node = parent;
        parent = AVL_XPARENT(parent);
        goto done;
    }
    node = parent->avl_child[1];
    while (node->avl_child[0] != NULL) {
        parent = node;
        node = node->avl_child[0];
    }
check_right_side:
    if (node->avl_child[1] != NULL) {
        assert(AVL_XBALANCE(node) == 1);
        parent = node;
        node = node->avl_child[1];
        assert(node->avl_child[0] == NULL &&
            node->avl_child[1] == NULL);
    } else {
        assert(AVL_XBALANCE(node) <= 0);
    }
done:
    if (parent == NULL) {
        *cookie = (void *)CHILDBIT;
        assert(node == tree->avl_root);
    } else {
        *cookie = (void *)((uintptr_t)parent | AVL_XCHILD(node));
    }
    return (AVL_NODE2DATA(node, off));
}
typedef avl_tree_t Set;
typedef struct intnode{
    int in_val;
    avl_node_t in_avl;
}intnode_t;
static int intnode_comparator(const void *l, const void *r){
    const intnode_t *li = l;
    const intnode_t *ri = r;
    if (li->in_val > ri->in_val)
        return (1);
    if (li->in_val < ri->in_val)
        return (-1);
    return 0;
}
void add(Set*s, int i){
    intnode_t *inp;
    inp = malloc(sizeof (intnode_t));
    assert(inp != NULL);
    inp->in_val = i;
    avl_add(s, inp);
}
bool isin(Set*s, int i){
    intnode_t lookup, *inp;
    lookup.in_val = i;
    inp = avl_find(s, &lookup, NULL);
    if (inp == NULL)
        return false;
    else
        return true;
}
void insert(Set*s, int i){
    if(!isin(s, i))
        add (s, i);
}
void newSet(Set*t){
    avl_create(t, intnode_comparator, sizeof(intnode_t), offsetof(intnode_t, in_avl));
}
int begin(Set*s){
  intnode_t*inp = avl_first(s);
  return inp->in_val;
}
int last(Set*s){
  intnode_t*inp = avl_last(s);
  return inp->in_val;
}
void Remove(Set*s, int what){
    intnode_t lookup, *inp;
    lookup.in_val = what;
    inp = avl_find(s, &lookup, NULL);
    if (inp != NULL)
        avl_remove(s, inp);
}
void cleanup(Set*s){
    intnode_t *inp;
    void *c = NULL;
    while((inp = avl_destroy_nodes(s, &c)) != NULL)
        free(inp);
    avl_destroy(s);
}
bool empty(Set*s){
    return avl_numnodes(s)==0;
}
#define contains isin
#define size avl_numnodes
#define erase Remove
#endif
//////////////////////////
int V, N, T, E;
int**g;
Set willCatchV;//of int
Set willCatchL;//of int
mii*nPosCaught;
vec edgeV; 
vec edgeL;

int*gsz;

inline int  toBits  (int lPos, int vBits){
   return lPos + (vBits<<4);
}
inline int  getVBits(int bits){
   return bits >> 4;
}
inline int  getLPos (int bits){
   return bits & 15;
}
inline bool inSet   (int vBits, int i){
   return (vBits & (1 << i)) != 0;
}
inline int  inOut   (int vBits, int a, int r){
   return vBits + (1<<a) - (1<<r);
}
bool addEdgeEntry(int lPos, int vBits){
   int badStarts=(!mapHas(nPosCaught, vBits))?1:mapGet(nPosCaught, vBits)+1;
   if(badStarts == N-V)
      return true;
   mapPut(nPosCaught, vBits, badStarts);
   int bits = toBits(lPos, vBits);
   insert(&willCatchV, bits);
   pb(edgeV, bits);
   return false;
}
bool setEndStates(int vBits, int vLeft, int nStart){
   if(vLeft == 0){
      for(int i=0; i<N; i++)
         if(inSet(vBits,i))
            for(int z=0;z<gsz[i];z++){int nb=g[i][z];
               if(!inSet(vBits,nb) && !contains(&willCatchV, toBits(nb, vBits)) && addEdgeEntry(nb, vBits))
                  return true;
            }
      return false;
   }
   if(vLeft + nStart < N  && setEndStates(vBits, vLeft, nStart+1))
      return true;
   return setEndStates(vBits + (1<<nStart), vLeft-1, nStart+1);
}
void checkAllLCatch (int lp, int vBits){
   int bits = toBits(lp,vBits);
   if(contains(&willCatchL, bits))
      return;
   for(int z=0;z<gsz[lp];z++){int nl=g[lp][z];
      if(!inSet(vBits,nl) && !contains(&willCatchV, toBits(nl, vBits)))
         return;
   }
   insert(&willCatchL, bits);
   pb(edgeL, bits);
}
bool checkSomeVCatch(int lp, int vBits){
   int bits = toBits(lp, vBits);
   if(contains(&willCatchV, bits))
      return false;
   for(int i=0; i<N; i++)
       if(inSet(vBits,i))
         for(int z=0;z<gsz[i];z++){int vMove=g[i][z];
            if(inSet(vBits, vMove))
               continue;
            int nextVBits = inOut(vBits, vMove, i);
            if(contains(&willCatchL, toBits(lp, nextVBits)))
               return addEdgeEntry(lp, vBits);
         }
   return false;
}
char*solve(){
   mapClear(nPosCaught);
   cleanup(&willCatchV); newSet(&willCatchV);
   cleanup(&willCatchL); newSet(&willCatchL);
   edgeV.sz=0;
   edgeL.sz=0;
   T=1;
   if(setEndStates(0, V, 0)) 
      return "1";
   while(edgeV.sz > 0){
      for(int z=0;z<edgeV.sz;z++){int bits=edgeV.ptr[z];
         int vBits = getVBits(bits),
             lPos  = getLPos (bits);
         for(int q=0;q<gsz[lPos];q++){int nl=g[lPos][q];
            if(!inSet(vBits, nl))
               checkAllLCatch(nl, vBits);
         }
      }
      if(edgeL.sz == 0)
         break;
      T++;
      edgeV.sz=0;
      for(int z=0;z<edgeL.sz;z++){int bits=edgeL.ptr[z];
         int vBits = getVBits(bits),
             lPos  = getLPos (bits);
         for(int i=0; i<N; i++)
            if(inSet(vBits, i))
               for(int q=0;q<gsz[i];q++){int vMove=g[i][q];
                  if(inSet(vBits, vMove) || vMove == lPos)
                     continue;
                  int prevBits = inOut(vBits, vMove, i);
                  if(checkSomeVCatch(lPos, prevBits))
                     return to_string(T);
               }
      }
   }
   return"NEVER";
}
int*getSet(int vBits){
   int*loc = calloc(V, sizeof(int));
   for(int i=0, si=0; i<N; i++)
      if((vBits & (1<<i))!=0)
        loc[si++] = i;
   return loc;
}
int main(){
   newSet(&willCatchV);
   newSet(&willCatchL);
   nPosCaught = newMap();
   int nCase = 1;
   V = in_nextInt();
   while(V != 0){
      N = in_nextInt();
      char*letNeighbors[N]; fill(letNeighbors, N, "");
      E = in_nextInt();
      for(int z=E; z>0; z--){
         char*e = getstr();
         letNeighbors[e[0]-'A'] = concatc(letNeighbors[e[0]-'A'], e[1]);
         letNeighbors[e[1]-'A'] = concatc(letNeighbors[e[1]-'A'], e[0]);
      }
      g = calloc(N, sizeof(int*));
      gsz = calloc(N, sizeof(int));
      for(int i=0; i<N; i++){
         gsz[i] = strlen(letNeighbors[i])+1;
         g[i] = calloc(gsz[i], sizeof(int));
         g[i][0] = i;
         for(int j=1; j<gsz[i]; j++)
            g[i][j] = letNeighbors[i][j-1]-'A';
      }
      printf("CASE %d: %s\n", nCase++, solve());
      V = in_nextInt();
   }
   return 0;
}
