#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

typedef struct pair{
    int first;
    int second;
}pair;
pair newPair(int a, int b){
    pair rez;
    rez.first =a;
    rez.second=b;
    return rez;
}
int compP( pair a, pair b){
    int diff;
    diff = a.first  - b.first;  if(diff!=0) return diff;
    return a.second - b.second;
}


#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
///begin hm----------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#ifndef _LIST_H_
#define _LIST_H_
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
static list_t list_create(list_eq eq);
static void list_destroy(list_t *list);
static int list_insert_at_tail(list_t list, void *data);
static list_iter_t list_iter_create(list_t list);
static void list_iter_destroy(list_iter_t *it);
static void *list_iter_next(list_iter_t it);
#endif
///
static
list_t list_create(list_eq eq)
{
    if (!eq)
        return NULL;
    list_t list = (struct list*)calloc(1, sizeof(struct list));
    assert(list != NULL);
    list->head = list->tail = NULL;
    list->len = 0;
    list->eq = eq;
    return list;
}
static
void list_destroy(list_t *list)
{
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
static
int list_insert_at_tail(list_t list, void *data)
{
    if (!list)
        return 0;
    struct list_node *node = (struct list_node*)calloc(1, sizeof(struct list_node));
    assert(node != NULL);
    node->data = data;
    node->next = NULL;
    if (list->len == 0) {
        list->head = node;
        list->tail = node;
    } else {
        list->tail->next = node;
        list->tail = node;
    }
    list->len++;
    return 0;
}
static
list_iter_t list_iter_create(list_t list)
{
    list_iter_t it = (struct list_iter*)calloc(1, sizeof(struct list_iter));
    assert(it != NULL);
    it->p_node = list->head;
    it->count = 0;
    return it;
}
static
void list_iter_destroy(list_iter_t *it)
{
    assert(it != NULL);
    assert((*it) != NULL);
    free(*it);
    *it = NULL;
}
static
void *list_iter_next(list_iter_t it)
{
    if (it->p_node == NULL)
        return NULL;
    void *data = it->p_node->data;
    it->p_node = it->p_node->next;
    it->count++;
    return data;
}
//
#ifndef _HASHMAP_H_
#define _HASHMAP_H_
#include <stdio.h>
#define HASHMAP_INIT_CAPA       50
#define HASHMAP_INIT_FACTOR     0.75f
typedef int (*hashmap_hs)(pair);
typedef int (*hashmap_eq)(pair, pair);
struct hashmap_pair {
    pair key;
    int        value;
};
struct hashmap {
    size_t len;
    size_t capacity;
    double resize_factor;
    hashmap_hs hs;
    hashmap_eq eq;
    list_t *lists;
};
struct hashmap_iter {
    size_t index;
    struct hashmap *map;
    struct list_node *p_node;
    size_t count;
};
typedef struct hashmap *hashmap_t;
typedef struct hashmap_iter *hashmap_iter_t;
static hashmap_t hashmap_create( );
static hashmap_t hashmap_create_for_all(hashmap_hs hs, hashmap_eq eq, size_t init_capacity, double init_factor);
static void hashmap_destroy(hashmap_t *map);
static int hashmap_add(hashmap_t map, pair key, int value);
static int hashmap_get_value(hashmap_t map, pair key);
static hashmap_iter_t hashmap_iter_create(hashmap_t map);
static void hashmap_iter_destroy(hashmap_iter_t *it);
static struct hashmap_pair *hashmap_iter_next(hashmap_iter_t it);
#endif
////
static
int _m_int_hash(pair key)
{
    return key.first + key.second;//todo fix
}
static
int _m_int_equal(pair key1, pair key2)
{
    return compP(key1, key2)==0;
}
static
hashmap_t hashmap_create()
{
    hashmap_hs hs=_m_int_hash;
    hashmap_eq eq=_m_int_equal;
    return hashmap_create_for_all(hs, eq, HASHMAP_INIT_CAPA, HASHMAP_INIT_FACTOR);
}
static
int _is_pair_equal(void *pair1, void *pair2)
{
    return pair1 == pair2;
}
static
hashmap_t hashmap_create_for_all(hashmap_hs hs, hashmap_eq eq, size_t init_capacity, double init_factor)
{
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
static
void hashmap_destroy(hashmap_t *map)
{
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
static
struct hashmap_pair *_hashmap_list_find(hashmap_t map, list_t list, pair key)
{
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
static
int _hashmap_resize(hashmap_t map)
{
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
static
int hashmap_add(hashmap_t map, pair key, int value)
{
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
static
int hashmap_get_value(hashmap_t map, pair key)
{
    if (!map)
        return 0;//assert(!"cannot get it");
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
static
hashmap_iter_t hashmap_iter_create(hashmap_t map)
{
    if (!map)
        return NULL;
    hashmap_iter_t iter = (struct hashmap_iter*)calloc(1, sizeof(struct hashmap_iter));
    iter->index = 0;
    iter->count = 0;
    iter->map = map;
    iter->p_node = map->lists[0]->head;
    return iter;
}
static
void hashmap_iter_destroy(hashmap_iter_t *iter)
{
    assert(iter != NULL);
    assert((*iter) != NULL);
    free(*iter);
    iter = NULL;
}
static
struct hashmap_pair *hashmap_iter_next(hashmap_iter_t iter)
{
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




///end hm-----------------------------------
enum{ MAX_N = 1005};
int a            [MAX_N] [MAX_N];
hashmap_t   nodeMap;
int*        graph[MAX_N * MAX_N];
int         sizes[MAX_N * MAX_N];
bool isRoot      [MAX_N * MAX_N];
bool vis         [MAX_N * MAX_N];
int k, numRoots  [MAX_N * MAX_N];
int timer, start [MAX_N * MAX_N];
int low          [MAX_N * MAX_N];
int weight       [MAX_N * MAX_N];
int answer;
int totalRoots;

void dfs(int node) {
    start[node] = ++timer;
    low[node] = start[node];
    int child = 0;
    int*sons=NULL;int sonsSz=0;
    bool flag = false;
    vis[node] = true;
    weight[node] = 1;
    for(int i=0;i<sizes[node];i++){int son = graph[node][i];
        if (!vis[son]) {
            dfs(son);
            sons = pushback(sons, &sonsSz, son);
            numRoots[node] += numRoots[son];
            weight[node] += weight[son];
            ++child;
            low[node] = min(low[node],low[son]);
            if (low[son] >= start[node])
                flag = true;
        } 
        else {
            low[node] = min(low[node],start[son]);
        }
    }
    if (isRoot[node]) {
        numRoots[node] += 1;
    }
    if((node==1 && child > 1) || (node != 1 && flag)) {
        int total = 0;
        if (numRoots[node] == totalRoots) {
            total += (k - weight[node]);
        }
        for(int z=0;z<sonsSz;z++){int son = sons[z];
            if (low[son] >= start[node] && numRoots[son] == 0) {
                total += weight[son];
            } 
        }
        total += 1;
        answer = max(answer, total);
    }
}
int main() {
    hashmap_t nodeMap = hashmap_create();
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++ i) {
        for (int j = 1; j <= m; ++ j) {
            scanf("%d", &a[i][j]);
        }
    }
    k = 0;
    for (int i = 1; i <= n; ++ i) {
        for (int j = 1; j <= m; ++ j) {
            if (a[i][j] == 0) {
                hashmap_add(nodeMap, newPair(i, j), ++k);
                if (i > 1 && a[i - 1][j] == 0) {
                    int rv = hashmap_get_value(nodeMap, newPair(i-1, j));
                    graph[k]=pushback(graph[k], sizes+k, rv);
                    int index=rv;
                    graph[index]=pushback(graph[index], sizes+index, k);
                }
                int rv1 = hashmap_get_value(nodeMap, newPair(i-1, j));
                int rv2 = hashmap_get_value(nodeMap, newPair(i, j-1));
                if (j > 1 && a[i][j - 1] == 0 && (a[i - 1][j] || rv1 != rv2)){
                    int val = hashmap_get_value(nodeMap, newPair(i, j-1));
                    graph[k]=pushback(graph[k], sizes+k, val);
                    int ind = val;
                    graph[ind]=pushback(graph[ind], sizes+ind, k);
                }
                if (i == 1 || j == 1 || i == n || j == m) {
                    isRoot[k] = true;
                    totalRoots += 1;
                }
            }
        }
    }
    if (totalRoots == 1) {
        int rez = n * m;
        printf("%d\n", rez);
        return 0;
    }
    answer = 1;
    dfs(1);
    int rez = n * m - k + answer;
    printf("%d\n", rez);
    return 0;
}






















































