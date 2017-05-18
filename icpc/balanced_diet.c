#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
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

int cmpP(void*pa,void*pb)
{
  pair*a=(pair*)pa;
  pair*b=(pair*)pb;
  int diff;
  diff = a->first  - b->first;  if(diff!=0) return diff;
  return a->second - b->second;
}



int main(){
  int i, x;
  int M, K;
  scanf("%d %d", &M, &K);
  do{
    int f[M];
    for(i = 0; i < M; i++)
      scanf("%d", &f[i]);
    long long ftot = 0;
    for(i = 0; i < M; i++)
      ftot += f[i];
    int atot[M];
    memset(atot, 0, sizeof(atot));
    for(i = 0; i < K; i++){
      scanf("%d", &x);
      atot[x-1]++;
    }
    PriorityQueue*q = newPriorityQueue(cmpP);
    for(i = 0; i < M; i++){
      push(q, newPair(-((atot[i]+1)*ftot+f[i]-1)/f[i], i));
    }
    int n;
    for (n = K+1; n <= K+2*ftot; n++){
      pair*tq=top(q);
      int tqf=tq->first;
      if (-tqf < n){
        n = -tqf; 
        break;
      }
      int i = tq->second;
      atot[i]++;
      pop(q);
      push(q, newPair(-((atot[i]+1)*ftot+f[i]-1)/f[i], i));
    }
    if(n > K+2*ftot){
      puts("forever");
    } 
    else{
      printf("%d\n", n-K-1);
    }
  }
  while(0);
}


















































