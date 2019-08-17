#include<stdio.h>   // tide
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

#if 1
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
#define dfill(arr, sz1, sz2, val)do{     \
  for(int i=0; i<sz1; i++)               \
    for(int j=0; j<sz2; j++)             \
      arr[i][j] = val;                   \
}while(0)

#define dcopy(arr1, arr2, sz1, sz2)do{   \
  for(int i=0; i<sz1; i++)               \
    for(int j=0; j<sz2; j++)             \
      arr1[i][j] = arr2[i][j];           \
}while(0)

int**newmat(int x, int y){
  int**rv = calloc(x, sizeof(int*));
  for(int i=0;i<x;i++)
    rv[i] = calloc(y, sizeof(int));
  return rv;
}
void freemat(int**m, int x){
  for(int i=0; i<x; i++)
    free(m[i]);
  free(m);
  m = NULL;
}

int rows, cols;
int  H;
int**F;
int**C;
int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, -1, 0, 1};
typedef struct{
    int r;
    int c;
    int p;
}trip;
trip*newtrip(int r, int c, int p){
    trip*rez=calloc(1, sizeof(trip));
    rez->r=r;
    rez->c=c;
    rez->p=p;
    return rez;
}
int cmpT(void*pa,void*pb){
    trip*a=(trip*)pa;
    trip*b=(trip*)pb;
    return(a->p > b->p)?-1:1;
}
int enter_time(int r1, int c1, int r2, int c2){
    if(fmin(C[r1][c1], C[r2][c2]) - fmax(F[r1][c1], F[r2][c2]) < 50)
        return INT_MAX;
    int th = (C[r2][c2] - 50);
    if (H <= th)
        return INT_MIN;
    else
        return H - th;
}
int dijkstra(int r0, int c0, int t0){
    int prio[rows][cols]; dfill(prio, rows, cols, INT_MAX);
    prio[0][0] = t0;
    PriorityQueue*q = newPriorityQueue(cmpT);//of trip
    push(q, newtrip(r0, c0, t0));
    while(!empty(q)){
        trip*pcur = top(q);
        trip cur = *pcur;
        pop(q);
        if(cur.p != prio[cur.r][cur.c])
            continue;
        for (int d = 0; d < 4; d++){
            int r2 = cur.r + dr[d];
            int c2 = cur.c + dc[d];
            if (r2 >= 0 && r2 < rows && c2 >= 0 && c2 < cols){
                int t = enter_time(cur.r, cur.c, r2, c2);
                if (t != INT_MAX){
                    if (t < cur.p)
                        t = cur.p;
                    if (H - t >= F[cur.r][cur.c] + 20)
                        t += 10;
                    else
                        t += 100;
                    if (t < prio[r2][c2]){
                        prio[r2][c2] = t;
                        push(q, newtrip(r2, c2, t));
                    }
                }
            }
        }
    }
    return prio[rows-1][cols-1];
}
int main(){
    int cases;
    scanf("%d", &cases);
    for(int cas=0; cas<cases; cas++){
        if(F)freemat(F, rows);
        if(C)freemat(C, rows);
        scanf("%d %d %d", &H, &rows, &cols);
        F = newmat(rows, cols);
        C = newmat(rows, cols);
        dcopy(C, F, rows, cols);
        for(int i=0; i<rows; i++)
            for(int j=0; j<cols; j++)
                scanf("%d", &C[i][j]);
        for(int i=0; i<rows; i++)
            for(int j=0; j<cols; j++)
                scanf("%d", &F[i][j]);
        int ans = dijkstra(0, 0, INT_MIN + 1);
        if(ans < 0)
           ans = 0;
        printf("Case #%d: %.1f\n", cas + 1, ans * 0.1);
    }
    return 0;
}
