#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

#define STB_(prefix,name)     stb__##prefix##name
//////////////////////////////////////////////////////////////////////////////
//
//                       templatized Sort routine
//
// This is an attempt to implement a templated sorting algorithm.
// To use it, you have to explicitly instantiate it as a _function_,
// then you call that function. This allows the comparison to be inlined,
// giving the sort similar performance to C++ sorts.
//
// It implements quicksort with three-way-median partitioning (generally
// well-behaved), with a final insertion sort pass.
//
// When you define the compare expression, you should assume you have
// elements of your array pointed to by 'a' and 'b', and perform the comparison
// on those. OR you can use one or more statements; first say '0;', then
// write whatever code you want, and compute the result into a variable 'c'.

#define stb_declare_sort(FUNCNAME, TYPE)    \
                       void FUNCNAME(TYPE *p, int n)
#define stb_define_sort(FUNCNAME,TYPE,COMPARE) \
                       stb__define_sort(       void, FUNCNAME,TYPE,COMPARE)
#define stb_define_sort_static(FUNCNAME,TYPE,COMPARE) \
                       stb__define_sort(static void, FUNCNAME,TYPE,COMPARE)

#define stb__define_sort(MODE, FUNCNAME, TYPE, COMPARE)                       \
                                                                              \
static void STB_(FUNCNAME,_ins_sort)(TYPE *p, int n)                          \
{                                                                             \
   int i,j;                                                                   \
   for (i=1; i < n; ++i) {                                                    \
      TYPE t = p[i], *a = &t;                                                 \
      j = i;                                                                  \
      while (j > 0) {                                                         \
         TYPE *b = &p[j-1];                                                   \
         int c = COMPARE;                                                     \
         if (!c) break;                                                       \
         p[j] = p[j-1];                                                       \
         --j;                                                                 \
      }                                                                       \
      if (i != j)                                                             \
         p[j] = t;                                                            \
   }                                                                          \
}                                                                             \
                                                                              \
static void STB_(FUNCNAME,_quicksort)(TYPE *p, int n)                         \
{                                                                             \
   /* threshold for transitioning to insertion sort */                       \
   while (n > 12) {                                                           \
      TYPE *a,*b,t;                                                           \
      int c01,c12,c,m,i,j;                                                    \
                                                                              \
      /* compute median of three */                                           \
      m = n >> 1;                                                             \
      a = &p[0];                                                              \
      b = &p[m];                                                              \
      c = COMPARE;                                                            \
      c01 = c;                                                                \
      a = &p[m];                                                              \
      b = &p[n-1];                                                            \
      c = COMPARE;                                                            \
      c12 = c;                                                                \
      /* if 0 >= mid >= end, or 0 < mid < end, then use mid */                \
      if (c01 != c12) {                                                       \
         /* otherwise, we'll need to swap something else to middle */         \
         int z;                                                               \
         a = &p[0];                                                           \
         b = &p[n-1];                                                         \
         c = COMPARE;                                                         \
         /* 0>mid && mid<n:  0>n => n; 0<n => 0 */                            \
         /* 0<mid && mid>n:  0>n => 0; 0<n => n */                            \
         z = (c == c12) ? 0 : n-1;                                            \
         t = p[z];                                                            \
         p[z] = p[m];                                                         \
         p[m] = t;                                                            \
      }                                                                       \
      /* now p[m] is the median-of-three */                                   \
      /* swap it to the beginning so it won't move around */                  \
      t = p[0];                                                               \
      p[0] = p[m];                                                            \
      p[m] = t;                                                               \
                                                                              \
      /* partition loop */                                                    \
      i=1;                                                                    \
      j=n-1;                                                                  \
      for(;;) {                                                               \
         /* handling of equality is crucial here */                           \
         /* for sentinels & efficiency with duplicates */                     \
         b = &p[0];                                                           \
         for (;;++i) {                                                        \
            a=&p[i];                                                          \
            c = COMPARE;                                                      \
            if (!c) break;                                                    \
         }                                                                    \
         a = &p[0];                                                           \
         for (;;--j) {                                                        \
            b=&p[j];                                                          \
            c = COMPARE;                                                      \
            if (!c) break;                                                    \
         }                                                                    \
         /* make sure we haven't crossed */                                   \
         if (i >= j) break;                                                   \
         t = p[i];                                                            \
         p[i] = p[j];                                                         \
         p[j] = t;                                                            \
                                                                              \
         ++i;                                                                 \
         --j;                                                                 \
      }                                                                       \
      /* recurse on smaller side, iterate on larger */                        \
      if (j < (n-i)) {                                                        \
         STB_(FUNCNAME,_quicksort)(p,j);                                       \
         p = p+i;                                                             \
         n = n-i;                                                             \
      } else {                                                                \
         STB_(FUNCNAME,_quicksort)(p+i, n-i);                                  \
         n = j;                                                               \
      }                                                                       \
   }                                                                          \
}                                                                             \
                                                                              \
MODE FUNCNAME(TYPE *p, int n)                                                 \
{                                                                             \
   STB_(FUNCNAME, _quicksort)(p, n);                                           \
   STB_(FUNCNAME, _ins_sort)(p, n);                                            \
}                                                                             \


enum{ Max =(int) 5e4+2};
enum{ languages =(int) 1e6+1};
int block, totalMatches;
int men[Max], women[Max], answer[Max];
int cntShared[languages], cntMen[languages], cntWomen[languages];

typedef struct{
    int l, r, index;
}query;

stb_define_sort(sort_q, query, (a->l/block == b->l/block)? a->r < b->r : a->l < b->l)

void add(int pos){
    if(men[pos] == women[pos]) {
        cntShared[men[pos]]++;
        totalMatches++;
        return;
    }
    if(cntWomen[men[pos]] > 0) {
        cntShared[men[pos]]++;
        cntWomen[men[pos]]--;
        totalMatches++;
    }
    else
        cntMen[men[pos]]++;
    if(cntMen[women[pos]] > 0) {
        cntShared[women[pos]]++;
        cntMen[women[pos]]--;
        totalMatches++;
    }
    else
        cntWomen[women[pos]]++;
}
void Remove(int pos){
    if(men[pos] == women[pos]) {
        cntShared[men[pos]]--;
        totalMatches--;
        return;
    }
    if(cntMen[men[pos]] > 0)
        cntMen[men[pos]]--;
    else {
        cntShared[men[pos]]--;
        cntWomen[men[pos]]++;
        totalMatches--;
    }
    if(cntWomen[women[pos]] > 0)
        cntWomen[women[pos]]--;
    else {
        cntShared[women[pos]]--;
        cntMen[women[pos]]++;
        totalMatches--;
    }
}
int main(){
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    block = ceil(sqrt(n));
    for(int i = 0; i < n; ++i)
        scanf("%d", &men[i]);
    for(int i = 0; i < n; ++i)
        scanf("%d", &women[i]);
    query queries[m];
    for(int i = 0; i < m; ++i){
        scanf("%d%d", &queries[i].l, &queries[i].r);
        queries[i].index = i;
        answer[i] = 0;
    }
    sort_q(queries, m);
    int left = 0, right = 0;
    totalMatches = 0;
    add(0);
    for(int z=0;z<m;z++){query*q = &queries[z];
        while(left > q->l) {
            left--;
            add(left);
        }
        while(right < q->r) {
            right++;
            add(right);
        }
        while(left < q->l) {
            Remove(left);
            left++;
        }
        while(right > q->r) {
            Remove(right);
            right--;
        }
        answer[q->index] = totalMatches;
    }
    for(int i = 0; i < m; ++i) 
        printf("%d\n", answer[i]);
    return 0;
}
