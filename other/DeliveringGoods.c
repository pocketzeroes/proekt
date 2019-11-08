#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
typedef long long ll;
enum{ N = 5010  };
enum{ M = 300100};
const ll INF = 0x3ffffffffffffffLL;

void fill(ll*arr, int sz, ll val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}

typedef struct Edge{
    int         node;
    ll          len;
    struct Edge*next;
}Edge;
Edge m_edge[M];
Edge*head[N];
int Ecnt,flag[N];
ll dist[N],dist2[N];

typedef struct Node{
    int         node;
    struct Node*next;
}Node;
Node m_node[M];
int girl[N],tick[N],Ncnt;
Node*Ver[N];
int C[N];

void init(){
    Ecnt = Ncnt = 0;
    clr(head);
    clr(Ver);
}
void mkEdge(int a, int b, ll c){
    m_edge[Ecnt].node = b;
    m_edge[Ecnt].len = c;
    m_edge[Ecnt].next = head[a];
    head[a] = m_edge+Ecnt++;
}
void mkNode(int b, int g){
    m_node[Ncnt].node = g;
    m_node[Ncnt].next = Ver[b];
    Ver[b] = m_node+Ncnt++;
}
typedef struct{
    int u;
    ll  d;
}hip;
hip*mkhip(ll d, int u){
    hip*rv=calloc(1, sizeof(hip));
    rv->d = d;
    rv->u = u;
    return rv;
}
int cmpH(void*pa, void*pb){
    hip*t=(hip*)pa;
    hip*a=(hip*)pb;
    return(t->d > a->d)?-1:1;
}
#if 1 // p_q
#ifndef __HEAP_H_GUARD__
#define __HEAP_H_GUARD__
#define HEAP_STARTING_SIZE 256
struct heap_st;
typedef struct heap_st PriorityQueue;
PriorityQueue* newPriorityQueue(signed(*)(void*, void*));
int   push(PriorityQueue*, void*);
void* top(PriorityQueue*);
void* pop(PriorityQueue*);
void delPriorityQueue(PriorityQueue**, void(*)(void*));
#endif
struct heap_st {
  void** info;
  signed(*compareFunction)(void*, void*);
  unsigned used;
  unsigned currentSize;
};
PriorityQueue* newPriorityQueue(signed(*compareFunction)(void*, void*)) {
  PriorityQueue* newHeap = (PriorityQueue*)malloc(sizeof(PriorityQueue));
  if (newHeap == NULL) {
    return NULL;
  }
  newHeap->info = (void**)malloc(HEAP_STARTING_SIZE * sizeof(void*));
  if (newHeap->info == NULL) {
    free(newHeap);
    return NULL;
  }
  newHeap->used = 0;
  newHeap->currentSize = HEAP_STARTING_SIZE;
  newHeap->compareFunction = compareFunction;
  return newHeap;
}
int  push(PriorityQueue* h, void* data) {
  if (h == NULL) {
    return 0;
  }
  if (h->used == 0) {
    h->info[0] = data;
    h->used = 1;
    return 1;
  }
  if (h->used == h->currentSize) {
    unsigned newSize = h->currentSize * 2;
    void** newIndexes = (void**)realloc(h->info, newSize * sizeof(PriorityQueue));
    if (newIndexes == NULL) {
      return 0;
    }
    h->info = newIndexes;
    h->currentSize = newSize;
  }
  h->info[h->used] = data;
  unsigned index, parentIndex;
  index = h->used;
  do {
    parentIndex = (index - 1) / 2;
    if (h->compareFunction(data, h->info[parentIndex]) > 0) {
      h->info[index] = h->info[parentIndex];
      h->info[parentIndex] = data;
      index = parentIndex;
    }
    else {
      break;
    }
  } while (parentIndex != 0);
  h->used++;
  return 1;
}
void*top(PriorityQueue*h) {
  if (h == NULL || h->used == 0) {
    return NULL;
  }
  return h->info[0];
}
void*pop(PriorityQueue*h) {
  if (h == NULL || h->used == 0) {
    return NULL;
  }
  void* toRet = h->info[0];
  if (h->used == 1) {
    h->info[0] = NULL;
    h->used--;
    return toRet;
  }
  h->used--;
  h->info[0] = h->info[h->used];
  h->info[h->used] = NULL;
  unsigned left, right, current = 0, index;
  do {
    index = current;
    left = (current * 2) + 1;
    right = (current * 2) + 2;
    if (left < h->used && h->compareFunction(h->info[left], h->info[current]) > 0) {
      if (right < h->used && h->compareFunction(h->info[right], h->info[current]) > 0 &&
        h->compareFunction(h->info[right], h->info[left]) > 0) {
        current = right;
      }
      else {
        current = left;
      }
    }
    else if (right < h->used && h->compareFunction(h->info[right], h->info[current]) > 0) {
      current = right;
    }
    if (current != index) {
      void* swap = h->info[current];
      h->info[current] = h->info[index];
      h->info[index] = swap;
    }
  } while (index != current);
  return toRet;
}
void delPriorityQueue(PriorityQueue** h, void(*freeFunction)(void*)) {
  if (h == NULL || *h == NULL) {
    return;
  }
  if (freeFunction != NULL) {
    unsigned i;
    for (i = 0; i < (*h)->used; ++i) {
      freeFunction((*h)->info[i]);
    }
  }
  free((*h)->info);
  free((*h));
  *h = NULL;
}
int size(PriorityQueue*h) {
  return h->used;
}
bool empty(PriorityQueue*h){
  return h->used==0;
}
#endif///////////////////////////////////////////

void dijkstra(int s, ll*dist){
    PriorityQueue*Q=newPriorityQueue(cmpH);//of hip
    fill(dist, N, INF);
    clr(flag);
    dist[s] = 0;
    push(Q, mkhip(0,s));
    while(!empty(Q)){
        hip*tq=top(Q); hip x = *tq; pop(Q);
        int u = x.u;
        if(flag[u])
            continue;
        flag[u] = 1;
        for(Edge*p = head[u]; p; p=p->next){
            int v = p->node;
            if(dist[v] > dist[u]+p->len){
               dist[v] = dist[u]+p->len;
               push(Q, mkhip(dist[v],v));
            }
        }
    }
}
bool find(int x){
    for(Node*p = Ver[x]; p; p=p->next){
        int s = p->node;
        if(!tick[s]){
            tick[s] = 1;
            if(girl[s] == 0||find(girl[s])){
                girl[s] = x;
                return true;
            }
        }
    }
    return false;
}
void Build(int n, int c){
    for(int i=0; i<c; ++i){
        dijkstra(C[i],dist2);
        for(int j=0; j<c; ++j){
            if(i != j && dist2[C[j]] != INF && dist[C[i]]+dist2[C[j]] == dist[C[j]]){
                mkNode(C[i],C[j]+n);
            }
        }
    }
}
int solve(int n, int c){
    Build(n, c);
    int cnt = 0;
    clr(girl);
    for(int i=0; i<c; ++i){
        clr(tick);
        if(find(C[i]))
            cnt++;
    }
    return cnt;
}
int main(){
    int n,m,c,cas = 0;
    while(~scanf("%d%d%d", &n, &m, &c) && n && m && c){
        init();
        for(int i=0; i<c; ++i)
            scanf("%d",&C[i]);
        int a, b;
        ll  d;
        for(int i=0; i<m; ++i){
            scanf("%d %d %lld", &a, &b, &d);
            mkEdge(a, b, d);
        }
        dijkstra(0, dist);
        printf("%d\n", c-solve(n, c));
    }
    return 0;
}
