int cmp(const void*a, const void*b){ return(*(int*)a-*(int*)b);}

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

#define REP(i,n) for(int i=0, i##_len=(n); i<i##_len; ++i)

int furthestBuilding(int*heights, int heightsSz, int bricks, int ladders){
    bool ok(int mid){
        int*V=NULL;
        REP(i, mid){
          if(heights[i] < heights[i+1])
              sb_push(V, heights[i+1] - heights[i]);
        }
        if(sb_count(V)>1)
          qsort(V, sb_count(V), sizeof(int), cmp);
        int B = bricks,
            L = ladders;
        for(int z=0;z<sb_count(V);z++){int e=V[z];
            if(e <= B)
                B -= e;
            else if(L)
                L--;
            else{
                sb_free(V);
                return false;
            }
        }
        sb_free(V);
        return true;
    }
    int lo = 0,
        hi = heightsSz;
    while(hi - lo > 1){
        int mid = (lo + hi) / 2;
        if(ok(mid))
           lo=mid;
        else
           hi=mid;
    }
    return lo;
}
