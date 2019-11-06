#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
typedef long double ld;
ld const inf=1e60L;
int n;

typedef struct{
  ll  first;
  int second;
}pli;
pli newpli(ll a, int b){
  return(pli){a,b};
}
pli*mkpli(ll a, int b){
  pli*rv=calloc(1, sizeof(pli));
  rv->first  = a;
  rv->second = b;
  return rv;
}
int cmpP(void*pa, void*pb){
  pli*a = (pli*)pa;
  pli*b = (pli*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
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

typedef struct Edge{
  int  s,t;
  ll   cap;
  ld   cost;
  struct Edge*rev;
}Edge;
Edge Edge_E[500*500*2];
int  Edge_N;
typedef Edge* Edgep;

#define pb(zpv, zvv) zpv.ptr = pushbackE(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
Edgep*pushbackE(Edgep*array, int *size, Edgep value){
  Edgep*output = resizeArray(array, Edgep, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	Edgep*ptr;
	int sz;
}vece;
vece newVecE(){
	vece rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}


vece   edge[500*500*2]; // of Edgep
bool   done[500*500*2];
Edgep  from[500*500*2];
ld     dist[500*500*2],
       pot [500*500*2];

void add_edge(int s,int t,ll cap,ld cost){
  Edge_E[Edge_N] = (Edge){s,t,cap,cost,Edge_E+Edge_N+1};
  pb(edge[s], Edge_E+Edge_N++);
  Edge_E[Edge_N]=(Edge){t,s, 0,-cost,Edge_E+Edge_N-1};
  pb(edge[t], Edge_E+Edge_N++);
}
ld augment(){
  for (int i=n; i--;)
    done[i]=from[i]=0, dist[i]=inf;
  PriorityQueue*todo = newPriorityQueue(cmpP);//of pli
  for(push(todo, mkpli(dist[0]=0, 0)); !empty(todo);){
    pli*tq=top(todo); int x = tq->second; pop(todo);
    if(done[x])
      continue;
    else
      done[x]=true;
    for(int z=0;z<edge[x].sz;z++){Edge*y = edge[x].ptr[z];
      if(y->cap)
        for(ld d=dist[x]+y->cost+pot[x]-pot[y->t]; d+1e-10L<dist[y->t] && ! done[y->t]; ++d)
          push(todo, mkpli(-d,y->t)),
          from[y->t]=y,
          dist[y->t]=d;
    }
  }
  for(int i=n; i--;)
    pot[i] = fminl(inf, pot[i]+dist[i]);
  if(!from[1])
    return inf;
  ld cost=0;
  for(int x=1; x; x=from[x]->s)
    cost+=from[x]->cost, from[x]->cap--, from[x]->rev->cap++;
  return cost;
}
ld mcmf(int reps){
  ld res=0;
  for (int i=n; i--;)
    pot[i]=0;
  while (reps-->0)
    res+=augment();
  return res;
}
int main(){
  ll sn,tn,q;
  scanf("%d %lld %lld %lld", &n, &sn, &tn, &q);
  static ll hill[500][3];
  for (int i=0; i<n; i++)
    for (int j=0; j<3; j++)
      scanf("%lld", &hill[i][j]);
  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      if(hill[j][2]<hill[i][2] &&
        (hill[j][0]-hill[i][0])*(hill[j][0]-hill[i][0])+
        (hill[j][1]-hill[i][1])*(hill[j][1]-hill[i][1])+
        (hill[j][2]-hill[i][2])*(hill[j][2]-hill[i][2])<=q*q){
        add_edge(i+2,j+2,sn+tn,hypotl(hypotl(hill[j][0]-hill[i][0],hill[j][1]-hill[i][1]),hill[j][2]-hill[i][2]));
      }
    }
  }
  for(int i=0; i<sn; i++){int x; scanf("%d", &x); ++x; add_edge(0,x,1,0);}
  for(int i=0; i<tn; i++){int x; scanf("%d", &x); ++x; add_edge(x,1,1,0);}
  n += 2;
  ld cost = mcmf(tn);
  if(cost<inf)
    printf("%.8Lf\n", cost);
  else
    puts("IMPOSSIBLE");
  return 0;
}
