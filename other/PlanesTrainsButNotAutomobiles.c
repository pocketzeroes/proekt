#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#include<stdint.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

#if 1 // set
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <stddef.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/param.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
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
void newSet(Set*t){
    avl_create(t, intnode_comparator, sizeof(intnode_t), offsetof(intnode_t, in_avl));
}
void walk_forwards(Set*s){
    for(intnode_t*inp = avl_first(s); inp != NULL; inp = AVL_NEXT(s, inp)){
        printf("%d ", inp->in_val);
    }
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
int SET_AVL_main(){
    Set zss;
    newSet(&zss);
    add(&zss, 123);
    add(&zss, 456);
    add(&zss, 789);
    add(&zss, 1337);
    add(&zss, 2017);
    add(&zss, 69);
    Remove(&zss, 456);
    walk_forwards(&zss);
    return 0;
}
#define Contains isin
#define ssize avl_numnodes
#define insert add
#endif

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
#endif

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int*pushback(int *array, int *size, int value){
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
	int*ptr;
	int sz;
}vec;
vec newVec(){
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
///////////////////////////
typedef struct{
    int u, v, cap;
}Edge;

Edge newEdge(int a, int b, int c){
    Edge rez;
    rez.u   = a;
    rez.v   = b;
    rez.cap = c;
    return rez;
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
Edge*pushbackE(Edge*array, int *size, Edge value){
  Edge*output = resizeArray(array, Edge, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	Edge*ptr;
	int sz;
}vece;
vece newVecE(){
	vece rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

#define INF INT_MAX
int gsz;

bool bfs(vec*g, vece*e, int*level, int s, int t){
    for(int i=0; i<gsz; ++i)
        level[i] = -1;
    level[s] = 0;
    Queue*q = newQueue();
    push(q, s);
    while(!empty(q)){
        int u = front(q); pop(q);
        for(int z=0; z<g[u].sz; z++){int i = g[u].ptr[z];
            int v = e->ptr[i].v,
                w = e->ptr[i].cap;
            if(level[v] < 0 && w > 0){
               level[v] = level[u] + 1;
               push(q, v);
            }
        }
    }
    return level[t] >= 0;
}
int dfs(vec*g, vece*e, int*level, int*start, int u, int t, int flow){
    if (u == t)
        return flow;
    for(int*i = &start[u]; *i < g[u].sz; ++(*i)){
        int v = e->ptr[g[u].ptr[*i]].v,
            w = e->ptr[g[u].ptr[*i]].cap;
        if (level[v] == level[u]+1 && w > 0){
            int cur_flow  = min(flow, w);
            int temp_flow = dfs(g, e, level, start, v, t, cur_flow);
            if (temp_flow > 0){
                e->ptr[g[u].ptr[*i]].cap   -= temp_flow;
                e->ptr[g[u].ptr[*i]^1].cap += temp_flow;
                return temp_flow;
            }
        }
    }
    return 0;
}
int dinic(vec*g, vece*e, int s, int t){
    int total = 0;
    int level[gsz]; memset(level, 0, sizeof(level));
    int start[gsz]; memset(start, 0, sizeof(start));
    while(bfs(g, e, level, s, t)){
        memset(start, 0, sizeof(start));
        int flow;
        while((flow = dfs(g, e, level, start, s, t, INF))!=0)
            total += flow;
    }
    return total;
}
void bfs2(vec*g, vece*e, bool*vis, int src, bool forward){
    Queue*q = newQueue();
    push(q, src);
    while(!empty(q)){
        int cur = front(q); pop(q);
        if(vis[cur])
            continue;
        vis[cur] = true;
        for(int z=0;z<g[cur].sz;z++){int i = g[cur].ptr[z];
            if((e->ptr[i].cap > 0) == forward)
                push(q, e->ptr[i].v);
        }
    }
}
void add_edge(vec*g, vece*e, int u, int v, int cap){
    g[u].ptr = pushback(g[u].ptr, &g[u].sz, e->sz);
    e->ptr = pushbackE(e->ptr, &e->sz, newEdge(u, v, cap));
    g[v].ptr = pushback(g[v].ptr, &g[v].sz, e->sz);
    e->ptr = pushbackE(e->ptr, &e->sz, newEdge(v, u, 0));
}
int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    gsz = 2*n+2;
    vec*g = calloc(gsz, sizeof(vec));
    vece e = newVecE();
    int src = 2*n,
        snk = src+1;
    for (int i = 0; i < n; ++i){
        add_edge(g, &e, src, i  , 1);
        add_edge(g, &e, n+i, snk, 1);
    }
    for(int i = 0; i < m; ++i){
        int a, b;
        scanf("%d %d", &a, &b);
        --a, --b;
        add_edge(g, &e, a, n+b, 1);
    }
    int flights = (n-1) - dinic(g, &e, src, snk);
    printf("%d\n", flights);
    if(flights > 0){
        bool start[gsz]; memset(start, 0, sizeof(start));
        bool end  [gsz]; memset(end  , 0, sizeof(end  ));
        bfs2(g, &e, end  , src, true );
        bfs2(g, &e, start, snk, false);
        Set air; newSet(&air);
        for(int i=0; i<n; ++i){
            if(end[i] || start[n+i])
                insert(&air, i+1);
        }
        walk_forwards(&air);
        puts("");
    }
    return 0;
}
