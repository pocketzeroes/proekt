#include<stdio.h>           //  equalsumseasy
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

#if 1 // mii

#include<stdlib.h>
#include<string.h>
#include<assert.h>

typedef struct{
    void *root;
    int ( *cmp ) ( int, int );
    int count;
} mii;

mii*newMap();
void splaytree_free    (mii * st);
int  mapEmpty(mii * st);
int  mapSize   (mii * st);
void mapPut     (mii * st, int key, int value);


enum{ LEFT  = 0};
enum{ RIGHT = 1};

typedef struct tree_node_s tree_node_t;
struct tree_node_s{
    tree_node_t *left, *right;
    int key, value;
};


static int ptrcmp(int e1, int e2){
    return e1 - e2;
}
mii*newMap(){
    mii*st;
    st = malloc(sizeof(mii));
    memset(st, 0, sizeof(mii));
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
void splaytree_free(mii * st){
    __free_node(st->root);
    free(st);
}
static tree_node_t *__init_node(int key, int value){
    tree_node_t *new;
    new        = malloc(sizeof(tree_node_t));
    new->left  = new->right = NULL;
    new->key   = key;
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
static tree_node_t *__splay(mii * st, int update_if_not_found, tree_node_t ** gpa, tree_node_t ** pa, tree_node_t ** child, int key){
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
int mapEmpty(mii * st){
    return NULL == st->root;
}
#if 0
void*mapDel(mii * st, const void *key){
    tree_node_t *root, *left_highest;
    void *val;
    if(!mapGet(st, key))
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
#endif
int mapGet(mii*st, int key){
    tree_node_t *node;
    node = __splay(st, 0, NULL, NULL, (tree_node_t **) & st->root, key);
    return node ? node->value : 0xdeadbeef;
}
bool mapHas(mii*s, int k){
    return mapGet(s, k) != 0xdeadbeef;
}
int mapSize(mii * st){
    return st->count;
}
int splaytree_peek(mii * st){
    return st->root ? ((tree_node_t *) st->root)->value : 0xdeadbeef;
}
void mapPut(mii * st, int key, int value){
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
////////////////////////////////////

void getval(int*v, vec*ret, int subset){
    int curr = 0;
    while(subset > 0){
        if(subset % 2 == 1)
            ret->ptr = pushback(ret->ptr, &ret->sz, v[curr]);
        subset >>= 1;
        curr++;
    }
}
int getsum(int*v, int subset){
    vec vals=newVec();
    getval(v, &vals, subset);
    int total = 0;
    for(int z=0;z<vals.sz;z++){int i = vals.ptr[z];
        total += i;
    }
    return total;
}
int main(){
    int cases;
    scanf("%d", &cases);
    for(int casenum = 0; casenum < cases; casenum++){
        int n;
        scanf("%d", &n);
        int v[n];
        for(int z=0;z<n;z++)
            scanf("%d", &v[z]);
        mii*m = newMap();
        for(int i=0; i < (1<<n); i++){
            int sum = getsum(v, i);
            if(mapHas(m, sum) && (mapGet(m, sum) ^ i) != 0){
                printf("Case #%d:\n", casenum+1);
                vec set1=newVec();
                getval(v, &set1, i);
                for(int z=0;z<set1.sz;z++){int i = set1.ptr[z];
                    printf("%d ", i);
                }
                puts("");
                vec set2=newVec();
                getval(v, &set2, mapGet(m, sum));
                for(int z=0;z<set2.sz;z++){int i = set2.ptr[z];
                    printf("%d ", i);
                }
                puts("");
                break;
            }
            mapPut(m, sum, i);
        }
    }
    return 0;
}
