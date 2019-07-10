#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
int max(int a,int b){return a>b?a:b;}

typedef struct{
  int first;
  int second;
}pair;
pair newPair(int a, int b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}
int cmpP(pair a, pair b){
  if(a.first  != b.first) return(a.first  < b.first )?-1:1;
  if(a.second != b.second)return(a.second < b.second)?-1:1;
  return 0;
}
typedef struct{
  int   first;
  pair second;
}trip;
trip*newTrip(int a, pair b){
  trip*rez=calloc(1, sizeof(trip));
  rez->first =a;
  rez->second=b;
  return rez;
}
int compT(void*pb, void*pa){//rev
  trip*a = (trip*)pa;
  trip*b = (trip*)pb;
  if(a->first != b->first)return(a->first < b->first )?-1:1;
  return cmpP(a->second, b->second);
}
#if 1// pq
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
////////////////////////////////////


int  course [1000][1000];
bool visited[1000][1000];

int main(){
  int m, n;
  scanf("%d %d", &m, &n);
  for(int i=0; i<m; i++){
    for(int j=0; j<n; j++){
      scanf("%d", &course[i][j]);
      visited[i][j] = false;
    }
  }
  PriorityQueue*q=newPriorityQueue(compT);//of trip rev
  push(q, newTrip(0, newPair(0,0)));
  int ladder = 0;
  while(1){
    trip*t = top(q);
    int  t_first = t->first;
    pair t_second= t->second;
    pop(q);
    ladder = max(ladder, t_first);
    int i = t_second.first;
    int j = t_second.second;
    if(i == m - 1 && j == n - 1)
      break;
    if(visited[i][j])
      continue;
    visited[i][j] = true;
    for(int x = -1; x <= 1; x++){
      for(int y = -1; y <= 1; y++){
        if((x == 0) == (y == 0))
          continue;
        if(i + x < 0 || i + x >= m || j + y < 0 || j + y >= n)
          continue;
        push(q, newTrip(course[i+x][j+y]-course[i][j], newPair(i+x,j+y)));
      }
    }
  }
  printf("%d\n", ladder);
  return 0;
}
