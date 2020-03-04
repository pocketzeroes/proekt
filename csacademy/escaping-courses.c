#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define back(_v) _v.ptr[_v.sz-1]

typedef struct{
  int first, second;
}pair;
pair newpair(int a, int b){
  return(pair){a,b};
}
typedef struct{
  pair first;
  int  second;
}trip;  // trip={pair, int}
trip newtrip(pair a, int b){
  return(trip){a,b};
}

typedef struct{
  int  first;
  pair second;
}pip;  // pip = {int, pair}
pip*mkpip(int a, pair b){
    pip*rv = calloc(1, sizeof(pip));
    rv->first =a;
    rv->second=b;
    return rv;
}
#define pbt(zpv, zvv) zpv.ptr = pushbackT(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
trip*pushbackT(trip*array, int *size, trip value){
  trip*output = resizeArray(array, trip, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
  trip*ptr;
  int sz;
}vect;
vect newVecT(){
  vect rez;
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
}

int cmpP(const void*pa, const void*pb){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}
int cmpPip(void*pa, void*pb){
  pip*a = (pip*)pa;
  pip*b = (pip*)pb;
  if(a->first != b->first)
    return(a->first < b->first )?-1:1;
  return cmpP(&a->second, &b->second);
}
int cmpT(const void*pa, const void*pb){
  trip*a = (trip*)pa;
  trip*b = (trip*)pb;
  int rv = cmpP(&a->first, &b->first);
  if(rv!=0)return rv;
  if(a->second != b->second) return(a->second < b->second )?-1:1;
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

///////////////////////////////////////
#define x first
#define y second

vect v [2002][2002],  // trip={pair, int}
     vv[2002][2002];
PriorityQueue*pq;// pip = {int, pair}
int dx[]={1,0,-1,0};
int dy[]={0,1,0,-1};

int main(){
    pq = newPriorityQueue(cmpPip);
    int n, m, r, i, j, p, q;
    char c;
    scanf("%d %d", &n, &m);
    getchar();
    for(i=1; i<=n; i++){
        for(j=1; j<=m; j++){
            c = getchar();
            if(c=='.'){
                pbt(v[i][j], newtrip(newpair(-1,-1),1<<30));
                pbt(v[i][j], newtrip(newpair(1<<30,1<<30),1<<30));
            }
        }
        getchar();
    }
    scanf("%d", &r);
    while(r--){
        scanf("%d %d %d %d", &i, &j, &p, &q);
        pbt(v[i][j], newtrip(newpair(p,q),1<<30));
    }
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++){
            qsort(v[i][j].ptr, v[i][j].sz, sizeof(trip), cmpT);
            for(r=v[i][j].sz-2; r>=0; r--)
               pbt(vv[i][j], newtrip(newpair(v[i][j].ptr[r].x.y+1, v[i][j].ptr[r+1].x.x-1),1<<30));
        }
    push(pq, mkpip(0, newpair(1,1)));
    back(vv[1][1]).y=0;
    while(!empty(pq)){
        pip*tq = top(pq);
        i =  tq->y.x;
        j =  tq->y.y;
        r = -tq->x;
        if(i==n&&j==m)
            break;
        pop(pq);
        if(r!=back(vv[i][j]).y)
            continue;
        for(p=0; p<4; p++){
            while(vv[i+dx[p]][j+dy[p]].sz && back(vv[i+dx[p]][j+dy[p]]).x.y-1<r)
                vv[i+dx[p]][j+dy[p]].sz--;
            for(int z=vv[i+dx[p]][j+dy[p]].sz-1; z>=0; z--){trip*it = &vv[i+dx[p]][j+dy[p]].ptr[z];
                if(it->x.x-1 > back(vv[i][j]).x.y)
                    break;
                q = fmax(it->x.x, r+1);
                if(it->y > q){
                    it->y = q;
                    push(pq, mkpip(-q, newpair(i+dx[p],j+dy[p])));
                }
            }
        }
        vv[i][j].sz--;
    }
    if(i!=n||j!=m)
        puts("-1");
    else
        printf("%d\n", r);
    return 0;
}
