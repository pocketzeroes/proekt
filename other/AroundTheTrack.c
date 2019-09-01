#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

#if 1 // pq
#ifndef __HEAP_H_GUARD__
#define __HEAP_H_GUARD__
#define HEAP_STARTING_SIZE 256
struct heap_st;
typedef struct heap_st PriorityQueue;
PriorityQueue* newPriorityQueue(int(*)(void*, void*));
int   push(PriorityQueue*, void*);
void* top(PriorityQueue*);
void* pop(PriorityQueue*);
void delPriorityQueue(PriorityQueue**, void(*)(void*));
#endif
struct heap_st {
  void** info;
  int(*compareFunction)(void*, void*);
  unsigned used;
  unsigned currentSize;
};
PriorityQueue* newPriorityQueue(int(*compareFunction)(void*, void*)) {
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

typedef struct snode{
    int    x, y;
struct snode*connections[4];
    int    numConnections;
}snode;
snode nodes[10000];
int numNodes;

typedef struct{
    snode* node;
    double penalty;
}scon;
scon*mkscon(snode*node, double penalty){
    scon*rv=calloc(1, sizeof(scon));
    rv->node=node;
    rv->penalty=penalty;
    return rv;
}
int cmpS(void*pa, void*pb){
    scon*lhs=(scon*)pa;
    scon*rhs=(scon*)pb;
    return(lhs->penalty > rhs->penalty)?-1:1;
}

double AngleDiff(int x1, int y1, int x2, int y2, int x3, int y3){
    x1 -= x2;
    y1 -= y2;
    x3 -= x2;
    y3 -= y2;
    double angleDiff = atan2((double)y1, (double)x1) - atan2((double)y3, (double)x3);
    if     (angleDiff >= M_PI) angleDiff = 2*M_PI - angleDiff;
    else if(angleDiff <=-M_PI) angleDiff = 2*M_PI + angleDiff;
    else if(angleDiff < 0    ) angleDiff = -angleDiff;
    return M_PI - angleDiff;
}
double GetAngleDiff(snode*n, snode*prev, snode* next){
    double ret;
    ret = AngleDiff(prev->x, prev->y, n->x, n->y, next->x, next->y);
    if(n->numConnections == 4){
        snode* p = 0;
        snode* q = 0;
        for(int i = 0; i < 4; ++i){
            if(n->connections[i] != prev && n->connections[i] != next){
                if(p){
                    q = n->connections[i];
                    break;
                }
                p = n->connections[i];
            }
        }
        double angleDiff = AngleDiff(p->x, p->y, n->x, n->y, q->x, q->y);
        ret += angleDiff;
    }
    return ret;
}
double RemoveConnections(snode*n, snode* prev, snode* next){
    if(n->numConnections == 2){
       n->numConnections = 0;
       return 0;
    }
    snode* p = 0;
    snode* q = 0;
    for(int i = 0; i < 4; ++i){
        if(n->connections[i] != prev && n->connections[i] != next){
            if(p){
                q = n->connections[i];
                break;
            }
            p = n->connections[i];
        }
    }
    double ret1, ret2;
    ret1  = AngleDiff(prev->x, prev->y, n->x, n->y, p->x, p->y);
    ret1 += AngleDiff(q->x, q->y, n->x, n->y, next->x, next->y);
    ret2  = AngleDiff(prev->x, prev->y, n->x, n->y, q->x, q->y);
    ret2 += AngleDiff(p->x, p->y, n->x, n->y, next->x, next->y);
    n->connections[0] = p;
    n->connections[1] = q;
    n->numConnections = 2;
    return fmin(ret1, ret2);
}
int main(){
    int numEdges;
    scanf("%d %d", &numNodes, &numEdges);
    for(int i = 0; i < numNodes; ++i){
        scanf("%d %d", &nodes[i].x, &nodes[i].y);
        nodes[i].numConnections = 0;
    }
    for(int i = 0; i < numEdges; ++i){
        int a, b;
        scanf("%d %d", &a, &b);
        nodes[a].connections[nodes[a].numConnections++] = &nodes[b];
        nodes[b].connections[nodes[b].numConnections++] = &nodes[a];
    }
    double ret = 0.;
    PriorityQueue*pq=newPriorityQueue(cmpS);//of scon
    push(pq, mkscon(&nodes[0], 0));
    while(!empty(pq)){
        scon*tq = top(pq); scon conn = *tq; pop(pq);
        snode*start = conn.node;
        if(start->numConnections == 0)
            continue;
        ret += conn.penalty;
        snode*next = start;
        snode*cur = start->connections[0];
        snode*startPrev = cur;
        do{
            snode*prev = cur;
            cur = next;
            double bestAngleDiff = 100000.;
            for(int j = 0; j < cur->numConnections; ++j){
                if(cur->connections[j] == prev)
                    continue;
                double diff = GetAngleDiff(cur, prev, cur->connections[j]);
                if(diff < bestAngleDiff){
                    bestAngleDiff = diff;
                    next = cur->connections[j];
                }
            }
            double angleDiff = AngleDiff(prev->x, prev->y, cur->x, cur->y, next->x, next->y);
            ret += angleDiff;
            double penalty = RemoveConnections(cur, prev, next);
            if(cur->numConnections > 0){
                penalty -= bestAngleDiff;
                push(pq, mkscon(cur, penalty));
            }
        }while(next != start || cur != startPrev);
    }
    printf("%.6lf\n", ret);
    return 0;
}
