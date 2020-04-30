#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

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

static void * stb__sbgrowf(void *arr, int increment, int itemsize){
  int dbl_cur = arr ? 2*stb__sbm(arr) : 0;
  int min_needed = stb_sb_count(arr) + increment;
  int m = dbl_cur > min_needed ? dbl_cur : min_needed;
  int *p = (int *) realloc(arr ? stb__sbraw(arr) : 0, itemsize * m + sizeof(int)*2);
  if (p) {
    if (!arr)
      p[1] = 0;
    p[0] = m;
    return p+2;
  } 
  else {
    #ifdef STRETCHY_BUFFER_OUT_OF_MEMORY
    STRETCHY_BUFFER_OUT_OF_MEMORY ;
    #endif
    return (void *) (2*sizeof(int)); 
  }
}
#endif

#if 1//stb
#define STB_(prefix,name)     stb__##prefix##name
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
}
#endif
///////////////////////////////
enum{MAXN = 500000};
int n,m;
int*X;
int*Y;
int*L;
int*ships_at_y[MAXN+1];
int left_end[2*MAXN+2];

int tt[1000000]; int tsz;
int ii[1000000]; int isz;
int ff[1000000]; int fsz;
int*current;

void rollback(int t){
    while(tsz > 0 && tt[tsz-1] == t){
        left_end[ii[isz-1]] = ff[fsz-1];
        tsz--;
        isz--;
        fsz--;
    }
}
void change(int i, int t, int dx){
    tt[tsz++] = t;
    ii[isz++] = i;
    ff[fsz++] = left_end[i];
    left_end[i] += dx;
}
stb_define_sort(sort_f, int, X[*a] < X[*b])

int main(){
    scanf("%d %d", &n, &m);
    for(int c1=0; c1<m; ++c1){
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        sb_push(X, fmax(0,a+c));
        sb_push(Y, c);
        sb_push(L, b+c - sb_last(X) + 1);
        sb_push(ships_at_y[c], c1);
    }
    int intervals = 0;
    for(int y = n-1; y >= 0; y--){
        if(sb_count(ships_at_y[y])>0)
            sort_f(ships_at_y[y], sb_count(ships_at_y[y]));
        int*merged = NULL;
        int p1 = 0;
        int p2 = 0;
        int prev = -1;
        while(p1 < sb_count(ships_at_y[y]) || p2 < sb_count(current)){
            intervals++;
            int j=0;
            bool curr = 0;
            if(p2 == sb_count(current) || (p1 != sb_count(ships_at_y[y]) && X[ships_at_y[y][p1]] < X[current[p2]])){
                j = ships_at_y[y][p1];
                if(L[j] <= 0)
                    j = -1;
                p1++;
            }
            else{
                j = current[p2];
                L[j]-=2;
                if(L[j] <= 0){
                    change(X[j], y, -1);
                    j = -1;
                }
                curr = 1;
                p2++;
            }
            if(j != -1){
                if(prev != -1 && X[prev] + L[prev] >= X[j]){
                    L[prev] = fmax(L[prev], X[j] - X[prev] + L[j]);
                    if(curr)
                        change(X[j], y, -1);
                }
                else{
                    sb_push(merged, j);
                    prev = j;
                    if(!curr)
                        change(X[j], y, 1);
                }
            }
        }
        current = merged;
    }
    int x = 0;
    bool fail = 0;
    for(int z=0; z<sb_count(current); z++){int j = current[z];
        if(X[j] <= x && X[j] + L[j] - 1 >= x)
            fail = 1;
    }
    if(fail)
        puts("impossible");
    else{
        for(int y=0; y<n; ++y){
            rollback(y);
            if(!left_end[x+2] && !left_end[x+1]){
                x += 2;
                putchar('+');
                continue;
            }
            if(!left_end[x+1]){
                x++;
                putchar('0');
                continue;
            }
            if(!left_end[x]){
                putchar('-');
                continue;
            }
        }
        puts("");
    }
    return 0;
}
