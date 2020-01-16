#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define swap(a,b) do{ __typeof(a) tp; tp = a; a = b; b = tp; }while(0)
typedef struct{
  int first, second;
}pair;

int compP(void*pb, void*pa){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}
pair*mkpair(int a, int b){
  pair*rez = malloc(sizeof(pair));
  rez->first  = a;
  rez->second = b;
  return rez;
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
typedef long long ll;
enum{ N = 30007 };
enum{ M = 100007};
#define inf 100000000000000LL

int head[N],head2[N],p=1;
typedef struct Rec{
    int go,nex;
    ll c;
}Rec;
Rec eg[M*2],e[M*2];

void build(int a, int b, ll c){
    eg[++p]=(Rec){b,head[a],-c};
    head[a]=p;
    eg[++p]=(Rec){a,head[b],0};
    head[b]=p;
}
ll dis[N],ans;
int Q[N],s[N],S,T,stop;

bool bfs(){
    memset(dis,0,sizeof(dis));
    dis[T]=1;
    Q[1]=T;
    for (int p1=1,p2=1;p1<=p2;p1++){
        for (int i=head[Q[p1]];i;i=eg[i].nex)
            if (eg[i^1].c<0&&!dis[eg[i].go]){
                dis[eg[i].go]=dis[Q[p1]]+1;
                Q[++p2]=eg[i].go;
            }
    }
    if (!dis[S])
        return false;
    memcpy(head2,head,sizeof(head));
    return true;
}
bool dinic(int p, int top){
    if (p==T){
        ll x=inf;
        for(int i=1;i<=top-1;i++)
            if(-eg[s[i]].c<x)
                x=-eg[s[i]].c,stop=i;
        for(int i=1;i<=top-1;i++)
            eg[s[i]].c+=x,eg[s[i]^1].c-=x;
        ans+=x;
        return true;
    }
#define i head2[p]
    for(; i; i = eg[i].nex){
        if(eg[i].c<0&&dis[eg[i].go]==dis[p]-1){
            s[top] = i;
            if(dinic(eg[i].go,top+1)&&top!=stop)
                return true;
        }
    }
    #undef i
    return false;
}
ll ask(){
    ans=0;
    while(bfs())
        dinic(S,1);
    return ans;
}
void init(int _S,int _T){
    S=_S,T=_T;
}

void clear(){
    p=1;
    memset(head,0,sizeof(head));
}
int n,m,ss,tt,why=0;
ll diss[N];

void addedge(int a, int b, ll c){
    p++;
    e[p].go=b;
    e[p].c=c;
    e[p].nex=head[a];
    head[a]=p;
}
void dijkstra(){
    PriorityQueue*q = newPriorityQueue(compP); // of pair rev
    for(int i=1; i<=n; i++)
        diss[i]=inf;
    diss[1]=0;
    push(q, mkpair(0,1));
    while(!empty(q)){
        pair*tq=top(q); int now = tq->second; pop(q);
        for(int i=head[now]; i; i=e[i].nex){
            if(diss[now]+e[i].c<diss[e[i].go]){
                diss[e[i].go]=diss[now]+e[i].c;
                push(q, mkpair(diss[e[i].go], e[i].go));
            }
        }
    }
}
int u[M],v[M],w[M],pos[M],c;

void solve(int l, int r){
    clear();
    ss=n+1;
    tt=n+2;
    init(ss,tt);
    for(int i = 1; i <= m; i++)
        build(u[i], v[i], 1);
    for(int i = l; i <= r; i++)
        build(pos[i], tt, 1);
    build(ss, 1, r - l + 1);
    why += ask();
}
int cmp_(const void*pa, const void*pb){
    int*a=(int*)pa;
    int*b=(int*)pb;
    return(diss[*a] < diss[*b])?-1:1;
}
int main(){
    scanf("%d %d %d", &n, &m, &c);
    p=0;
    for(int i=1; i<=m; i++)
        scanf("%d %d %d", &u[i], &v[i], &w[i]);
    for(int i=1; i<=c; i++)
        scanf("%d", &pos[i]);
    for(int i=1; i<=m; i++)
        addedge(u[i], v[i], w[i]), addedge(v[i], u[i], w[i]);
    dijkstra();
    int tmp = 0;
    for(int i=1; i<=m; i++){
        if(diss[u[i]] > diss[v[i]])
            swap(u[i], v[i]);
        if(diss[v[i]] == diss[u[i]] + w[i]){
            ++tmp;
            swap(u[i], u[tmp]);
            swap(v[i], v[tmp]);
            swap(w[i], w[tmp]);
        }
    }
    m = tmp;
    qsort(pos+1, c, sizeof(int), cmp_);
    for(int i=1, j; i<=c; i=j){
        j = i;
        while(diss[pos[i]] == diss[pos[j]] && j <= c)
            j++;
        if(diss[pos[i]]==inf)
            break;
        solve(i, j - 1);
    }
    printf("%d\n", why);
    return 0;
}
