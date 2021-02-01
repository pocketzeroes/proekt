#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
enum{ N = 200016};
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

int*restoreArray(int**adjacentPairs, int adjacentPairsSz, int*adjacentPairs0sz, int*rsz){
    int*g[N]; clr(g);
    for(int z=0;z<adjacentPairsSz;z++){int*e = adjacentPairs[z];
        int x = e[0] + N / 2;
        int y = e[1] + N / 2;
        sb_push(g[x], y);
        sb_push(g[y], x);
    }
    int current = 0;
    for(; sb_count(g[current])!=1; ++current);
    int last = -1;
    int*result=NULL;
    while(1){
        sb_push(result, current-N/2);
        int next = -1;
        for(int z=0;z<sb_count(g[current]);z++){int p = g[current][z];
            if(p != last){
                next = p;
                break;
            }
        }
        if(next < 0)
            break;
        last = current;
        current = next;
    }
   *rsz=sb_count(result);
    return result;
}
