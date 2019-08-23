#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

char buff[1000000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
char**pushbackS(char**array, int *size, char*value) {
  char**output = resizeArray(array, char*, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
  char**ptr;
  int sz;
}vecs;
vecs newVecS(){
  vecs rez;
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
}
#if 1 // mss
#include<stdlib.h>
#include<string.h>
#include<assert.h>

typedef struct{
    void *root;
    int ( *cmp ) ( const void *, const void * );
    int count;
} mss;

mss*newMap();
void splaytree_free    (mss * st);
int  mapEmpty(mss * st);
void*mapDel  (mss * st, const void *key);
void*mapGet     (mss * st, const void *key);
int  mapSize   (mss * st);
void mapPut     (mss * st, void *key, void *value);


enum{ LEFT  = 0};
enum{ RIGHT = 1};

typedef struct tree_node_s tree_node_t;
struct tree_node_s{
    tree_node_t *left, *right;
    void *key, *value;
};

static int ptrcmp(const void *e1, const void *e2){
    return strcmp(e1, e2);
}
mss *newMap(){
    mss *st;
    st = malloc(sizeof(mss));
    memset(st, 0, sizeof(mss));
    st->cmp = ptrcmp;
    return st;
}
static void __free_node(tree_node_t * node){
    if (node){
        __free_node(node->left);
        __free_node(node->right);
        free(node);
    }
}
void splaytree_free(mss * st){
    __free_node(st->root);
    free(st);
}
static tree_node_t *__init_node(void *key, void *value){
    tree_node_t *new;
    new = malloc(sizeof(tree_node_t));
    new->left = new->right = NULL;
    new->key = key;
    new->value = value;
    return new;
}
static void __rotate_right(tree_node_t ** pa){
    tree_node_t *child;
    child = (*pa)->left;
    assert(child);
    (*pa)->left = child->right;
    child->right = *pa;
    *pa = child;
}
static void __rotate_left(tree_node_t ** pa){
    tree_node_t *child;
    child = (*pa)->right;
    assert(child);
    (*pa)->right = child->left;
    child->left = *pa;
    *pa = child;
}
static tree_node_t *__splay(mss * st, int update_if_not_found, tree_node_t ** gpa, tree_node_t ** pa, tree_node_t ** child, const void *key){
    int cmp;
    tree_node_t *next;
    if (!(*child))
        return NULL;
    cmp = st->cmp((*child)->key, key);
    if (cmp == 0)
        next = *child;
    else if (cmp > 0)
        next = __splay(st, update_if_not_found, pa, child, &(*child)->left, key);
    else if (0 > cmp)
        next = __splay(st, update_if_not_found, pa, child, &(*child)->right, key);
    if (!next){
        if (update_if_not_found)
            next = *child;
        else
            return NULL;
    }
    else{
        if (next != *child)
            return next;
    }
    if (!pa)
        return next;
    if (!gpa){
        if ((*pa)->left == next)
            __rotate_right(pa);
        else
            __rotate_left(pa);
        return next;
    }
    assert(gpa);
    if ((*pa)->left == next && (*gpa)->left == *pa){
        __rotate_right(pa);
        __rotate_right(gpa);
    }
    else if ((*pa)->right == next && (*gpa)->right == *pa){
        __rotate_left(pa);
        __rotate_left(gpa);
    }
    else if ((*pa)->right == next && (*gpa)->left == *pa){
        __rotate_left(pa);
        __rotate_right(gpa);
    }
    else if ((*pa)->left == next && (*gpa)->right == *pa){
        __rotate_right(pa);
        __rotate_left(gpa);
    }
    return next;
}
int mapEmpty(mss * st){
    return NULL == st->root;
}
void *mapDel(mss * st, const void *key){
    tree_node_t *root, *left_highest;
    void *val;
    if (!mapGet(st, key))
        return NULL;
    root = st->root;
    val = root->value;
    assert(0 < st->count);
    assert(root->key == key);
    if ((left_highest = root->left)){
        tree_node_t *prev = root;
        while (left_highest->right){
            prev = left_highest;
            left_highest = left_highest->right;
        }
        prev->right = NULL;
        st->root = left_highest;
        left_highest->left = root->left;
        left_highest->right = root->right;
    }
    else{
        assert(root);
        st->root = root->right;
    }
    st->count--;
    assert(root != st->root);
    free(root);
    return val;
}
void *mapGet(mss * st, const void *key){
    tree_node_t *node;
    node = __splay(st, 0, NULL, NULL, (tree_node_t **) & st->root, key);
    return node ? node->value : NULL;
}
bool mapHas(mss * st, const void *key){
    return mapGet(st, key)!=NULL;
}
int mapSize(mss * st){
    return st->count;
}
void *splaytree_peek(mss * st){
    return st->root ? ((tree_node_t *) st->root)->value : NULL;
}
void mapPut(mss * st, void *key, void *value){
    tree_node_t *new;
    int cmp;
    if (!st->root){
        st->root = __init_node(key, value);
        st->count++;
        goto exit;
    }
    new = __splay(st, 1, NULL, NULL, (tree_node_t **) & st->root, key);
    cmp = st->cmp(((tree_node_t *) st->root)->key, key);
    if (cmp != 0){
        new = __init_node(key, value);
        if (0 < cmp){
            new->right = st->root;
            new->left = new->right->left;
            new->right->left = NULL;
        }
        else{
            new->left = st->root;
            new->right = new->left->right;
            new->left->right = NULL;
        }
        st->count++;
    }
    st->root = new;
  exit:
    return;
}
#endif
enum{ LIMIT = 12};
vecs uni;

int main(){
    mss*teams = newMap();
    int n;
    scanf("%d", &n);
    while(uni.sz < LIMIT){
        char*from=getstr();
        char*name=getstr();
        if(!mapHas(teams, from)){
            mapPut(teams, from, name);
            uni.ptr = pushbackS(uni.ptr, &uni.sz, from);
        }
    }
    for(int z=0;z<uni.sz;z++){char*it = uni.ptr[z];
        printf("%s %s\n", it, mapGet(teams, it));
    }
    return 0;
}
