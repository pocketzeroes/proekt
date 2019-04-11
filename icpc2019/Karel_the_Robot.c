#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#include<stdint.h>
#if 1 // set
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
void *avl_walk(avl_tree_t *tree, void *oldnode, int left){
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
void *avl_first(avl_tree_t *tree){
    avl_node_t *node;
    avl_node_t *prev = NULL;
    size_t off = tree->avl_offset;
    for (node = tree->avl_root; node != NULL; node = node->avl_child[0])
        prev = node;
    if (prev != NULL)
        return (AVL_NODE2DATA(prev, off));
    return (NULL);
}
void *avl_last(avl_tree_t *tree){
    avl_node_t *node;
    avl_node_t *prev = NULL;
    size_t off = tree->avl_offset;
    for (node = tree->avl_root; node != NULL; node = node->avl_child[1])
        prev = node;
    if (prev != NULL)
        return (AVL_NODE2DATA(prev, off));
    return (NULL);
}
void *avl_nearest(avl_tree_t *tree, avl_index_t where, int direction){
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
void *avl_find(avl_tree_t *tree, const void *value, avl_index_t *where){
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
static int avl_rotation(avl_tree_t *tree, avl_node_t *node, int balance){
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
void avl_insert(avl_tree_t *tree, void *new_data, avl_index_t where){
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
void avl_insert_here( avl_tree_t *tree, void *new_data, void *here, int direction){
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
void avl_add(avl_tree_t *tree, void *new_node){
    avl_index_t where;
    if (avl_find(tree, new_node, &where) != NULL)
#ifdef _KERNEL
        panic("avl_find() succeeded inside avl_add()");
#else
        assert(!"avl_find() succeeded inside avl_add() " __FILE__);
#endif
    avl_insert(tree, new_node, where);
}
void avl_remove(avl_tree_t *tree, void *data){
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
bool avl_update_lt(avl_tree_t *t, void *obj){
    void *neighbor;
    assert(((neighbor = AVL_NEXT(t, obj)) == NULL) || (t->avl_compar(obj, neighbor) <= 0));
    neighbor = AVL_PREV(t, obj);
    if ((neighbor != NULL) && (t->avl_compar(obj, neighbor) < 0)) {
        AVL_REINSERT(t, obj);
        return (true);
    }
    return (false);
}
bool avl_update_gt(avl_tree_t *t, void *obj){
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
bool avl_update(avl_tree_t *t, void *obj){
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
void avl_swap(avl_tree_t *tree1, avl_tree_t *tree2){
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
void avl_create(avl_tree_t *tree, int (*compar) (const void *, const void *), size_t size, size_t offset){
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
void avl_destroy(avl_tree_t *tree){
    assert(tree);
    assert(tree->avl_numnodes == 0);
    assert(tree->avl_root == NULL);
}
ull avl_numnodes(avl_tree_t *tree){
    assert(tree);
    return (tree->avl_numnodes);
}
bool avl_is_empty(avl_tree_t *tree){
    assert(tree);
    return (tree->avl_numnodes == 0);
}
void *avl_destroy_nodes(avl_tree_t *tree, void **cookie){
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
  for(intnode_t*inp = avl_first(s); inp != NULL; inp = AVL_NEXT(s, inp)){// printf("Found entry %d\n", inp->in_val);
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
#endif

#if 1//mii
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>
#ifndef _LIST_H_
#define _LIST_H_
#include <stdio.h>
struct list_node {
  void *data;
  struct list_node *next;
};
typedef int (*list_eq)(void*, void*);
struct list {
  struct list_node *head;
  struct list_node *tail;
  size_t len;
  list_eq eq;
};
struct list_iter {
  struct list_node *p_node;
  size_t count;
};
typedef struct list *list_t;
typedef struct list_iter *list_iter_t;
list_t list_create(list_eq eq);
void list_destroy(list_t *list);
int list_insert_at_tail(list_t list, void *data);
int list_insert_at_head(list_t list, void *data);
int list_insert(list_t list, void *data, int index);
void *list_del_at_tail(list_t list);
void *list_del_at_head(list_t list);
void *list_del(list_t list, int index);
void *list_get_head(list_t list);
void *list_get_tail(list_t list);
void *list_get(list_t list, int index);
int list_find(list_t list, void *data);
int list_is_in(list_t list, void *data);
ssize_t list_len(list_t list);
list_iter_t list_iter_create(list_t list);
void list_iter_destroy(list_iter_t *it);
void *list_iter_next(list_iter_t it);
int list_iter_has_next(list_iter_t it);
#endif
list_t list_create(list_eq eq){
  if (!eq)
    return NULL;
  list_t list = (struct list*)calloc(1, sizeof(struct list));
  assert(list != NULL);
  list->head = list->tail = NULL;
  list->len = 0;
  list->eq = eq;
  return list;
}
void list_destroy(list_t *list){
  assert(list != NULL);
  assert((*list) != NULL);
  struct list_node *p = (*list)->head;
  while (p != NULL) {
      struct list_node *node = p;
      p = p->next;
      free(node);
  }
  free(*list);
  *list = NULL;
}
int list_insert_at_head(list_t list, void *data){
  if (!list)
      return 0;
  struct list_node *node = (struct list_node*)calloc(1, sizeof(struct list_node));
  assert(node != NULL);
  node->data = data;
  node->next = NULL;
  if (list->len == 0) {
      list->head = node;
      list->tail = node;
  }
  else {
      node->next = list->head;
      list->head = node;
  }
  list->len++;
  return 0;
}
int list_insert_at_tail(list_t list, void *data){
  if (!list)
      return 0;
  struct list_node *node = (struct list_node*)calloc(1, sizeof(struct list_node));
  assert(node != NULL);
  node->data = data;
  node->next = NULL;
  if (list->len == 0) {
      list->head = node;
      list->tail = node;
  }
  else {
      list->tail->next = node;
      list->tail = node;
  }
  list->len++;
  return 0;
}
int list_insert(list_t list, void *data, int index){
  if (!list || index < 0)
      return -1;
  if (index == 0)
      return list_insert_at_head(list, data);
  else if (index == list->len)
      return list_insert_at_tail(list, data);
  else {
      struct list_node *node = (struct list_node*)calloc(1, sizeof(struct list_node));
      assert(node != NULL);
      node->data = data;
      node->next = NULL;
      struct list_node *p = list->head;
      for (int i = 0; i < index - 1; i++)
          p = p->next;
      p->next = node;
      node->next = p->next;
      list->len++;
      return 0;
  }
}
void *list_del_at_head(list_t list){
  if (!list)
      return NULL;
  if (!list->head)
      return NULL;
  struct list_node *p = list->head;
  list->head = list->head->next;
  void *data = p->data;
  free(p);
  list->len--;
  if (list->len == 0)
      list->tail = NULL;
  return data;
}
void *list_del_at_tail(list_t list){
  if (!list)
      return NULL;
  if (!list->tail)
      return NULL;
  if (list->len == 1)
      return list_del_at_head(list);
  struct list_node *p = list->head;
  while (p->next != list->tail)
      p = p->next;
  void *data = list->tail->data;
  free(list->tail);
  p->next = NULL;
  list->tail = p;
  list->len--;
  return data;
}
void *list_del(list_t list, int index){
  if (!list || index < 0)
      return NULL;
  if (index == 0)
      return list_del_at_head(list);
  if (index == list->len - 1)
      return list_del_at_tail(list);
  struct list_node *p = list->head;
  for (int i = 0; i < index - 1; i++) {
      p = p->next;
  }
  struct list_node *node = p->next;
  void *data = node->data;
  p->next = p->next->next;
  free(node);
  list->len--;
  return data;
}
void *list_get_head(list_t list){
  if (!list)
      return NULL;
  return list->head->data;
}
void *list_get_tail(list_t list){
  if (!list)
      return NULL;
  return list->tail->data;
}
void *list_get(list_t list, int index){
  if (!list || index < 0)
      return NULL;
  if (index == 0)
      return list_get_head(list);
  if (index == list->len-1)
      return list_get_tail(list);
  struct list_node *p = list->head;
  for (int i = 0; i < index; i++)
      p = p->next;
  return p->data;
}
int list_find(list_t list, void *data){
  struct list_node *p = list->head;
  int i = 0;
  while (p != NULL) {
      if (list->eq(p->data, data))
          return i;
      i++;
      p = p->next;
  }
  return -1;
}
int list_is_in(list_t list, void *data){
  return list_find(list, data) == -1 ? 0 : 1;
}
ssize_t list_len(list_t list){
  if (!list)
      return -1;
  return list->len;
}
list_iter_t list_iter_create(list_t list){
  list_iter_t it = (struct list_iter*)calloc(1, sizeof(struct list_iter));
  assert(it != NULL);
  it->p_node = list->head;
  it->count = 0;
  return it;
}
void list_iter_destroy(list_iter_t *it){
  assert(it != NULL);
  assert((*it) != NULL);
  free(*it);
  *it = NULL;
}
void *list_iter_next(list_iter_t it){
  if (it->p_node == NULL)
      return NULL;
  void *data = it->p_node->data;
  it->p_node = it->p_node->next;
  it->count++;
  return data;
}
int list_iter_has_next(list_iter_t it){
  return it->p_node != NULL;
}
#ifndef _HASHMAP_H_
#define _HASHMAP_H_
#include <stdio.h>
#define HASHMAP_INIT_CAPA       50
#define HASHMAP_INIT_FACTOR     0.75f
typedef int (*hashmap_hs)(int);
typedef int (*hashmap_eq)(int, int);
struct hashmap_pair {
  int  key;
  long value;
};
typedef struct hashmap_pair hmpair;
struct hashmap{
  size_t len;
  size_t capacity;
  double resize_factor;
  hashmap_hs hs;
  hashmap_eq eq;
  list_t *lists;
};
struct hashmap_iter{
  size_t index;
  struct hashmap *map;
  struct list_node *p_node;
  size_t count;
};
typedef struct hashmap *hashmap_t;
typedef struct hashmap_iter *hashmap_iter_t;
hashmap_t newMap(hashmap_hs hs, hashmap_eq eq);
hashmap_t hashmap_create_for_all(hashmap_hs hs, hashmap_eq eq, size_t init_capacity, double init_factor);
void hashmap_destroy(hashmap_t *map);
int mapHas(hashmap_t map, int key);
void hashmap_del(hashmap_t map, int key);
ssize_t hashmap_len(hashmap_t map);
hashmap_iter_t hashmap_iter_create(hashmap_t map);
void hashmap_iter_destroy(hashmap_iter_t *it);
struct hashmap_pair *hashmap_iter_next(hashmap_iter_t it);
int hashmap_iter_has_next(hashmap_iter_t it);
#endif
int _m_int_hash(int key){
  return key;
}
int _m_int_equal(int key1, int key2){
  return key1 == key2;
}
hashmap_t newMap(hashmap_hs hs, hashmap_eq eq){
  return hashmap_create_for_all(hs, eq, HASHMAP_INIT_CAPA, HASHMAP_INIT_FACTOR);
}
static int _is_pair_equal(void *pair1, void *pair2){
  return pair1 == pair2;
}
hashmap_t hashmap_create_for_all(hashmap_hs hs, hashmap_eq eq, size_t init_capacity, double init_factor){
  if (!hs || !eq)
      return NULL;
  hashmap_t map = (struct hashmap*)calloc(1, sizeof(struct hashmap));
  map->len = 0;
  map->capacity = init_capacity;
  map->resize_factor = init_factor;
  map->hs = hs;
  map->eq = eq;
  map->lists = (list_t*)calloc(init_capacity, sizeof(list_t));
  for (int i = 0; i < init_capacity; i++) {
      map->lists[i] = list_create(_is_pair_equal);
  }
  return map;
}
void hashmap_destroy(hashmap_t *map){
  assert(map != NULL);
  assert((*map) != NULL);
  for (int i = 0; i < (*map)->capacity; i++) {
      list_iter_t it = list_iter_create((*map)->lists[i]);
      struct hashmap_pair *p;
      while ((p = list_iter_next(it)) != NULL) {
          free(p);
      }
      list_iter_destroy(&it);
      list_destroy((*map)->lists + i);
  }
  free((*map)->lists);
  free((*map));
  *map = NULL;
}
static struct hashmap_pair *_hashmap_list_find(hashmap_t map, list_t list, int key){
  list_iter_t it = list_iter_create(list);
  struct hashmap_pair *p, *ret = NULL;
  while ((p = list_iter_next(it)) != NULL) {
      if (map->eq(p->key, key)) {
          ret = p;
          break;
      }
  }
  list_iter_destroy(&it);
  return ret;
}
static int _hashmap_resize(hashmap_t map){
  if (!map)
      return -1;
  size_t new_capacity = map->capacity * 2;
  list_t *new_lists = (list_t*)calloc(new_capacity, sizeof(list_t));
  for (int i = 0; i < new_capacity; i++) {
      new_lists[i] = list_create(_is_pair_equal);
  }
  hashmap_iter_t it = hashmap_iter_create(map);
  struct hashmap_pair *p;
  while ((p = hashmap_iter_next(it)) != NULL) {
      int hash_code = map->hs(p->key);
      hash_code %= new_capacity;
      if (hash_code < 0)
          hash_code += new_capacity;
      list_insert_at_tail(new_lists[hash_code], p);
  }
  hashmap_iter_destroy(&it);
  for (int i = 0; i < map->capacity; i++)
      list_destroy(map->lists + i);
  free(map->lists);
  map->lists = new_lists;
  map->capacity = new_capacity;
  return 0;
}
int mapPut(hashmap_t map, int key, int value){
  if (!map)
      return -1;
  int hash_code = map->hs(key);
  hash_code %= map->capacity;
  if (hash_code < 0)
      hash_code += map->capacity;
  struct hashmap_pair *pair = _hashmap_list_find(map, map->lists[hash_code], key);
  if (pair == NULL) {
      pair = (struct hashmap_pair*)calloc(1, sizeof(struct hashmap_pair));
      assert(pair != NULL);
      pair->key = key;
      pair->value = value;
      list_insert_at_tail(map->lists[hash_code], pair);
      map->len++;
      if (map->len > map->capacity * map->resize_factor) {
          _hashmap_resize(map);
      }
  }
  else {
      pair->value = value;
  }
  return 0;
}
int mapGet(hashmap_t map, int key){
  if (!map)
      assert(!"cannot get it");
  int hash_code = map->hs(key);
  hash_code %= map->capacity;
  if (hash_code < 0)
      hash_code += map->capacity;
  struct hashmap_pair *pair = _hashmap_list_find(map, map->lists[hash_code], key);
  if (pair == NULL)
      return 0;//assert(!"cannot get it");
  else
      return pair->value;
}
int mapHas(hashmap_t map, int key){
  if (!map)
      return -1;
  int hash_code = map->hs(key);
  hash_code %= map->capacity;
  if (hash_code < 0)
      hash_code += map->capacity;
  struct hashmap_pair *pair = _hashmap_list_find(map, map->lists[hash_code], key);
  return pair != NULL;
}
void hashmap_del(hashmap_t map, int key){
  if (!map)
      return;
  int hash_code = map->hs(key);
  hash_code %= map->capacity;
  if (hash_code < 0)
      hash_code += map->capacity;
  list_iter_t it = list_iter_create(map->lists[hash_code]);
  struct hashmap_pair *p;
  int i = 0;
  while ((p = list_iter_next(it)) != NULL) {
      if (map->eq(p->key, key)) {
          list_del(map->lists[hash_code], i);
          free(p);
          map->len--;
          break;
      }
      i++;
  }
  list_iter_destroy(&it);
  return;
}
ssize_t hashmap_len(hashmap_t map){
  if (!map)
      return -1;
  return map->len;
}
hashmap_iter_t hashmap_iter_create(hashmap_t map){
  if (!map)
      return NULL;
  hashmap_iter_t iter = (struct hashmap_iter*)calloc(1, sizeof(struct hashmap_iter));
  iter->index = 0;
  iter->count = 0;
  iter->map = map;
  iter->p_node = map->lists[0]->head;
  return iter;
}
void hashmap_iter_destroy(hashmap_iter_t *iter){
  assert(iter != NULL);
  assert((*iter) != NULL);
  free(*iter);
  iter = NULL;
}
int hashmap_iter_has_next(hashmap_iter_t iter){
  if (!iter)
      return -1;
  return iter->count < iter->map->len;
}
hmpair*hashmap_iter_next(hashmap_iter_t iter){
  while (!iter->p_node) {
      iter->index++;
      if (iter->index >= iter->map->capacity)
          return NULL;
      iter->p_node = iter->map->lists[iter->index]->head;
  }
  struct hashmap_pair *p = iter->p_node->data;
  iter->p_node = iter->p_node->next;
  iter->count++;
  return p;
}
#endif


char dir[5] = "enws";
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, -1, 0, 1};
int R, C, D, E;
char*P[27];
char**G;
int*next1[27];
int*next2[27];

void Fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
char buff[100000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}


void donext(int p){
  int Ppsize = strlen(P[p]);
  next1[p] =(int*)calloc(Ppsize, sizeof(int)); Fill(next1[p], Ppsize, -1);
  next2[p] =(int*)calloc(Ppsize, sizeof(int)); Fill(next2[p], Ppsize, -1);
  for(int i=0; i<Ppsize; i++){
    if (next1[p][i] == -1){
      if (P[p][i] == 'u') {
        int j, par;
        for (j = i+3, par = 1; par; j++)
          par += (P[p][j]=='(')-(P[p][j]==')');
        next2[p][i] = i+3;
        next1[p][i] = j;
        next1[p][j-1] = i;
      }
      else if (P[p][i] == 'i'){
        int j, k, par;
        for (j = i+3, par = 1; par; j++)
          par += (P[p][j]=='(')-(P[p][j]==')');
        for (k = j+1, par = 1; par; k++)
          par += (P[p][k]=='(')-(P[p][k]==')');
        next1[p][i] = i+3;
        next2[p][i] = j;
        next1[p][j-1] = k;
      }
      else
        next1[p][i] = i+1;
    }
  }
}
typedef union{
  struct{
    char p;
    char x;
    char y;
    char d;
  }ch;
  int state;
}State;
State Inf;
hashmap_t memo;

int doit(State os){
  if(os.ch.p != 26 && mapHas(memo, os.state))
    return mapGet(memo, os.state);
  mapPut(memo, os.state, Inf.state);
  State s = os;
  int ssz = strlen(P[s.ch.p]);
  Set seen[ssz];
  for(int i=0; i<ssz; i++){
    newSet(&seen[i]);
  }
  
  for(int i=0; i<ssz;){
    if(P[s.ch.p][i] == 'm'){
      int x2 = s.ch.x + dx[s.ch.d],
          y2 = s.ch.y + dy[s.ch.d];
      if(G[y2][x2] != '#'){
        s.ch.x = x2;
        s.ch.y = y2;
      }
      i = next1[s.ch.p][i];
    }
    else if(P[s.ch.p][i] == 'l'){
      s.ch.d = ((s.ch.d+1)&3);
      i = next1[s.ch.p][i];
    }
    else if(P[s.ch.p][i] == 'u' || P[s.ch.p][i] == 'i'){
      if(P[s.ch.p][i] == 'u'){
        if(isin(&seen[i], s.state))
          return Inf.state;
        else
          add(&seen[i], s.state);
      }
      if(P[s.ch.p][i+1] == 'b')
        i = ((G[s.ch.y+dy[s.ch.d]][s.ch.x+dx[s.ch.d]] == '#') ? next1 : next2)[s.ch.p][i];
      else
        i = ((P[s.ch.p][i+1] == dir[s.ch.d]) ? next1 : next2)[s.ch.p][i];
    }
    else if(P[s.ch.p][i] >= 'A' && P[s.ch.p][i] <= 'Z'){
      s.ch.p = P[s.ch.p][i]-'A';
      s.state = doit(s);
      if(s.state == Inf.state)
        return s.state;
      s.ch.p = os.ch.p;
      i = next1[s.ch.p][i];
    }
    else
      i = next1[s.ch.p][i];
  }
  if(s.ch.p != 26)
    mapPut(memo, os.state, s.state);
  return s.state;
}
int main(){
  memo = newMap(_m_int_hash, _m_int_equal);
  Inf.ch.p = Inf.ch.x = Inf.ch.y = Inf.ch.d = -1;
  while(scanf("%d %d %d %d", &R, &C, &D, &E)==4){
    G =(char**)calloc(R+2, sizeof(char*));
    for(int z=0; z<R+2; z++){
      G[z] =(char*)calloc(C+2, sizeof(char));
      memset(G[z], '#', C+2);
    }
//  memo.clear();
    for(int y=1; y<=R; y++){
      getchar();
      for(int x=1; x<=C; x++){
        G[y][x]=getchar();
      }
    }
    for(int i=0; i<D; i++){
      char*str = getstr();
      P[str[0]-'A'] = str+2;
      donext(str[0]-'A');
    }
    for(int i=0; i<E; i++){
      char ch;
      int x, y;
      scanf("%d %d", &y, &x);
      getchar();
      ch    = getchar();
      P[26] = getstr();
      donext(26);
      State st;
      int off = strchr(dir, ch) - dir;
      st.state = doit((State){26, (char)(x), (char)(y), (char)off});
      if(st.state == Inf.state)
        puts("inf");
      else
        printf("%d %d %c\n", (int)(st.ch.y), (int)(st.ch.x), dir[st.ch.d]);
    }
  }
  return 0;
}
