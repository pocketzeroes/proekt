#pragma GCC optimize "-O3" // Weather Report
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;

typedef struct{
  double sz, p, ev;
}Group;

int cmpG(void*a,void*b){
  Group*t=(Group*)a;
  Group*g=(Group*)b;
  return(t->p > g->p)?-1:1;
}
Group*mkgrp(Group g){
  Group*rv = calloc(1, sizeof(Group));
 *rv = g;
  return rv;
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


int main(){
  int N;
  double P1, P2, P3, P4;
  while(scanf("%d", &N)==1){
    scanf("%lf %lf %lf %lf", &P1, &P2, &P3, &P4);
    PriorityQueue*q = newPriorityQueue(cmpG);//of group
    for(int n1=0; n1<=N; n1++)
      for(int n2=0; n1+n2<=N; n2++)
        for(int n3=0; n1+n2+n3<=N; n3++){
          int n4 = N-n1-n2-n3;
          Group g;
          g.sz = 1.0;
          for(int i = 1; i <= N ; i++) g.sz *= i;
          for(int i = 1; i <= n1; i++) g.sz /= i;
          for(int i = 1; i <= n2; i++) g.sz /= i;
          for(int i = 1; i <= n3; i++) g.sz /= i;
          for(int i = 1; i <= n4; i++) g.sz /= i;
          g.p = 1.0;
          for(int i = 0; i < n1; i++) g.p *= P1;
          for(int i = 0; i < n2; i++) g.p *= P2;
          for(int i = 0; i < n3; i++) g.p *= P3;
          for(int i = 0; i < n4; i++) g.p *= P4;
          g.ev = 0.0;
          if(g.p > 1e-90)
            push(q, mkgrp(g));
        }
    while(size(q) > 1){
      Group*tq=top(q); Group g = *tq; pop(q);
      if(g.sz < 1e15){
        ll sz = (ll)(g.sz + 0.5);
        if(sz % 2){
          sz--;
          Group*tq=top(q); Group g2 = *tq; pop(q);
          g2.sz -= 1;
          if(g2.sz > 0.5)
            push(q, mkgrp(g2));
          Group g3;
          g3.sz = 1;
          g3.p = g.p + g2.p;
          g3.ev = g.ev + g2.ev + g3.p;
          push(q, mkgrp(g3));
        }
        g.sz = sz;
      }
      if(g.sz >= 2){
        Group g2;
        g2.sz = g.sz / 2;
        g2.p = g.p * 2;
        g2.ev = g.ev * 2 + g2.p;
        push(q, mkgrp(g2));
      }
    }
    Group*tq = top(q);
    printf("%.6lf\n", tq->ev);
  }
  return 0;
}
