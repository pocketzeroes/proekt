#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{  MAXOBJS         =  21};
enum{  MAXSEGS         = 220};
double ZEROLIM         = 1.0E-9;
double INTERSECTIONLIM = 1.0E-7;
double INF             = 10000000000.0;
enum{  SCREEN          = 0};
double speed           = 1.0;
double tdiff           = 1.0;
int    nBalls;

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


typedef struct object{
    int    count;
    double removeT;
}object;
object objects[MAXOBJS];
int nObjs;
typedef struct{
    double x, y;
}pt;

double length(pt p){
    return sqrt(p.x*p.x + p.y*p.y);
}

typedef struct segment{
    pt  p1, a, n;
    int iObj;
}segment;
segment segs[MAXSEGS];
int nSegs;

void initSeg(segment*s, int x1, int y1, int x2, int y2, int index){
    s->p1.x     = x1;
    s->p1.y     = y1;
    s->a.x      = x2-x1;
    s->a.y      = y2-y1;
    s->n.x      = -s->a.y;
    s->n.y      =  s->a.x;
    double len  = sqrt(s->n.x * s->n.x + s->n.y * s->n.y);
    s->n.x     /= len;
    s->n.y     /= len;
    s->iObj     = index;
}
pt reflection(segment*s, pt a){
    pt aref = a;
    double dotProd = a.x * s->n.x + a.y * s->n.y;
    aref.x -= 2*dotProd * s->n.x;
    aref.y -= 2*dotProd * s->n.y;
    if(fabs(aref.x - (int)(aref.x+0.5)) < ZEROLIM)
        aref.x = (int)(aref.x+0.5);
    if(fabs(aref.y - (int)(aref.y+0.5)) < ZEROLIM)
        aref.y = (int)(aref.y+0.5);
    return aref;
}



typedef struct event{
    double thit;
    pt     loc;
    pt     a;
    int    iSeg;
}event;
event*mkevent(event e){
    event*rv=calloc(1, sizeof(event));
    *rv = e;
    return rv;
}
int cmpE(void*a, void*b){
    event*lhs=(event*)a;
    event*rhs=(event*)b;
    return(lhs->thit > rhs->thit)?-1:1;
}
#define pb(zpv, zvv) zpv.ptr = pushbackE(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
event*pushbackE(event*array, int *size, event value){
  event*output = resizeArray(array, event, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
    event*ptr;
    int sz;
}vece;
vece newVecE(){
    vece rez;
    rez.ptr = NULL;
    rez.sz  = 0;
    return rez;
}

PriorityQueue*pq;//of event

bool intersection(segment ball, segment s, double*t, double*u){
    double a = ball.a.x;
    double b = ball.a.y;
    double c = s.a.x;
    double d = s.a.y;
    double det = -a*d + b*c;
    if (abs(det) <= ZEROLIM)
        return false;
    double e = s.p1.x - ball.p1.x;
    double f = s.p1.y - ball.p1.y;
   *u = (-e*b+f*a)/det;
    if(*u < 0.0 || *u > 1.0)
        return false;
   *t = (-e*d + f*c)/det;
    return *t > 0.0;
}
bool findNextIntersection(segment ball, int currSeg, double*t, double*u, int*iSeg){
   *t = INF;
    bool found = false;
    for(int i=0; i<nSegs; i++){
        if(i == currSeg || objects[segs[i].iObj].count <= 0)
            continue;
        double tt, uu;
        if(intersection(ball, segs[i], &tt, &uu)){
            if(tt < *t){
               *t     = tt;
               *u     = uu;
               *iSeg  = i;
                found = true;
            }
        }
    }
    if(found && (fabs(*u) <=INTERSECTIONLIM || fabs(*u-1) <= INTERSECTIONLIM))
       ;// fprintf(stderr, "ERROR: intersecti0n too close to endpoint of object.\n");
    return found;
}
void processEvents(){
    double t, u;
    int    iSeg;
    double prevTime = -1.0;
    while(!empty(pq)){
        event*tq=top(pq); event e = *tq; pop(pq);
        int iObj = segs[e.iSeg].iObj;
        if(!empty(pq) && fabs(e.thit - prevTime) > ZEROLIM){
            vece list = newVecE();//of event
            event*tq=top(pq); event e1 = *tq; pop(pq);
            while(!empty(pq) && fabs(e1.thit - e.thit) <= ZEROLIM){
                pb(list, e1);
                tq = top(pq); e1 = *tq; pop(pq);
            }
            if(fabs(e1.thit-e.thit) > ZEROLIM)
                push(pq, mkevent(e1));
            else
                pb(list, e1);
            int countHits[MAXOBJS] = {0};
            countHits[iObj] = 1;
            for(int i=0; i<list.sz; i++) {
                int j = segs[list.ptr[i].iSeg].iObj;
                countHits[j]++;
            }
            for(int i=1; i<=nObjs; i++) {
                if (countHits[i] >= objects[i].count)
                    objects[i].count = 0;
            }
            for(int i=0; i<list.sz; i++)
                push(pq, mkevent(list.ptr[i]));
        }
        if(--objects[iObj].count > 0){
            pt aReflect = reflection(&segs[e.iSeg], e.a);
            segment tmp;
            tmp.p1 = e.loc;
            tmp.a = aReflect;
            if(findNextIntersection(tmp, e.iSeg, &t, &u, &iSeg)){
                double nextHitTime = e.thit+length(tmp.a)*t/speed;
                event nextEvent;
                nextEvent.thit = nextHitTime;
                nextEvent.loc.x = e.loc.x+t*tmp.a.x;
                nextEvent.loc.y = e.loc.y+t*tmp.a.y;
                nextEvent.a = tmp.a;
                nextEvent.iSeg = iSeg;
                push(pq, mkevent(nextEvent));
            }
        }
        else{
            segment tmp;
            tmp.p1 = e.loc;
            tmp.a = e.a;
            if(findNextIntersection(tmp, -1, &t, &u, &iSeg)){
                double nextHitTime = e.thit + length(tmp.a) * t/speed;
                event nextEvent;
                nextEvent.thit = nextHitTime;
                nextEvent.loc.x = e.loc.x+t*tmp.a.x;
                nextEvent.loc.y = e.loc.y+t*tmp.a.y;
                nextEvent.a = tmp.a;
                nextEvent.iSeg = iSeg;
                push(pq, mkevent(nextEvent));
            }
        }
        objects[SCREEN].count = 10;
        prevTime = e.thit;
    }
}
int filter(int a){
    if (a < 0)
        return 0;
    return a;
}
int main(){
    pq = newPriorityQueue(cmpE);
    int width, height, r, s;
    double loc;
    scanf("%d %d %d %d %lf %d %d", &width, &height, &nBalls, &nObjs, &loc, &r, &s);
    segs[0].p1.x          = 0;
    segs[0].p1.y          = 0;
    segs[0].a.x           = 0;
    segs[0].a.y           = height;
    segs[0].n.x           = 1;
    segs[0].n.y           = 0;
    segs[0].iObj          = SCREEN;
    segs[1].p1.x          = 0;
    segs[1].p1.y          = height;
    segs[1].a.x           = width;
    segs[1].a.y           = 0;
    segs[1].n.x           = 0;
    segs[1].n.y           = -1;
    segs[1].iObj          = SCREEN;
    segs[2].p1.x          = width;
    segs[2].p1.y          = height;
    segs[2].a.x           = 0;
    segs[2].a.y           = -height;
    segs[2].n.x           = -1;
    segs[2].n.y           = 0;
    segs[2].iObj          = SCREEN;
    objects[SCREEN].count = 10;
    nSegs                 = 3;
    for(int i=1; i<=nObjs; i++){
        int p;
        scanf("%d", &p);
        int prevx, prevy;
        scanf("%d %d", &prevx, &prevy);
        for(int j=1; j<p; j++){
            int x, y;
            scanf("%d %d", &x, &y);
            initSeg(&segs[nSegs], prevx, prevy, x, y, i);
            prevx = x;
            prevy = y;
            nSegs++;
        }
        initSeg(&segs[nSegs], prevx, prevy, segs[nSegs-p+1].p1.x, segs[nSegs-p+1].p1.y, i);
        nSegs++;
        scanf("%d", &objects[i].count);
        objects[i].removeT = INF;
    }
    segment ball;
    ball.p1.x = loc;
    ball.p1.y = 0;
    ball.a.x  = r;
    ball.a.y  = s;
    double t, u;
    int iSeg;
    if(!findNextIntersection(ball, -1, &t, &u, &iSeg)){
        fprintf(stderr, "ERROR: no initial intersecti0n\n");
        exit(-1);
    }
    double thit = length(ball.a)*t/speed;
    event e;
    e.thit = thit;
    e.loc.x = loc+t*r;
    e.loc.y = 0 + t*s;
    e.a = ball.a;
    e.iSeg = iSeg;
    push(pq, mkevent(e));
    for(int i=2; i<=nBalls; i++) {
        e.thit += tdiff;
        push(pq, mkevent(e));
    }
    processEvents();
    printf("%d", filter(objects[1].count));
    for(int i=2; i<=nObjs; i++)
        printf(" %d", filter(objects[i].count));
    puts("");
    return 0;
}

