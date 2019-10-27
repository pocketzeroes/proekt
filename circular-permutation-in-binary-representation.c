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
/////////////////////////////////////////////////////

int*grayCode(int n){
    int*ans = NULL;
    sb_push(ans, 0);
    if(n == 0)
        return ans;
    sb_push(ans, 1);
    if(n == 1)
        return ans;
    sb_free(ans);
    ans = NULL;
    if(n >= 2){
        int*u = grayCode(n-1);
        for(int z=0;z< sb_count(u); z++){int v = u[z];
            sb_push(ans, v);
        }
        for(int i=sb_count(u)-1; i>=0; i--){
            sb_push(ans, (1<<(n-1))+u[i]);
        }
        return ans;
    }
    return ans;
}
int*circularPermutation(int n, int start, int*rsz){
    int*g = grayCode(n);
    int i = 0;
    for(;i < sb_count(g); i++)
        if(g[i] == start)
            break;
    int*ans = NULL;
    for(int j=i; j< sb_count(g); j++)
        sb_push(ans, g[j]);
    for(int j=0; j<i; j++)
        sb_push(ans, g[j]);
   *rsz =  sb_count(ans);
    return ans;
}
