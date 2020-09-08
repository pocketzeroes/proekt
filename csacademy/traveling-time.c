#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
enum{MAX_M = 100000};

typedef struct{
  int l, r, t;
}Range;
Range ranges[MAX_M];

int cmp(const void*pa, const void*pb){
  Range*a=(Range*)pa;
  Range*b=(Range*)pb;
  return(a->t < b->t || (a->t == b->t && a->l < b->l))?-1:1;
}
typedef int* intp;
int cmpp(const void*pa, const void*pb){
  intp*aa=(intp*)pa;
  intp*bb=(intp*)pb;
  intp a=*aa;
  intp b=*bb;
  return(*a<*b)?-1:1;
}

int aint[1+8*(MAX_M + 1)],
    lazy[1+8*(MAX_M + 1)];
int*pnt [2*MAX_M+2];

void pushLazy(int nod, int l, int r){
  if(l < r){
    lazy[2 * nod  ] = fmin(lazy[2 * nod], lazy[nod]);
    lazy[2 * nod+1] = fmin(lazy[2 * nod + 1], lazy[nod]);
  }
  aint[nod] = fmin(aint[nod], lazy[nod]);
  lazy[nod] = MAX_M + 1;
}
void build(int nod, int l, int r){
  if(l < r){
    int mid = (l + r) / 2;
    build(2 * nod, l, mid);
    build(2 * nod + 1, mid + 1, r);
  }
  aint[nod] = lazy[nod] = MAX_M + 1;
}
int query(int i, int j, int l, int r, int nod){
  pushLazy(nod, l, r);
  if(r < i || j < l || j < i)
    return MAX_M + 1;
  if(i <= l && r <= j){
    return aint[nod];
  }
  else{
    int mid = (l + r) / 2;
    return fmin(query(i, j, l, mid, 2 * nod), query(i, j, mid + 1, r, 2 * nod + 1));
  }
}
void update(int i, int j, int val, int l, int r, int nod){
  pushLazy(nod, l, r);
  if(r < i || j < l || j < i)
    return;
  if(i <= l && r <= j){
    lazy[nod] = fmin(lazy[nod], val);
    pushLazy(nod, l, r);
  }
  else{
    int mid = (l + r) / 2;
    update(i, j, val, l, mid, 2 * nod);
    update(i, j, val, mid + 1, r, 2 * nod + 1);
    aint[nod] = fmin(aint[2 * nod], aint[2 * nod + 1]);
  }
}
int normalize(int N, int M){
  int top = 0;
  int one = 1;
  pnt[top++] = &one;
  pnt[top++] = &N;
  for(int i=0; i<M; ++i){
    pnt[top++] = &ranges[i].l;
    pnt[top++] = &ranges[i].r;
  }
  qsort(pnt, top, sizeof(intp), cmpp);
  int last = *pnt[0], j = 0;
  for(int i=0; i<top; ++i)
    if(*pnt[i] == last)
       *pnt[i] = j;
    else{
      ++j;
      last = *pnt[i];
      *pnt[i] = j;
    }
  return N;
}
int main(){
  int N, M, T;
  scanf("%d %d %d", &N, &M, &T);
  T -= N;
  for(int i=0; i<M; ++i){
    int l, r, t;
    scanf("%d %d %d", &l, &r, &t);
    t -= l;
    ranges[i] = (Range){l, r, t};
  }
  N = normalize(N, M);
  qsort(ranges, M, sizeof(Range), cmp);
  build(1,0,2*MAX_M+2);
  update(0, 0, 0, 0, 2*MAX_M+2, 1);
  for(int i=0; i<M; ++i){
    if(ranges[i].t <= T){
      int best = query(ranges[i].l, ranges[i].r, 0, 2*MAX_M+2, 1);
      update(ranges[i].l, ranges[i].r, best + 1, 0, 2*MAX_M+2, 1);
    }
  }
  int res = query(N, N, 0, 2*MAX_M+2, 1);
  if(res > MAX_M)
    printf("-1");
  else
    printf("%d", res);
  return 0;
}
