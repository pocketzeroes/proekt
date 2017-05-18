#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
int cmp (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}

typedef struct pair{
    int first;
    int second;
}pair;
pair*newPair(int a, int b){
    pair*rez=malloc(sizeof(pair));
    rez->first =a;
    rez->second=b;
    return rez;
}
#ifndef __HEAP_H_GUARD__
#define __HEAP_H_GUARD__
#define HEAP_STARTING_SIZE 256
struct heap_st;
typedef struct heap_st PriorityQueue;
PriorityQueue* newPriorityQueue(int (*)(void*, void*));
int   push(PriorityQueue*, void*);
void* top(PriorityQueue*);
void* pop(PriorityQueue*);
void delPriorityQueue(PriorityQueue**, void (*)(void*));
#endif
struct heap_st{
	void** info;
	int (*compareFunction)(void*, void*);
	unsigned used;
	unsigned currentSize;
};
PriorityQueue* newPriorityQueue(int (*compareFunction)(void*, void*)){
	PriorityQueue* newHeap = (PriorityQueue*)malloc(sizeof(PriorityQueue));
	if (newHeap == NULL){
		return NULL;
	}
	newHeap->info = (void**) malloc(HEAP_STARTING_SIZE*sizeof(void*));
	if (newHeap->info == NULL){
		free(newHeap);
		return NULL;
	}
	newHeap->used = 0;
	newHeap->currentSize = HEAP_STARTING_SIZE;
	newHeap->compareFunction = compareFunction;
	return newHeap;
}
int  push(PriorityQueue* h, void* data){
	if (h == NULL){
		return 0;
	}
	if (h->used == 0){
		h->info[0] = data;
		h->used = 1;
		return 1;
	}
	if(h->used == h->currentSize){
		unsigned newSize =  h->currentSize * 2;
		void** newIndexes = (void**) realloc (h->info, newSize*sizeof(PriorityQueue));
		if (newIndexes == NULL){
			return 0;
		}
		h->info = newIndexes;
		h->currentSize = newSize;
	}
	h->info[h->used] = data;
	unsigned index, parentIndex;
	index = h->used;
	do{
		parentIndex = (index-1)/2;
		if(h->compareFunction(data, h->info[parentIndex]) > 0){
			h->info[index] = h->info[parentIndex];
			h->info[parentIndex] = data;
			index = parentIndex;
		}
		else{
			break;
		}
	}
    while (parentIndex != 0);
	h->used++;
	return 1;
}
void*top(PriorityQueue*h){
	if (h == NULL || h->used == 0){
		return NULL;
	}
	return h->info[0];
}
void*pop(PriorityQueue*h){
	if (h == NULL || h->used == 0){
		return NULL;
	}
	void* toRet = h->info[0];
	if (h->used == 1){
		h->info[0] = NULL;
		h->used--;
		return toRet;
	}
	h->used--;
	h->info[0] = h->info[h->used];
	h->info[h->used] = NULL;
	unsigned left, right, current = 0, index;
	do{
		index = current;
		left = (current * 2) + 1;
		right = (current * 2) + 2;
		if (left < h->used && h->compareFunction(h->info[left], h->info[current]) > 0){
			if (right < h->used && h->compareFunction(h->info[right], h->info[current]) > 0 &&
					h->compareFunction(h->info[right], h->info[left]) > 0){
				current = right;
			}
			else{
				current = left;
			}
		}
		else if (right < h->used && h->compareFunction(h->info[right], h->info[current]) > 0){
			current = right;
		}
		if (current != index){
			void* swap = h->info[current];
			h->info[current] = h->info[index];
			h->info[index] = swap;
		}
	}
    while(index != current);
	return toRet;
}
void delPriorityQueue(PriorityQueue** h, void (*freeFunction)(void*)){
	if (h == NULL || *h == NULL){
		return;
	}
	if (freeFunction != NULL){
		unsigned i;
		for (i = 0; i < (*h)->used; ++i){
			freeFunction((*h)->info[i]);
		}
	}
	free((*h)->info);
	free((*h));
	*h = NULL;
}
int size(PriorityQueue*h){
    return h->used;
}
bool empty(PriorityQueue*h){
  return size(h)==0;
}
int cmpP(void*pa,void*pb)
{
  pair*a=(pair*)pa;
  pair*b=(pair*)pb;
  int diff;
  diff = a->first  - b->first;  if(diff!=0) return diff;
  return a->second - b->second;
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct vecS {
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;// = malloc(sizeof(vec));
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
/////
typedef long long ll;
ll min(ll a,ll b){return a<b?a:b;}
ll max(ll a,ll b){return a>b?a:b;}

int gN;
void dijkstra(int*dist, vec*e, vec*el, int s){
  for(int i=0;i<gN;i++)dist[i] =(int) 1e9;
  PriorityQueue*q = newPriorityQueue(cmpP);
  push(q, newPair(0, s));
  while (!empty(q)){
    pair*tq=top(q);
    int d = -tq->first, x = tq->second;
    pop(q);
    if (d >= dist[x])
      continue;
    dist[x] = d;
    for (int i = 0; i < e[x].sz; i++){
      push(q, newPair(-d-el[x].ptr[i], e[x].ptr[i]));
    }
  }
}

int main(){
  int N, B, S, R;
  scanf("%d %d %d %d", &N, &B, &S, &R);
  do{
    vec fe[N], fel[N], be[N], bel[N];
    memset(fe, 0, sizeof(fe));
    memset(fel,0, sizeof(fe));
    memset(be, 0, sizeof(fe));
    memset(bel,0, sizeof(fe));
    for (int i = 0; i < R; i++){
      int X, Y, L;
      scanf("%d %d %d", &X, &Y, &L);
      X--, Y--;
      fe [X].ptr = pushback(fe [X].ptr, &fe [X].sz, Y);
      fel[X].ptr = pushback(fel[X].ptr, &fel[X].sz, L);
      be [Y].ptr = pushback(be [Y].ptr, &be [Y].sz, X);
      bel[Y].ptr = pushback(bel[Y].ptr, &bel[Y].sz, L);
    }
    gN=N;
    int fdist[N]; dijkstra(fdist, fe, fel, B);
    int bdist[N]; dijkstra(bdist, be, bel, B);
    int dist[B];
    for (int i = 0; i < B; i++)
      dist[i] = fdist[i] + bdist[i];
    qsort(dist, B, sizeof(int), cmp);
    ll cumdist[B+1];
    memset(cumdist, 0, sizeof(cumdist));
    for (int i = 0; i < B; i++)
      cumdist[i+1] = cumdist[i] + dist[i];
    ll dyn [B+1];
    ll dyn2[B+1];
    ll tmp [B+1];
    for (int i = 1; i <= B; i++)
      dyn[i] = (i-1)*cumdist[i];
    for (int s = 2; s <= S; s++){
      memcpy(dyn2, dyn, sizeof(dyn));
      for(int i = 1; i<=B; i++)
        for(int j=1; j*s<=i; j++){
          dyn2[i] = min(dyn2[i], dyn[i-j] + (j-1)*(cumdist[i]-cumdist[i-j]));
        }
      memcpy(tmp, dyn , sizeof(dyn));
      memcpy(dyn, dyn2, sizeof(dyn));
      memcpy(dyn2,tmp , sizeof(dyn));
    }
    printf("%lld\n", dyn[B]);
  }
  while(0);
}



















































