#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ MAXJ = 1000};
enum{ MAXD = 5};
enum{ INF  = 10000000};

typedef struct{
    int w;
    int len;
    int ang;
    int vnum;
}vertex_info;

typedef struct{
    int m;
    vertex_info edges[MAXD];
}vertex_input;
vertex_input input[MAXJ+1];

typedef struct edge{
    int    dest, len;
    struct edge*next;
}edge;
edge*newedge(int d, int l, edge*n){
    edge*rv = calloc(1, sizeof(edge));
    rv->dest = d;
    rv->len  = l;
    rv->next = n;
    return rv;
}

typedef struct{
    int  baseNum;
    edge*list;
    bool visited;
    int  dist;
}vertex;
vertex graph[MAXJ*MAXD];

typedef struct{
    int v;
    int dist;
}entry;
entry*mkentry(int v, int d){
    entry*rv=calloc(1, sizeof(entry));
    rv->v    = v;
    rv->dist = d;
    return rv;
}
int cmpE(void*a, void*b){
    entry*lhs=(entry*)a;
    entry*rhs=(entry*)b;
    return(lhs->dist > rhs->dist)?-1:1;
}

#if 1 // pq
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

PriorityQueue*pq;// of entry

void dijkstra(int src, int nV){
    for(int i=0; i<nV; i++) {
        graph[i].dist = INF;
        graph[i].visited = false;
    }
    graph[src].dist = 0;
    entry*e = mkentry(src, 0);
    push(pq, e);
    while(!empty(pq)){
        entry*tq = top(pq); entry e = *tq; pop(pq);
        if(graph[e.v].visited)
            continue;
        graph[e.v].visited = true;
        for(edge* p = graph[e.v].list; p != 0; p = p->next){
            int w = p->dest;
            int dist = graph[e.v].dist + p->len;
            if (dist < graph[w].dist){
                graph[w].dist = dist;
                entry*e2 = mkentry(w, dist);
                push(pq, e2);
            }
        }
    }
}
void addEdge(int v, int w, int len){
    graph[v].list = newedge(w, len, graph[v].list);
}
int findVertexNum(int w, int v){
    for(int j=0; j<input[w].m; j++)
        if (input[w].edges[j].w == v)
            return input[w].edges[j].vnum;
    exit(-1);
}
bool canUseEdge(int ang1, int ang2, int d1, int d2){
    if (ang1 > 360)
        ang1 -= 360;
    int upper = ang1+d1;
    if (upper >= 360)
        upper -= 360;
    int lower = ang1-d2;
    if (lower < 0)
        lower += 360;
    if (upper > lower)
        return (ang2 <= upper && ang2 >= lower);
    else
        return (ang2 <= upper || ang2 >= lower);
}
int main(){
    pq = newPriorityQueue(cmpE);
    int nVert, dest, a1, a2;
    scanf("%d %d %d %d", &nVert, &dest, &a1, &a2);
    int vnum = 1;
    for(int i=1; i<=nVert; i++){
        scanf("%d", &input[i].m);
        for(int j=0; j<input[i].m; j++){
            scanf("%d %d %d", &input[i].edges[j].w,
                              &input[i].edges[j].len,
                              &input[i].edges[j].ang);
            input[i].edges[j].vnum = vnum++;
        }
    }
    for(int i=1; i<=nVert; i++) {
        vertex_input inp = input[i];
        for(int j=0; j<inp.m; j++) {
            vertex_info inf = inp.edges[j];
            for(int k=0; k<inp.m; k++) {
                if (canUseEdge(inf.ang+180, inp.edges[k].ang, a1, a2)) {
                    int wnum = findVertexNum(inp.edges[k].w, i);
                    addEdge(inf.vnum, wnum, inp.edges[k].len);
                }
            }
        }
    }
    for(int j=0; j<input[1].m; j++) {
        int wnum = findVertexNum(input[1].edges[j].w, 1);
        addEdge(0, wnum, input[1].edges[j].len);
        addEdge(input[1].edges[j].vnum,0,0);
    }
    dijkstra(0, vnum);
    int*saveDists = calloc(input[dest].m, sizeof(int));
    for(int j=0; j<input[dest].m; j++){
        int w = input[dest].edges[j].vnum;
        saveDists[j] = graph[w].dist;
    }
    int minDist = INF;
    for(int j=0; j<input[dest].m; j++){
        dijkstra(input[dest].edges[j].vnum, vnum);
        if(saveDists[j] + graph[0].dist < minDist)
            minDist = saveDists[j] + graph[0].dist;
    }
    if(minDist < INF)
        printf("%d\n", minDist);
    else
        puts("impossible");
    return 0;
}
