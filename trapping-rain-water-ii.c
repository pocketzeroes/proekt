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
///////////////

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

////////////
int compare(void*pa, void*pb){
    pair*a=(pair*)pa;
    pair*b=(pair*)pb;
    return a->second < b->second;
}
inline int min(int a,int b){return a<b?a:b;}
inline int max(int a,int b){return a>b?a:b;}


int getIdx(int x, int y, int ncol) {
    return x*ncol+y;
}
int getX(int idx, int ncol) {
    return idx/ncol;
}
int getY(int idx, int ncol) {
    return idx%ncol;
}
int trapRainWater(int**board,int boardsize,int board0size){
    int nrow = boardsize;
    if (nrow == 0) return 0;
    int ncol = board0size;
    bool visited[nrow][ncol];
    memset(visited,0,sizeof(visited));
    PriorityQueue*qq=newPriorityQueue(compare);

    for (int j=0; j<ncol; ++j) {
        push(qq, newPair(j, board[0][j]));
        visited[0][j] = true;
        push(qq, newPair((nrow-1)*ncol+j, board[nrow-1][j]));
        visited[nrow-1][j] = true;
    }
    for (int i=0; i<nrow; ++i) {
        push(qq, newPair(getIdx(i, 0, ncol), board[i][0]));
        visited[i][0] = true;
        push(qq, newPair(getIdx(i, ncol-1, ncol), board[i][ncol-1]));
        visited[i][ncol-1] = true;
    }
    int res = 0;
    while (size(qq) > 0){
        pair*cur = top(qq);
        int curHeight = cur->second;
        int curX = getX(cur->first, ncol);
        int curY = getY(cur->first, ncol);
        pop(qq);
        if (curX-1>=0   && visited[curX-1][curY] == false){
            visited[curX-1][curY] = true;
            res += max(0, (curHeight - board[curX-1][curY]));
            push(qq, newPair(getIdx(curX-1, curY, ncol), max(board[curX-1][curY], curHeight)));
        }
        if (curX+1<nrow && visited[curX+1][curY] == false){
            visited[curX+1][curY] = true;
            res += max(0, (curHeight - board[curX+1][curY]));
            push(qq, newPair(getIdx(curX+1, curY, ncol), max(board[curX+1][curY], curHeight)));
        }
        if (curY-1>=0   && visited[curX][curY-1] == false){
            visited[curX][curY-1] = true;
            res += max(0, (curHeight - board[curX][curY-1]));
            push(qq, newPair(getIdx(curX, curY-1, ncol), max(board[curX][curY-1], curHeight)));
        }
        if (curY+1<ncol && visited[curX][curY+1] == false){
            visited[curX][curY+1] = true;
            res += max(0, (curHeight - board[curX][curY+1]));
            push(qq, newPair(getIdx(curX, curY+1, ncol), max(board[curX][curY+1], curHeight)));
        }
    }
    return res;
}






