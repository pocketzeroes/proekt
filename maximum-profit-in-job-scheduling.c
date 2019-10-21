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

int cmp(const void * a, const void * b){
  return ( *(int*)a - *(int*)b );
}
int unique(int*a, int len){
  int i, j;
  for(i = j = 0; i < len; i++)
    if(a[i] != a[j])
      a[++j] = a[i];
  return j + 1;
}
int lower_bound(int*a, int n, int x){
  int l = 0;
  int h = n;
  while (l < h) {
    int mid = (l + h) / 2;
    if (x <= a[mid]) 
      h = mid;
    else
      l = mid + 1;
  }
  return l;
}
//////////////////////////
int jobScheduling(int*s, int sSz, int*t, int tSz, int*profit, int profitSz){
  int n = sSz;
  int*pos=NULL;
  int possz=0;
  for(int i=0; i<n; ++i){
    sb_push(pos, s[i]);
    sb_push(pos, t[i]);
  }
  qsort(pos, sb_count(pos), sizeof(int), cmp);
  possz = unique(pos, sb_count(pos));
  int m = possz;
  int*a[m]; clr(a);
  for(int i=0; i<n; ++i){
    s[i] = lower_bound(pos, possz, s[i]);
    t[i] = lower_bound(pos, possz, t[i]);
    sb_push(a[t[i]], i);
  }
  int dp[m]; clr(dp);
  for(int i=0; i<m; ++i){
    if(i > 0)
      dp[i] = dp[i - 1];
    for(int z=0; z<sb_count(a[i]); z++){int k = a[i][z];
      dp[i] = fmax(dp[i], dp[s[k]] + profit[k]);
    }
  }
  return dp[m-1];
}
