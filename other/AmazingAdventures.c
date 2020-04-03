#pragma GCC optimize "-O3" // https://open.kattis.com/problems/amazingadventures
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

#define pb(zpv, zvv) zpv.ptr = pushback(zpv.ptr, &zpv.sz, zvv)
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


#define fill(arr, sz, val)do{     \
  for(int i=0; i<sz; i++)         \
    arr[i] = val;                 \
}while(0)

typedef struct{
  int first, second;
}pair;
pair newpair(int a, int b){
  return(pair){a,b};
}
pair*mkpair(int a, int b){
  pair*rv=calloc(1, sizeof(pair));
  rv->first =a;
  rv->second=b;
  return rv;
}

int cmpP(void*pb, void*pa){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
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
#endif
//////////////////////
enum{Maxn=205      };
enum{Maxm=205      };
enum{INF=0x3f3f3f3f};
const int dx[4]={-1,1,0,0};
const int dy[4]={0,0,-1,1};

typedef struct{
    int to, cap, cost, rev;
    bool isrev;
}Edge;
Edge newedge(int t, int c, int o, int r, bool i){
    return(Edge){t, c, o, r, i};
}
#define pbe(zpv, zvv) zpv.ptr = pushbackE(zpv.ptr, &zpv.sz, zvv)
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

////////////////////////////////////////
int n,m;
int  dist[Maxn*Maxm];
bool used[Maxn*Maxm];
vece G[Maxn*Maxm];//of Edge
pair f[Maxn*Maxm];

void add_edge(int from, int to, int cap, int cost){
   pbe(G[from], newedge(to,cap,cost, (int)G[to  ].sz  ,0));
   pbe(G[to  ], newedge(from,0,-cost,(int)G[from].sz-1,1));
}
int min_cost(int s, int t){
    PriorityQueue*q = newPriorityQueue(cmpP);//of pair rev
    fill(f, 2*n*m, newpair(-1,-1));
    fill(dist, 2*n*m, INF);
    dist[s]=0;
    push(q, mkpair(0,s));
    while(!empty(q)){
        pair*tq=top(q);
        int cost = tq->first;
        int u    = tq->second; pop(q);
        if(u==t||cost>dist[u])
            continue;
        for(int i=0;i<G[u].sz;i++)
        if(G[u].ptr[i].cap>0){
            int v=G[u].ptr[i].to;
            if(cost+G[u].ptr[i].cost<dist[v]){
                dist[v]=cost+G[u].ptr[i].cost;
                f[v]=newpair(u,i);
                push(q, mkpair(dist[v], v));
            }
        }
    }
    int now=t;
    while(now!=s){
        int v=f[now].first,
          num=f[now].second;
        if(v<0)
            return-1;
        G[v].ptr[num].cap--;
        G[now].ptr[G[v].ptr[num].rev].cap++;
        now=v;
    }
    return dist[t];
}
int main(){
    while(scanf("%d%d",&n,&m),n!=0,m!=0){
        for(int i=0;i<2*n*m;i++){
            used[i]=0;
            G[i].sz=0;
        }
        int rb,cb,rc,cc,rg,cg,ru,cu;
        scanf("%d%d%d%d%d%d%d%d", &rb,&cb,&rc,&cc,&rg,&cg,&ru,&cu);
        rb--,cb--,rc--,cc--,rg--,cg--,ru--,cu--;
        rb=n-1-rb; rc=n-1-rc; rg=n-1-rg; ru=n-1-ru;
        int b=rb*m+cb+n*m, c=rc*m+cc+n*m, g=rg*m+cg+n*m, u=ru*m+cu+n*m;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                int loc=i*m+j;
                if(loc!=u-n*m)
                    add_edge(loc,loc+n*m,1,0);
                for(int k=0;k<4;k++){
                    int nowx=i+dx[k],
                        nowy=j+dy[k];
                    if(nowx<0||nowy<0||nowx==n||nowy==m)
                        continue;
                    add_edge(loc+n*m, nowx*m+nowy,1,1);
                }
            }
        }
        if(min_cost(c,g)<0||
           min_cost(c,b)<0){
            printf("NO\n");
            continue;
        }
        vec id=newVec();
        int now=b;
        while(now!=c){
            now%=n*m;
            used[now]=1;
            pb(id, now);
            for(int z=0;z<G[now].sz;z++){Edge e=G[now].ptr[z];
                if(e.cap&&e.isrev){
                    now=e.to;
                    break;
                }
            }
        }
        while(now!=g){
            pb(id, now%(n*m));
            for(int z=0;z<G[now].sz;z++){Edge e=G[now].ptr[z];
                if(e.cap==0&&!e.isrev&&!used[e.to]){
                    now=e.to;
                    break;
                }
            }
            now+=n*m;
        }
        pb(id, now%(n*m));
        printf("YES\n");
        for(int i=0;i<id.sz-1;i++){
            int nowx=id.ptr[i]/m,
                nowy=id.ptr[i]%m;
            int nxtx=id.ptr[i+1]/m,
                nxty=id.ptr[i+1]%m;
            if(nxtx-nowx==1)printf("D");
            if(nowx-nxtx==1)printf("U");
            if(nxty-nowy==1)printf("R");
            if(nowy-nxty==1)printf("L");
        }
        printf("\n");
    }
    return 0;
}
