#pragma GCC optimize "-O3"
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
 
typedef long long ll;
enum{ INF = 0x3f3f3f3f};
 
int n, m, x, y;
int a  [505][505];
int vis[505][505],
    h  [505][505];
int dir[8][2] = { {1,0},{0,1},{0,-1},{-1,0},{1,1},{-1,-1},{1,-1},{-1,1} };
 
typedef struct{
    int x, y, h;
}node;

node*newnode(int a, int b, int c){
    node*rv = calloc(1, sizeof(node));
    rv->x = a;
    rv->y = b;
    rv->h = c;
    return rv;
}
int cmpN(void*pa, void*pb){
    node*t=(node*)pa;
    node*a=(node*)pb;
    return(t->h > a->h)?-1:1;
}
node*pre;
node*nt;
 
int main(){
    while(~scanf("%d%d", &n, &m)){
        PriorityQueue*q = newPriorityQueue(cmpN);//of node
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= m; j++)
                scanf("%d", &a[i][j]);
        scanf("%d%d", &x, &y);
        memset(vis, 0, sizeof vis);
        pre = newnode(x, y, a[x][y]);
        push(q, pre);
        vis[x][y] = 1;
        h  [x][y] = a[x][y];
        while(!empty(q)){
            pre = top(q); pop(q);
            for(int i = 0; i < 8; i++){
                int xx = pre->x + dir[i][0];
                int yy = pre->y + dir[i][1];
                if(xx<1 || yy<1 || xx>n || yy>m|| a[xx][yy] >= 0||vis[xx][yy])
                    continue;
                int tmp = fmax(pre->h, a[xx][yy]);
                h  [xx][yy] = tmp;
                vis[xx][yy] = 1;
                nt = newnode(xx,yy,tmp);
                push(q, nt);
            }
        }
        ll ans = 0;
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= m; j++)
                ans += -1LL * h[i][j];
        printf("%lld\n", ans);
    }
    return 0;
}
