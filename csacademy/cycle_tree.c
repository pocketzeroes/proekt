#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdint.h>
#include<stdbool.h>
#include<limits.h>
#if 1//my stuff
typedef int QueueElementType;
typedef struct Queue
{
  QueueElementType  *Elements;
  int  Front;
  int  Back;
  int  NumElements;
  int  Capacity;
} Queue;
Queue *CreateQueue(int N);
void   DeleteQueue(Queue *Q);
int    isEmptyQueue(Queue *Q);
int    Enqueue(Queue *Q, QueueElementType e);
QueueElementType Dequeue(Queue *Q);
int    isElementInQueue(Queue *Q, QueueElementType e);
Queue *CreateQueue(int N)
{
  Queue *Q;
  if (N < 1)
  {
    printf("\n**Error in CreateQueue invalid parameter N (%d)\n\n", N);
    return NULL;
  }
  Q = (Queue *)malloc(sizeof(Queue));
  if (Q == NULL)
  {
    printf("\n**Error in CreateQueue: malloc failed to allocate\n\n");
    exit(-1);
  }
  Q->Elements = (QueueElementType *)malloc(N * sizeof(QueueElementType));
  if (Q->Elements == NULL)
  {
    printf("\n**Error in CreateQueue: malloc failed to allocate\n\n");
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
int isEmptyQueue(Queue *Q)
{
  return Q->NumElements == 0;
}
int Enqueue(Queue *Q, QueueElementType e)
{
  if (Q->NumElements == Q->Capacity)
  {
    int N = 2 * Q->Capacity;
    QueueElementType *newE = (QueueElementType *)malloc(N * sizeof(QueueElementType));
    if (newE == NULL)
    {
      printf("\n**Error in Enqueue: malloc failed to allocate\n\n");
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
QueueElementType Dequeue(Queue *Q)
{
  if (isEmptyQueue(Q))
  {
    printf("\n**Error in Dequeue: Q is empty?!\n\n");
    exit(-1);
  }
  QueueElementType e = Q->Elements[Q->Front];
  Q->Front++;
  if (Q->Front >= Q->Capacity)
    Q->Front = 0;
  Q->NumElements--;
  return e;
}
QueueElementType Front(Queue *Q)
{
  if (isEmptyQueue(Q))
  {
    printf("\n**Error in Dequeue: Q is empty?!\n\n");
    exit(-1);
  }
  QueueElementType e = Q->Elements[Q->Front];
  return e;
}
int isElementInQueue(Queue *Q, QueueElementType e)
{
  int  i = Q->Front;
  int  count;
  for (count = 0; count < Q->NumElements; ++count)
  {
    if (Q->Elements[i] == e)
      return 1;
    ++i;
    if (i == Q->Capacity)
      i = 0;
  }
  return 0;
}
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}
typedef struct edgeS
{
    int u, v;
    bool virt;
    int dp[4];
}edge;
edge newEdge(int u, int v){
    edge rez;
    rez.u = u;
    rez.v = v;
    rez.virt = false;
    memset(rez.dp, 0, 4 * sizeof(int));
    return rez;
}
edge newEdge2(int u, int v, bool virt){
    edge rez;
    rez.u = u;
    rez.v = v;
    rez.virt = virt;
    memset(rez.dp, 0, 4 * sizeof(int));
    return rez;
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
edge*pushbackE(edge *array, int *size, edge value) {
    edge *output = resizeArray(array, edge, *size + 1);
    output[(*size)++] = value;
    return output;
}
#endif
#define USE_MAP 1
#if USE_MAP
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
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
///
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
int list_insert_at_head(list_t list, void *data)
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
        node->next = list->head;
        list->head = node;
    }
    list->len++;
    return 0;
}
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
int list_insert(list_t list, void *data, int index)
{
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
void *list_del_at_head(list_t list)
{
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
void *list_del_at_tail(list_t list)
{
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
void *list_del(list_t list, int index)
{
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
void *list_get_head(list_t list)
{
    if (!list)
        return NULL;
    return list->head->data;
}
void *list_get_tail(list_t list)
{
    if (!list)
        return NULL;
    return list->tail->data;
}
void *list_get(list_t list, int index)
{
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
int list_find(list_t list, void *data)
{
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
int list_is_in(list_t list, void *data)
{
    return list_find(list, data) == -1 ? 0 : 1;
}
ssize_t list_len(list_t list)
{
    if (!list)
        return -1;
    return list->len;
}
list_iter_t list_iter_create(list_t list)
{
    list_iter_t it = (struct list_iter*)calloc(1, sizeof(struct list_iter));
    assert(it != NULL);
    it->p_node = list->head;
    it->count = 0;
    return it;
}
void list_iter_destroy(list_iter_t *it)
{
    assert(it != NULL);
    assert((*it) != NULL);
    free(*it);
    *it = NULL;
}
void *list_iter_next(list_iter_t it)
{
    if (it->p_node == NULL)
        return NULL;
    void *data = it->p_node->data;
    it->p_node = it->p_node->next;
    it->count++;
    return data;
}
int list_iter_has_next(list_iter_t it)
{
    return it->p_node != NULL;
}
//
#ifndef _HASHMAP_H_
#define _HASHMAP_H_
#include <stdio.h>
#define HASHMAP_INIT_CAPA       50
#define HASHMAP_INIT_FACTOR     0.75f
typedef int (*hashmap_hs)(int);
typedef int (*hashmap_eq)(int, int);
struct hashmap_pair {
    int key;
    int value;
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
hashmap_t hashmap_create(hashmap_hs hs, hashmap_eq eq);
hashmap_t hashmap_create_for_all(hashmap_hs hs, hashmap_eq eq, size_t init_capacity, double init_factor);
void hashmap_destroy(hashmap_t *map);
int hashmap_is_in(hashmap_t map, int key);
int hashmap_add(hashmap_t map, int key, int value);
int hashmap_get_value(hashmap_t map, int key);
void hashmap_del(hashmap_t map, int key);
ssize_t hashmap_len(hashmap_t map);
hashmap_iter_t hashmap_iter_create(hashmap_t map);
void hashmap_iter_destroy(hashmap_iter_t *it);
struct hashmap_pair *hashmap_iter_next(hashmap_iter_t it);
int hashmap_iter_has_next(hashmap_iter_t it);
#endif
////
int _m_int_hash(int key)
{
    return key;
}
int _m_int_equal(int key1, int key2)
{
    return key1 == key2;
}
hashmap_t hashmap_create(hashmap_hs hs, hashmap_eq eq)
{
    return hashmap_create_for_all(hs, eq, HASHMAP_INIT_CAPA, HASHMAP_INIT_FACTOR);
}
static int _is_pair_equal(void *pair1, void *pair2)
{
    return pair1 == pair2;
}
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
static struct hashmap_pair *_hashmap_list_find(hashmap_t map, list_t list, int key)
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
static int _hashmap_resize(hashmap_t map)
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
int hashmap_add(hashmap_t map, int key, int value)
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
int hashmap_get_value(hashmap_t map, int key)
{
    if (!map)
        assert(!"cannot get it");
    int hash_code = map->hs(key);
    hash_code %= map->capacity;
    if (hash_code < 0)
        hash_code += map->capacity;
    struct hashmap_pair *pair = _hashmap_list_find(map, map->lists[hash_code], key);
    if (pair == NULL)
        assert(!"cannot get it");
    else
        return pair->value;
}
int hashmap_is_in(hashmap_t map, int key)
{
    if (!map)
        return -1;
    int hash_code = map->hs(key);
    hash_code %= map->capacity;
    if (hash_code < 0)
        hash_code += map->capacity;
    struct hashmap_pair *pair = _hashmap_list_find(map, map->lists[hash_code], key);
    return pair != NULL;
}
void hashmap_del(hashmap_t map, int key)
{
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
            //value = p->value;
            list_del(map->lists[hash_code], i);
            free(p);
            map->len--;
            break;
        }
        i++;
    }
    list_iter_destroy(&it);
    return;// value;
}
ssize_t hashmap_len(hashmap_t map)
{
    if (!map)
        return -1;
    return map->len;
}
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
void hashmap_iter_destroy(hashmap_iter_t *iter)
{
    assert(iter != NULL);
    assert((*iter) != NULL);
    free(*iter);
    iter = NULL;
}
int hashmap_iter_has_next(hashmap_iter_t iter)
{
    if (!iter)
        return -1;
    return iter->count < iter->map->len;
}
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
#endif
enum{ MAX_MAP_SZ = 16*4096};
hashmap_t g[MAX_MAP_SZ];
void init(){
    for(int i=0;i<MAX_MAP_SZ;i++)
        g[i] = hashmap_create(_m_int_hash, _m_int_equal);
}
void swap(int*nums, int i, int j) {
   int t   = nums[i];
   nums[i] = nums[j];
   nums[j] = t;
}
int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    init();
    edge*edges=NULL;int edgesSz=0;
    for (int i = 0; i < m; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        --u, --v;
        hashmap_add(g[u], v, edgesSz);
        edges=pushbackE(edges, &edgesSz, newEdge(u, v));
        hashmap_add(g[v], u, edgesSz);
        edges=pushbackE(edges, &edgesSz, newEdge(v, u));
    }
    Queue*q=CreateQueue(1000);
    char in_queue[n]; memset(in_queue,0,sizeof(in_queue));
    for (int i = 0; i < n; ++i){
        if(hashmap_len(g[i]) == 2){
            Enqueue(q, i);
            in_queue[i] = true;
        }
    }
    int ans = 0;
    while (!isEmptyQueue(q)){
        int v = Front(q);
        Dequeue(q);
        if( hashmap_len( g[v] ) != 2) {
            hashmap_iter_t mit;
            struct hashmap_pair *pair;
            mit  = hashmap_iter_create(g[v]);
            pair = hashmap_iter_next(mit);
            int it = pair->value;
            for (int mask = 0; mask < 4; ++mask) {
                if (mask == 3 && !edges[it].virt) {
                    continue;
                }
                ans = max(ans, edges[it].dp[mask] + (mask & 1) + ((mask >> 1) & 1));
            }
            break;
        }
        hashmap_iter_t mit2;
        struct hashmap_pair *pair2;
        struct hashmap_pair *pair3;
        mit2 = hashmap_iter_create(g[v]);
        pair2 = hashmap_iter_next(mit2);
        int x = pair2->key, a = pair2->value;
        hashmap_del(g[x], v);
        pair3 = hashmap_iter_next(mit2);
        int y = pair3->key, b = pair3->value;
        hashmap_del(g[y], v);
        if (x == y)
            break;
        int id;
        if(!hashmap_is_in(g[x], y) ){
            id = edgesSz;
            hashmap_add(g[x], y, edgesSz);
            edges=pushbackE(edges, &edgesSz, newEdge2(x, y, true));
            hashmap_add(g[y], x, edgesSz);
            edges=pushbackE(edges, &edgesSz, newEdge2(y, x, true));
        }
        else{
            id = hashmap_get_value(g[x], y);
        }
        if (hashmap_len(g[x]) == 2 && !in_queue[x]) {
            Enqueue(q, x);
            in_queue[x] = true;
        }
        if (hashmap_len(g[y]) == 2 && !in_queue[y]) {
            Enqueue(q, y);
            in_queue[y] = true;
        }
        for (int mask = 0; mask < 4; ++mask) {
            if (mask == 3 && !edges[id].virt)
                continue;
            int d = 0;
            for (int c = 0; c < 2; ++c) {
                if (c == 1 && (((mask & 1) && !edges[a].virt) || ((mask & 2) && !edges[b].virt)))
                    continue;
                int cnt = edges[a].dp[c + 2 * (mask & 1)] + edges[b].dp[c + 2 * ((mask >> 1) & 1)] + c;
                d = max(d, cnt);
            }
            edges[id].dp[mask] += d;
            ans = max(ans, edges[id].dp[mask] + (mask & 1) + ((mask >> 1) & 1));
//          printf("answer = %d\n", ans);
        }
        memcpy(edges[id ^ 1].dp, edges[id].dp, 4 * sizeof(int));
        swap(edges[id^1].dp, 1, 2);
    }
    printf("%d\n", ans);
}
