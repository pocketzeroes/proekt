void fill(double*arr, int sz, double val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
#ifndef STB_STRETCHY_BUFFER_H_INCLUDED
#define STB_STRETCHY_BUFFER_H_INCLUDED
#ifndef NO_STRETCHY_BUFFER_SHORT_NAMES
#define sb_free   stb_sb_free
#define push_back   stb_sb_push
#define size      stb_sb_count
#define sb_add    stb_sb_add
#define back      stb_sb_last
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

typedef long long ll;

double*getCollisionTimes(int**cars, int carsSz, int*cars0sz, int*rsz){
    int n=carsSz;
    double*ans = calloc(n, sizeof(double)); fill(ans, n, -1);
    int*st=NULL;
    for(int i=n-1; ~i; --i){
        while(size(st)&&cars[back(st)][1]>=cars[i][1]||size(st)>1&&(ll)(cars[i][0]-cars[back(st)][0])*(cars[st[size(st)-2]][1]-cars[back(st)][1])>(ll)(cars[back(st)][0]-cars[st[size(st)-2]][0])*(cars[back(st)][1]-cars[i][1]))
            stb__sbn(st)--;
        if(size(st))
            ans[i]=(double)(cars[i][0]-cars[back(st)][0])/(cars[back(st)][1]-cars[i][1]);
        push_back(st, i);
    }
   *rsz=n;
    return ans;
}
