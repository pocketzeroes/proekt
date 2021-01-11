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

int*a[505];
bool b[505],g[505][505];
int i,d[505],f[505];
int checkWays(int**pairs, int pairsSz, int*pairs0sz){
  memset(d,0,sizeof(d));
  memset(b,0,sizeof(b));
  memset(g,0,sizeof(g));
  for(int z=0;z<pairsSz;z++){int*e=pairs[z];
    d[e[0]]++;
    d[e[1]]++;
    b[e[0]]=b[e[1]]=1;
    g[e[0]][e[1]]=g[e[1]][e[0]]=1;
  }
  int n=500,i,j;
  for(i=1;i<=n;i++){
    sb_free(a[i]);
    a[i]=NULL;
  }
  for(int z=0;z<pairsSz;z++){int*e=pairs[z];
    if(d[e[0]]<d[e[1]])
      sb_push(a[e[0]], e[1]);
    else
      sb_push(a[e[1]], e[0]);
  }
  for(i=1;i<=n;i++){
    if(b[i]){
      j=0;
      for(int z=0;z<sb_count(a[i]);z++){int c=a[i][z];
        if(!j||d[c]<d[j]||d[c]==d[j]&&c>j)
          j=c;
      }
      f[i]=j;
    }
  }
  for(i=1,j=0;i<=n;i++)
    if(b[i]&&!f[i])
      j++;
  if(!j||j>1)
    return 0;
  for(i=1;i<=n;i++)
    if(b[i])
      for(j=f[i];j;j=f[j])
        if(!g[i][j])
          return 0;
  memset(g,0,sizeof(g));
  for(i=1;i<=n;i++)
    if(b[i])
      for(j=f[i];j;j=f[j])
        g[i][j]=g[j][i]=1;
  for(int z=0;z<pairsSz;z++){int*e=pairs[z];
    if(!g[e[0]][e[1]])
      return 0;
  }
  for(i=1;i<=n;i++)
    if(b[i]&&f[i]&&d[i]==d[f[i]])
      return 2;
  return 1;
}
