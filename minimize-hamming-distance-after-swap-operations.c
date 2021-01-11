int cmp (const void * a, const void * b){
  return ( *(int*)a - *(int*)b );
}
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

#define REP(i, n) for(int i = 0; i < n; i++)
#define REPP(i, n) for(int i = 1; i <= n; i++)
#define ALL(obj) (obj).begin(), (obj).end()


int**G;
bool*visited;
int*source;
int*target;
int*s;
int*t;

void dfs(int v){
    visited[v] = true;
    sb_push(s, source[v]);
    sb_push(t, target[v]);
    for(int z=0;z<sb_count(G[v]);z++){int nv = G[v][z];
        if(visited[nv]) 
          continue;
        dfs(nv);
    }
    return;
}
int minimumHammingDistance(int*sourc, int sourceSz, int*targe, int targetSz, int**allowedSwaps, int allowedSwapsSz, int*allowedSwaps0sz){
    int n = sourceSz;
    G=calloc(n, sizeof(int*));
    visited=calloc(n, sizeof(bool));
    source = sourc;
    target = targe;
    for(int z=0;z<allowedSwapsSz;z++){int*Swap=allowedSwaps[z];
        int a = Swap[0],
            b = Swap[1];
        sb_push(G[a], b);
        sb_push(G[b], a);
    }
    int ans = n;
    REP(i, n){
        if(visited[i])
          continue;
        sb_free(s);
        sb_free(t);
        s=NULL;
        t=NULL;
        dfs(i);
        qsort(s, sb_count(s), sizeof(int), cmp);
        qsort(t, sb_count(t), sizeof(int), cmp);
        int m = sb_count(s);
        int p1 = 0, p2 = 0;
        while(p1 < m && p2 < m){
            if(s[p1] == t[p2]){
                ans--;
                p1++;
                p2++;
            }
            else if(s[p1] < t[p2]){
                p1++;
            }
            else{
                p2++;
            }
        }
    }
    return ans;
}
