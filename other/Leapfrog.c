#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;

#define pb(zpv, zvv) zpv.ptr = pushbackN(zpv.ptr, &zpv.sz, zvv)

#define int ll
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
void mapFree(hashmap_t *map);
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
void mapFree(hashmap_t *map){
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
#undef int


typedef struct Node{
    ll si,ssi,num;
}Node;

Node newNode(ll a, ll b, ll c){
    return(Node){a,b,c};
}

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
Node*pushbackN(Node*array, int *size, Node value){
  Node*output = resizeArray(array, Node, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	Node*ptr;
	int sz;
}vecn;
vecn newVecN(){
	vecn rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}


int cmpN(const void*pa, const void*pb){
    Node*a=(Node*)pa;
    Node*b=(Node*)pb;
    return a->si < b->si;
};
ll ss [45],
   dis[45],
   s  [45];
hashmap_t mp;
hashmap_t mp_;
ll cnt=0;
vecn remain[45];//of Node
ll ans=9223372036854775807ll,sum=0ll,sum_=0ll;
ll p [45],
   a [45],
   aa[45];

void exgcd(ll a, ll b, ll*d, ll*x, ll*y){
    if(!b){
       *d=a;
       *x=1;
       *y=0;
    }
    else{
        exgcd(b, a%b, d, y, x);
        (*y) -= (*x) * (a/b);
    }
}
ll CRT(){
    ll P=p[1],A=a[1],t;
    for(ll i=2;i<=cnt;i++){
        ll d,x,y;
        exgcd(P, p[i], &d, &x, &y);
        if((a[i]-A)%d)
            return -1;
        x*=(a[i]-A)/d,t=p[i]/d,x=(x%t+t)%t;
        A=P*x+A,P=P/d*p[i],A%=P;
    }
    A=(A%P+P)%P;
    for(ll i=1;i<=cnt;i++){
        if(A<aa[i])
            A+=(aa[i]-A)/P*P;
        while(A<aa[i])
            A+=P;
    }
    return A;
}
void dfs(ll x){
    if(x==0){
        ll tmp=CRT();
        if(sum>sum_)
            sum_=sum,ans=tmp;
        if(sum==sum_&&tmp<ans)
            ans=tmp;
        return;
    }
    for(ll i=0; i<remain[x].sz; i++){
        a[x]  = remain[x].ptr[i].si;
        p[x]  = mapGet(mp_, x);
        aa[x] = remain[x].ptr[i].ssi;
        sum  += remain[x].ptr[i].num;
        dfs(x-1);
        sum -= remain[x].ptr[i].num;
    }
}
int main(){
    mp  = newMap(_m_int_hash, _m_int_equal);
    mp_ = newMap(_m_int_hash, _m_int_equal);
    ll n;
    scanf("%lld", &n);
    for(ll i=1; i<=n; i++){
        scanf("%lld%lld", &ss[i], &dis[i]), s[i]=ss[i]%dis[i];
        if(!mapHas(mp, dis[i])){
            mapPut(mp, dis[i], ++cnt);
            mapPut(mp_, cnt, dis[i]);
        }
        int ri=mapGet(mp, dis[i]);
        pb(remain[ri], newNode(s[i],ss[i],1));
    }
    for(ll i=1; i<=cnt; i++){
        qsort(remain[i].ptr, remain[i].sz, sizeof(Node), cmpN);
        for(ll j=1; j<remain[i].sz; j++){
            if(remain[i].ptr[j].si  == remain[i].ptr[j-1].si)
               remain[i].ptr[j].num += remain[i].ptr[j-1].num;
        }
    }
    dfs(cnt);
    printf("%lld %lld\n", ans, sum_);
    return 0;
}
