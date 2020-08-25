#pragma GCC optimize "-O3"
#pragma GCC option("arch=native","tune=native","no-zero-upper")
#pragma GCC target("avx")
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

int cnt[100000];

int*findSmallestSetOfVertices(int n, int**edges, int edgesSz, int*edges0sz, int*rsz){
  clr(cnt);
  int i;
  int*res=NULL;
  for(int z=0;z<edgesSz;z++){int*a = edges[z];
    cnt[a[1]]++;
  }
  for(i=0; i<n; i++)
    if(cnt[i]==0)
      sb_push(res, i);
  *rsz=  sb_count(res);
  return res;
}
