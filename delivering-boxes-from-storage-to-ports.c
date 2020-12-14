#pragma GCC optimize "-O3"
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

int boxDelivering(int**boxes, int boxesSz, int*boxes0sz, int portsCount, int maxBoxes, int maxWeight){
  int n, mb, mw;
  n = boxesSz;
  int dest[n];
  int w[n];
  int*kiri=NULL;
  for(int i=0; i<n; ++i){
    dest[i]=boxes[i][0];
    w[i]   =boxes[i][1];
    if(i == 0)
      sb_push(kiri, i);
    else if(dest[i] == dest[i-1])
      sb_push(kiri, kiri[i-1]);
    else
      sb_push(kiri, i);
  }
  int dp[n+1]; clr(dp);
  dp[n] = 0;
  mb = maxBoxes;
  mw = maxWeight;
  int j = n - 1;
  int totb = 0;
  int totw = 0;
  int beda = 0;
  for(int i=n-1; i>=0; --i){
    ++totb;
    totw += w[i];
    if(i == n - 1 || dest[i] != dest[i+1])
      ++beda;
    while(j > i && (totb > mb || totw > mw)){
      if(dest[j] != dest[j-1])
        --beda;
      --totb;
      totw -= w[j];
      --j;
    }
    dp[i] = beda + 1 + dp[j+1];
    if(kiri[j] > i)
      dp[i] = fmin(dp[i],beda + dp[kiri[j]]);
  }
  return dp[0];
}
