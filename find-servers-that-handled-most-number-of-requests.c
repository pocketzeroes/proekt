#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)

#ifndef STB_STRETCHY_BUFFER_H_INCLUDED
#define STB_STRETCHY_BUFFER_H_INCLUDED
#ifndef NO_STRETCHY_BUFFER_SHORT_NAMES
#define sb_free   stb_sb_free
#define sb_push   stb_sb_push
#define sb_count  stb_sb_count
#define sb_add    stb_sb_add
#define sb_last   stb_sb_last
#endif
#define stb_sb_free(a)         ((a) ? free(stb__sbraw(a)),0 : 0)
#define stb_sb_push(a,v)       (stb__sbmaybegrow(a,1), (a)[stb__sbn(a)++] = (v))
#define stb_sb_count(a)        ((a) ? stb__sbn(a) : 0)
#define stb_sb_add(a,n)        (stb__sbmaybegrow(a,n), stb__sbn(a)+=(n), &(a)[stb__sbn(a)-(n)])
#define stb_sb_last(a)         ((a)[stb__sbn(a)-1])
#define stb__sbraw(a) ((int *) (a) - 2)
#define stb__sbm(a)   stb__sbraw(a)[0]
#define stb__sbn(a)   stb__sbraw(a)[1]
#define stb__sbneedgrow(a,n)  ((a)==0 || stb__sbn(a)+(n) >= stb__sbm(a))
#define stb__sbmaybegrow(a,n) (stb__sbneedgrow(a,(n)) ? stb__sbgrow(a,n) : 0)
#define stb__sbgrow(a,n)      (*((void **)&(a)) = stb__sbgrowf((a), (n), sizeof(*(a))))

static void*stb__sbgrowf(void*arr, int increment, int itemsize){
  int dbl_cur = arr ? 2*stb__sbm(arr) : 0;
  int min_needed = stb_sb_count(arr) + increment;
  int m = dbl_cur > min_needed ? dbl_cur : min_needed;
  int*p = (int *) realloc(arr ? stb__sbraw(arr) : 0, itemsize * m + sizeof(int)*2);
  if(p){
    if(!arr)
      p[1] = 0;
    p[0] = m;
    return p+2;
  } 
  else {
    #ifdef STRETCHY_BUFFER_OUT_OF_MEMORY
    STRETCHY_BUFFER_OUT_OF_MEMORY;
    #endif
    return(void*)(2*sizeof(int));
  }
}
#endif


typedef struct SegTree{
    int leftMost, rightMost;
    struct SegTree*left;
    struct SegTree*right;
    int min;
}SegTree;
void recalc(SegTree*t);

SegTree*newSegTree(int leftMost, int rightMost, int*arr){
    SegTree*this=calloc(1, sizeof(SegTree));
    this->leftMost  = leftMost;
    this->rightMost = rightMost;
    if(leftMost == rightMost)
        this->min = arr[leftMost];
    else{
        int mid = leftMost + rightMost >> 1;
        this->left  = newSegTree(leftMost, mid, arr);
        this->right = newSegTree(mid + 1, rightMost, arr);
        recalc(this);
    }
    return this;
}
void recalc(SegTree*t){
    if(t->leftMost == t->rightMost)
        return;
    t->min = fmin(t->left->min, t->right->min);
}
int query(SegTree*t, int idx, int val){
    if(t->min > val || t->rightMost < idx)
        return -1;
    if(t->leftMost == t->rightMost)
        return t->leftMost;
    int resL = query(t->left, idx, val);
    return resL != -1 ? resL : query(t->right, idx, val);
}
void update(SegTree*t, int idx, int val){
    if(t->leftMost == t->rightMost)
        t->min = val;
    else{
        int mid = t->leftMost + t->rightMost >> 1;
        if(idx <= mid)
            update(t->left, idx, val);
        else
            update(t->right, idx, val);
        recalc(t);
    }
}

int*busiestServers(int k, int*arrival, int arrivalSz, int*load, int loadSz, int*rsz){
    int handled[k]; clr(handled);
    int*res = NULL;
    int nk[k]; clr(nk);
    SegTree*st = newSegTree(0, k-1, nk);
    for(int i=0; i<arrivalSz; i++){
        int target = i % k;
        int pos = query(st, target, arrival[i]);
        if(pos < target){
            pos = query(st, 0, arrival[i]);
        }
        if(pos != -1){
            handled[pos]++;
            update(st, pos, arrival[i] + load[i]);
        }
    }
    int max = 0;
    for(int i=0; i<k; i++){
        max = fmax(max, handled[i]);
    }
    for(int i=0; i<k; i++){
        if(handled[i] == max){
            sb_push(res, i);
        }
    }
   *rsz=  sb_count(res);
    return res;
}
