#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))

typedef long long ll;

#if 1 //que
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
#endif

typedef struct{
    int first;
    int second;
}Pair;
Pair newPair(int a, int b){
    Pair rez;
    rez.first =a;
    rez.second=b;
    return rez;
}
int cmpP(const void*pa, const void*pb){
  Pair*a = (Pair*)pa;
  Pair*b = (Pair*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
Pair*pushbackP(Pair *array, int *size, Pair value) {
    Pair *output = resizeArray(array, Pair, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
	Pair*ptr;
	int sz;
}vecp;
vecp newVecP(){
	vecp rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

#if 1 // hash map (Pair, int)
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
static list_t list_create(list_eq eq){
    if (!eq)
        return NULL;
    list_t list = (struct list*)calloc(1, sizeof(struct list));
    assert(list != NULL);
    list->head = list->tail = NULL;
    list->len = 0;
    list->eq = eq;
    return list;
}
static void list_destroy(list_t *list){
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
static int list_insert_at_tail(list_t list, void *data){
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
static list_iter_t list_iter_create(list_t list){
    list_iter_t it = (struct list_iter*)calloc(1, sizeof(struct list_iter));
    assert(it != NULL);
    it->p_node = list->head;
    it->count = 0;
    return it;
}
static void list_iter_destroy(list_iter_t *it){
    assert(it != NULL);
    assert((*it) != NULL);
    free(*it);
    *it = NULL;
}
static void *list_iter_next(list_iter_t it){
    if (it->p_node == NULL)
        return NULL;
    void *data = it->p_node->data;
    it->p_node = it->p_node->next;
    it->count++;
    return data;
}
#ifndef _HASHMAP_H_
#define _HASHMAP_H_
#include <stdio.h>
#define HASHMAP_INIT_CAPA       50
#define HASHMAP_INIT_FACTOR     0.75f
typedef int (*hashmap_hs)(Pair);
typedef int (*hashmap_eq)(Pair, Pair);
struct hashmap_pair {
    Pair key;
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
static int hashmap_add(hashmap_t map, Pair key, int value);
static int hashmap_get_value(hashmap_t map, Pair key);
static hashmap_iter_t hashmap_iter_create(hashmap_t map);
static void hashmap_iter_destroy(hashmap_iter_t *it);
static struct hashmap_pair *hashmap_iter_next(hashmap_iter_t it);
#endif
static int _m_int_hash(Pair key){
    return key.first + key.second;//todo fix
}
static int _m_int_equal(Pair key1, Pair key2){
    return cmpP(&key1, &key2)==0;
}
static hashmap_t hashmap_create(){
    hashmap_hs hs=_m_int_hash;
    hashmap_eq eq=_m_int_equal;
    return hashmap_create_for_all(hs, eq, HASHMAP_INIT_CAPA, HASHMAP_INIT_FACTOR);
}
static int _is_pair_equal(void *pair1, void *pair2){
    return pair1 == pair2;
}
static hashmap_t hashmap_create_for_all(hashmap_hs hs, hashmap_eq eq, size_t init_capacity, double init_factor){
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
static void hashmap_destroy(hashmap_t *map){
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
static struct hashmap_pair *_hashmap_list_find(hashmap_t map, list_t list, Pair key){
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
static int hashmap_add(hashmap_t map, Pair key, int value){
    if (!map)
        return -1;
    int hash_code = map->hs(key);
    hash_code %= map->capacity;
    if (hash_code < 0)
        hash_code += map->capacity;
    struct hashmap_pair *Pair = _hashmap_list_find(map, map->lists[hash_code], key);
    if (Pair == NULL) {
        Pair = (struct hashmap_pair*)calloc(1, sizeof(struct hashmap_pair));
        assert(Pair != NULL);
        Pair->key = key;
        Pair->value = value;
        list_insert_at_tail(map->lists[hash_code], Pair);
        map->len++;
        if (map->len > map->capacity * map->resize_factor) {
            _hashmap_resize(map);
        }
    }
    else {
        Pair->value = value;
    }
    return 0;
}
static int hashmap_get_value(hashmap_t map, Pair key){
    if (!map)
        return 0;//assert(!"cannot get it");
    int hash_code = map->hs(key);
    hash_code %= map->capacity;
    if (hash_code < 0)
        hash_code += map->capacity;
    struct hashmap_pair *Pair = _hashmap_list_find(map, map->lists[hash_code], key);
    if (Pair == NULL)
        return 0;//assert(!"cannot get it");
    else
        return Pair->value;
}
static hashmap_iter_t hashmap_iter_create(hashmap_t map){
    if (!map)
        return NULL;
    hashmap_iter_t iter = (struct hashmap_iter*)calloc(1, sizeof(struct hashmap_iter));
    iter->index = 0;
    iter->count = 0;
    iter->map = map;
    iter->p_node = map->lists[0]->head;
    return iter;
}
static void hashmap_iter_destroy(hashmap_iter_t *iter){
    assert(iter != NULL);
    assert((*iter) != NULL);
    free(*iter);
    iter = NULL;
}
static struct hashmap_pair *hashmap_iter_next(hashmap_iter_t iter){
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



typedef struct{
    int u;
    int v;
    int w;
}Edge;
Edge newEdge(int a, int b, int c){
    Edge rez;
    rez.u = a;
    rez.v = b;
    rez.w = c;
    return rez;
}
typedef struct{
    int t, a, b, x, r;
}Event;
Event newEvent(int t, int a, int b, int x, int r){
    Event rez;
    rez.t = t;
    rez.a = a;
    rez.b = b;
    rez.x = x;
    rez.r = r;
    return rez;
}
int cmpEvent(const void*pa, const void*pb){
    Event*a = (Event*)pa;
    Event*b = (Event*)pb;
    if(a->x != b->x) return a->x - b->x;
    if(a->a != b->a) return a->a - b->a;
    if(a->b != b->b) return a->b - b->b;
    if(a->r != b->r) return a->r - b->r;
    return a->t - b->t;
}

#define INF 1000000000000000000ll
int n, m, q;
vecp*adj;
Edge* Edges;
Event*E;
int inp_nextInt(){
    int x;
    scanf("%d", &x);
    return x;
}

///////////////////////////////////////////
void AddEdge(int u, int v, int w){
    adj[u].ptr = pushbackP(adj[u].ptr, &adj[u].sz, newPair(v, w));
    adj[v].ptr = pushbackP(adj[v].ptr, &adj[v].sz, newPair(u, w));
}
ll Compute(){
    n += q;
    ll*d= (ll*) calloc(n, sizeof(ll));
    adj = (vecp*) calloc(n, sizeof(vecp));
    for(int i=0; i<n; ++i){
        d[i] = INF;
        adj[i] = newVecP();
    }
    int*id =(int*) calloc(m, sizeof(int));
    int*le =(int*) calloc(m, sizeof(int));
    for(int i=0; i<m; ++i){
        id[i] = -1;
        le[i] =  0;
    }
    for(int i=0; i<q; ++i){
        int c = n - q + i;
        int p = E[i].r;
        if (id[p] == -1)
            AddEdge(E[i].a, c, E[i].x);
        else
            AddEdge(id[p], c, E[i].x - le[p]);
        id[p] = c;
        le[p] = E[i].x;
        d [c] = E[i].t;
    }
    for(int i=0; i<m; ++i){
        if(id[i] != -1)
            AddEdge(id[i], Edges[i].v, Edges[i].w - le[i]);
        else
            AddEdge(Edges[i].u, Edges[i].v, Edges[i].w);
    }
    Queue*Q = newQueue();
    bool*inQueue = (bool*) calloc(n, sizeof(bool));
    for(int i=0; i<n; ++i){
        inQueue[i] = false;
        if (d[i] < INF){
            push(Q, i);
            inQueue[i] = true;
        }
    }
    while (!empty(Q)){
        int u = front(Q); pop(Q); // pollFirst
        inQueue[u] = false;
        for(int z=0;z<adj[u].sz;z++){Pair e = adj[u].ptr[z];
            int v = e.first;
            int l = e.second;
            if (d[v] > d[u] + l){
                d[v] = d[u] + l;
                if (!inQueue[v]){
                    push(Q, v);
                    inQueue[v] = true;
                }
            }
        }
    }
    ll ans = 0;
    for(int i=0; i<n; ++i)
        ans = max(ans, d[i]);
    for(int u=0; u<n; ++u){
        for(int z=0;z<adj[u].sz;z++){Pair e = adj[u].ptr[z];
            int v = e.first;
            int l = e.second;
            ans = max((l + d[u] + d[v]) / 2, ans);
        }
    }
    return ans;
}
int main(){
    n     = inp_nextInt();
    m     = inp_nextInt();
    q     = inp_nextInt();
    Edges = (Edge*)  calloc(m, sizeof(Edge));
    E     = (Event*) calloc(q, sizeof(Event));
    hashmap_t M = hashmap_create();
    for(int i=0; i<m; ++i){
        int u = inp_nextInt() - 1;
        int v = inp_nextInt() - 1;
        int w = inp_nextInt() * 2;
        if(u > v){
            int tmp = u;
            u = v;
            v = tmp;
        }
        Edges[i] = newEdge(u, v, w);
        hashmap_add(M, newPair(u, v), i);
    }
    for(int i=0; i<q; ++i){
        int t = inp_nextInt() * 2;
        int a = inp_nextInt() - 1;
        int b = inp_nextInt() - 1;
        int x = inp_nextInt() * 2;
        bool rev = false;
        if(a > b){
            int tmp = a;
            a       = b;
            b       = tmp;
            rev     = true;
        }
        int p = hashmap_get_value(M, newPair(a, b));
        if(rev)
            x = Edges[p].w - x;
        E[i] = newEvent(t, a, b, x, p);
    }
    qsort(E, q, sizeof(Event), cmpEvent);
    printf("%f\n", Compute()/2.0);
    return 0;
}
