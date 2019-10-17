#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ MAX_H = 200};
enum{ MAX_W = 200};
enum{ maxClimb = 1000};
double dryingPeriod = 1.;

typedef struct{ // pos
  int x, y;
  double t;
}pos;
pos newpos(int x, int y, double t){
  return(pos){x,y,t};
}
pos*mkpos(int x, int y, double t){
  pos*rv = calloc(1, sizeof(pos));
  rv->x=x;
  rv->y=y;
  rv->t=t;
  return rv;
}
int compP(void*pa, void*pb){
  pos*lhs=(pos*)pa;
  pos*rhs=(pos*)pb;
  return(lhs->t < rhs->t)?-1:1;
}
int compPr(void*pb, void*pa){
  pos*lhs=(pos*)pa;
  pos*rhs=(pos*)pb;
  return(lhs->t < rhs->t)?-1:1;
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

//////////////
double a, m;
int    w, h;
int    mapZ     [MAX_H][MAX_W];
double dryTime  [MAX_H][MAX_W];  
double wetTime  [MAX_H][MAX_W];  
double enterTime[MAX_H][MAX_W];
double leaveTime[MAX_H][MAX_W];
int dxs[4] = {1,-1,0,0};
int dys[4] = {0,0,1,-1};

void shortestPathOut(pos*start){
  PriorityQueue*pq=newPriorityQueue(compPr);//of pos rev
  push(pq, start);
  while(!empty(pq)){
    pos*tq = top(pq); pos p = *tq; pop(pq);
    for(int i=0; i<4; ++i){
      int x = p.x + dxs[i];
      int y = p.y + dys[i];
      if(x < 0 || x >= w || y < 0 || y >= h)
        continue;
      int zDiff = mapZ[p.y][p.x] - mapZ[y][x];
      if(abs(zDiff) > maxClimb)
        continue;
      double nextTime = fmax(p.t, dryTime[y][x]) + m;
      if(nextTime > wetTime[y][x])
        continue;
      if(nextTime < enterTime[y][x]){
        enterTime[y][x] = nextTime;
        push(pq, mkpos(x,y,nextTime));
      }
    }
  }
}
void shortestPathBack(pos*start){
  PriorityQueue*pq=newPriorityQueue(compP);//of pos
  push(pq, start);
  while(!empty(pq)){
    pos*tq = top(pq); pos p = *tq; pop(pq);
    for(int i = 0; i < 4; ++i){
      int x = p.x + dxs[i];
      int y = p.y + dys[i];
      if(x < 0 || x >= w || y < 0 || y >= h)
        continue;
      int zDiff = mapZ[p.y][p.x] - mapZ[y][x];
      if(abs(zDiff) > maxClimb)
        continue;
      double nextTime = fmin(p.t, wetTime[y][x]) - m;
      if(nextTime < dryTime[y][x])
        continue;
      if(nextTime > leaveTime[y][x]){
        leaveTime[y][x] = nextTime;
        push(pq, mkpos(x,y,nextTime));
      }
    }
  }
}
double calcDist(int dx, int dy){
  return sqrt((double)dx*dx + dy*dy);
}
int main(){
  scanf("%lf %lf", &a, &m);
  a *= 1000.0;
  m /= 3600.0;
  pos start = newpos(0, 0, 0.0);
  scanf("%d%d%d%d", &w, &h, &start.x, &start.y);
  pos stop = start;
  stop.t = 12.0;
  for(int y = 0; y < h; ++y){
    for(int x = 0; x < w; ++x){
      int z;
      scanf("%d", &z);
      mapZ[y][x] = z;
      if(z <= a){
        double t = acos((2.0*z)/a-1)*6/M_PI;
        dryTime[y][x] = t + dryingPeriod;
        wetTime[y][x] = 12 - t;
      }
      else{
        dryTime[y][x] = -2;
        wetTime[y][x] = 14;
      }
      enterTime[y][x] = 12;
      leaveTime[y][x] = 0;
    }
  }
  enterTime[start.y][start.x] = 0;
  leaveTime[start.y][start.x] = 12;
  shortestPathOut (&start);
  shortestPathBack(&stop );
  double ret = 0;
  for(int y = 0; y < h; ++y){
    for(int x = 0; x < w; ++x){
      if(enterTime[y][x] <= leaveTime[y][x]){
        double dist = calcDist(x - start.x, y - start.y);
        if(dist > ret)
          ret = dist;
      }
    }
  }
  printf("%.10lf\n", 10.*ret);
  return 0;
}
