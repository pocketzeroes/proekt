#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

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

typedef unsigned long long ull;
const ull base1 = 100000007;
const ull base2 = 100000037;
enum{ MAXN = (1<<10)};
enum{ MAXL = (1<<10)};
int n , mxl = -1;
int l      [MAXN], seq[MAXN][MAXL];
int lpos   [MAXN];
ull hash1  [MAXN][MAXL], hash2[MAXN][MAXL];
ull deduce1[MAXN], deduce2[MAXN];
ull pow1   [MAXL], pow2   [MAXL];


ull get_hash1(int ind, int len){
    return hash1[ind][lpos[ind] + len] - deduce1[ind]*pow1[len];
}
ull get_hash2(int ind, int len){
    return hash2[ind][lpos[ind] + len] - deduce2[ind]*pow2[len];
}
bool equal(int ind1, int ind2, int len){
    return(get_hash1(ind1 , len) == get_hash1(ind2, len)&&
           get_hash2(ind1 , len) == get_hash2(ind2, len));
}
int cmp(void*pa, void*pb){
    int*a=(int*)pa;
    int*b=(int*)pb;
    int ind1 = *a;
    int ind2 = *b;
    int l1 = l[ind1] - lpos[ind1];
    int l2 = l[ind2] - lpos[ind2];
    if(equal(ind1 , ind2 , fmin(l1,l2)))
        return(!(l1>l2))?-1:1;
    int le = 0,
        ri = fmin(l1,l2),
        mid;
    while(le<ri){
        mid = (le + ri + 1)/2;
        if(equal(ind1 , ind2 , mid))
            le = mid;
        else
            ri = mid - 1;
    }
    return(!(seq[ind1][lpos[ind1] + le + 1] < seq[ind2][lpos[ind2] + le + 1]))?-1:1;
}

int*mki(int i){
    int*rv = calloc(1, sizeof(int));
   *rv = i;
    return rv;
}
PriorityQueue*pq;

void init(){
    scanf("%d",&n);
    for(int i=0; i<n; i++){
        scanf("%d",&l[i]);
        if(mxl < l[i])
           mxl = l[i];
        for(int j=1; j<=l[i]; j++)
            scanf("%d", &seq[i][j]);
    }
    pow1[0]=1;
    pow2[0]=1;
    for(int i=1; i<=mxl; i++){
        pow1[i] = pow1[i-1]*base1;
        pow2[i] = pow2[i-1]*base2;
    }
    for(int i=0; i<n; i++){
        for(int j=1; j<=l[i]; j++){
            hash1[i][j] = hash1[i][j-1]*base1 + seq[i][j];
            hash2[i][j] = hash2[i][j-1]*base2 + seq[i][j];
        }
    }
}
void take(int get){
    deduce1[get] = deduce1[get]*base1 + seq[get][lpos[get]];
    deduce2[get] = deduce2[get]*base2 + seq[get][lpos[get]];
}
void solve(){
    for(int i=0; i<n; i++)
        push(pq, mki(i));
    int get;
    int*tq = top(pq); get = *tq; pop(pq);
    lpos[get]++;
    printf("%d", seq[get][lpos[get]]);
    take(get);
    if(lpos[get]!=l[get])
        push(pq, mki(get));
    while(!empty(pq)){
        int*tq = top(pq); get = *tq; pop(pq);
        lpos[get]++;
        printf(" %d", seq[get][lpos[get]]);
        take(get);
        if(lpos[get]!=l[get])
            push(pq, mki(get));
    }
    puts("");
}
int main(){
    pq = newPriorityQueue(cmp);
    init();
    solve();
    return 0;
}
