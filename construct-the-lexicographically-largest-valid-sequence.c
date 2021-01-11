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

int m,a[50];
int*ans;
bool b[25];

bool dfs(int x){
    int i;
    if(x+1==m<<1){
        sb_free(ans);
        ans=NULL;
        for(i=0;i+1<m<<1;i++)
          sb_push(ans, a[i]);
        return 1;
    }
    if(a[x])
      return dfs(x+1);
    for(i=m;i>1;i--)
      if(!b[i]&&x+i+1<m<<1&&!a[x+i]){
        a[x]=a[x+i]=i;
        b[i]=1;
        if(dfs(x+1))
          return 1;
        a[x]=a[x+i]=b[i]=0;
      }
    if(!b[1]){
        a[x]=b[1]=1;
        if(dfs(x+1))
          return 1;
        a[x]=b[1]=0;
    }
    return 0;
}
int*constructDistancedSequence(int n, int*rsz){
    ans=NULL;
    m=n;
    memset(a,0,sizeof(a));
    memset(b,0,sizeof(b));
    dfs(0);
   *rsz=sb_count(ans);
    return ans;
}
